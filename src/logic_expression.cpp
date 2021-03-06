#include "logic_expression.hpp"
#include "valuation.hpp"

// TODO: LogicTerm is a LogicConstant || LogicVar
// TODO: Implement DNF and CNF
// check out http://cs.jhu.edu/~jason/tutorials/convert-to-CNF
// TODO: Implement an AST and cache the leaves (they are the LogicVars)
// or the actual tree could be immutable while only changing the map
// TODO: validation is in the slides

LogicExpression::LogicExpression(vector<char> tokens)
    : vars(extract_vars(tokens)), postfix_expr(to_postfix(tokens)) {}

const vector<LogicVar> &LogicExpression::get_vars() const { return vars; }

vector<char> LogicExpression::to_postfix(vector<char> &tokens) {
  unordered_map<char, int> precedence; // defines operator precedence
  precedence['('] = 0;
  precedence['>'] = 1; // implication
  precedence['='] = 1; // eqvivalence
  precedence['^'] = 1; // exclusive disjunction
  precedence['|'] = 2; // disjunction
  precedence['&'] = 2; // conjunction
  precedence['~'] = 3; // negation
  vector<char> postfix;
  std::stack<char> s;
  for (const char t : tokens) {
    if (t == '(') {
      s.push(t);
    } else if (t == ')') {
      while (s.top() != '(') {
        postfix.push_back(s.top());
        s.pop();
      }
      s.pop();                           // deletes the (
    } else if (precedence.contains(t)) { // t is an operator
      // removes operators of higher precedence (OHP) and pushes t to the stack
      while (!s.empty() && precedence[s.top()] >= precedence[t]) {
        postfix.push_back(s.top()); // saves OHP to the output vector
        s.pop();
      }
      s.push(t);
    } else { // t is a LogicVar
      postfix.push_back(t);
    }
  }
  while (!s.empty()) {
    postfix.push_back(s.top());
    s.pop();
  }
  return postfix;
}

vector<char> LogicExpression::set_valuation(Valuation &val) {
  auto expr = postfix_expr;
  for (char &t : expr) {
    if (std::isalpha(t)) { // t is LogicVar
      t = val[t] ? '1' : '0';
    }
  }
  return expr;
}

// Gets all variables that are used in the expression and lexicographically
// sorts them
vector<LogicVar> LogicExpression::extract_vars(vector<char> &tokens) {
  std::set<char> var_names;
  for (const char t : tokens) {
    if (std::isalpha(t)) {
      var_names.insert(t);
    }
  }
  return vector<LogicVar>(var_names.begin(), var_names.end());
}

bool LogicExpression::evaluate(Valuation &val) {
  vector<char> expr = set_valuation(val);
  std::stack<char> s;
  char el, L, R;
  for (const char t : expr) {
    if (t == '0' || t == '1') { // is LogicConstant
      s.push(t);
    } else if (t == '~') {
      el = s.top();
      s.pop();
      s.push(el ^ 1); // changes 0 to 1 and vice versa
    } else {
      R = s.top();
      s.pop();
      L = s.top();
      s.pop();
      s.push(apply_binary_logic_operator(t, L, R) ? '1' : '0');
    }
  }
  return s.top() - '0';
}

bool LogicExpression::apply_binary_logic_operator(char op, char L, char R) {
  switch (op) {
  case '&':
    return (L & R) - '0';
  case '|':
    return (L | R) - '0';
  case '^':
    return L != R;
  case '>':
    return !(L == '1' && R == '0'); // change to !L || R
  case '=':
    return L == R;
  }
  return -1; // check this out
}
