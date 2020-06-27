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

// Gets all variables that are used in the expression and lexicographically sorts them
vector<LogicVar> LogicExpression::extract_vars(vector<char> &tokens) {
  std::set<char> var_names;
  for (const char t : tokens) {
    if (std::isalpha(t)) { // if is_var
      var_names.insert(t);
    }
  }
  return vector<LogicVar>(var_names.begin(), var_names.end());
}

bool is_unary_operator(char code) { return code == '~'; }
bool is_binary_operator(char code) { return code == '&' || code == '|' || code == '^' || code == '>' || code == '='; }
bool is_operator(char code)  { return is_binary_operator(code) || is_unary_operator(code); }

bool LogicExpression::evaluate(Valuation &val) {
  // Set valuation on leaves
  for (ExprNode* leaf : expr_tree.iter_leaves()) {
    leaf->valuation = val[leaf->code];
  }
  // Evaluate the expression using postorder traversal
  std::stack<bool> s;
  for (ExprNode* node : expr_tree.iter_postorder()) {
    if (is_operator(node->code)) {
      if (is_unary_operator(node->code)) {
        bool left_child = s.top(); // nodes of unary operators always put their child as left
        s.push(apply_unary_logic_operator(node->code, left_child));
      } else {
        bool right_child = s.top();
        s.pop();
        bool left_child = s.top();
        s.pop();

        s.push(apply_binary_logic_operator(node->code, left_child, right_child));
      }
    } else {
      s.push(node->valuation);
    }
  }
  return s.top();
}


bool LogicExpression::apply_unary_logic_operator(char op_code, bool left_child) {
  switch (op_code) {
    case '~':
      return left_child ^ 1;
  }
  return -1;
}

bool LogicExpression::apply_binary_logic_operator(char op_code, bool left_child, bool right_child) {
  switch (op_code) {
  case '&':
    return left_child & right_child;
  case '|':
    return left_child | right_child;
  case '^':
    return left_child != right_child;
  case '>':
    return !left_child || right_child;
  case '=':
    return left_child == right_child;
  }
  return -1;
}
