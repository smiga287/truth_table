#include "logic_expression.hpp"
#include "valuation.hpp"
#include <memory>

// TODO: LogicTerm is a LogicConstant || LogicVar
// TODO: Implement DNF and CNF
// check out http://cs.jhu.edu/~jason/tutorials/convert-to-CNF
// TODO: Implement an AST and cache the leaves (they are the LogicVars)
// or the actual tree could be immutable while only changing the map
// TODO: validation is in the slides

LogicExpression::LogicExpression(vector<char> &tokens)
    : vars(extract_vars(tokens)), expr_tree(tokens) {}

const vector<LogicVar> &LogicExpression::get_vars() const { return vars; }

// Gets all variables that are used in the expression and lexicographically
// sorts them
vector<LogicVar> LogicExpression::extract_vars(vector<char> &tokens) {
  std::set<char> var_names;
  for (const char t : tokens) {
    if (std::isalpha(t)) { // if is_var
      var_names.insert(t);
    }
  }
  return vector<LogicVar>(var_names.begin(), var_names.end());
}

bool LogicExpression::evaluate(Valuation &val) {
  // Set valuation on leaves
  for (ExprNode* leaf : expr_tree.iter_leaves()) {
    leaf->valuation = val[leaf->code];
  }
  // Evaluate the expression using postorder traversal
  std::stack<ExprNode*> s;
  for (ExprNode* node : expr_tree.iter_postorder()) {
    if (node->is_op()) {
      if (node->is_unary()) {
        auto L = s.top()->valuation;
        node->code = apply_unary_logic_operator(node->valuation, L);
        s.push(node);
      } else {
        auto R = s.top()->valuation;
        s.pop();
        auto L = s.top()->valuation;
        s.pop();
        node->code = apply_binary_logic_operator(node->valuation, L, R);
        s.push(node);
      }
    } else {
      s.push(node);
    }
  }
  return s.top()->valuation;
}


bool LogicExpression::apply_unary_logic_operator(char op, char L) {
  switch (op) {
    case '~':
      return L ^ 1;
  }
  return -1;
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
