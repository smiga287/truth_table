#include "expression_tree.hpp"

void ExpressionTree::add_node(std::stack<ExprNode*> &nodes, char op) {
  ExprNode *right = nodes.top();
  nodes.pop();
  ExprNode *left = nodes.top();
  nodes.pop();
  nodes.push(new ExprNode(op, left, right));
}

ExpressionTree::ExpressionTree(vector<char> &tokens) {
  static unordered_map<char, int> precedence{{'>', 1}, {'=', 1}, {'^', 1},
                                             {'|', 2}, {'&', 2}, {'~', 3}};
  std::stack<ExprNode*> nodes;
  std::stack<char> ops;
  for (const char t : tokens) {
    if (t == '(') {
      ops.push(t);
    } else if (t == ')') {
      while (ops.top() != '(') {
        add_node(nodes, ops.top());
        ops.pop();
      }
      ops.pop();                         // deletes the (
    } else if (precedence.contains(t)) { // t is an operator
      // removes operators of higher precedence (OHP) and pushes t to the stack
      while (!ops.empty() && precedence[ops.top()] >= precedence[t]) {
        add_node(nodes, ops.top());
        ops.pop();
      }
      ops.push(t);
    } else { // t is a LogicVar
      nodes.push(new ExprNode(t));
      leaves.push_back(nodes.top()); // populates the leaves vector
    }
  }
  while (!ops.empty()) {
    add_node(nodes, ops.top());
    ops.pop();
  }
  root = nodes.top();
  nodes.pop();
}

IteratorProxy<vector<ExprNode*>> ExpressionTree::iter_leaves() {
  return IteratorProxy<vector<ExprNode*>>(leaves);
}

// IteratorProxy<IteratorPostorder> ExpressionTree::iter_postorder() {
//   IteratorPostorder it();
//   return IteratorProxy<IteratorPostorder>(it);
// }
