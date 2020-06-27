#include "expression_tree.hpp"

// Adds a non leaf node to the expression tree
void ExprTree::add_operator_node(std::stack<ExprNode*> &nodes, char op_code) {
  ExprNode *right = nodes.top();
  nodes.pop();
  ExprNode *left = nodes.top();
  nodes.pop();
  nodes.push(new ExprNode(op_code, left, right));
}

// Implements Dijkstra's Shunting Yard algorithm for creating an expression tree
ExprTree::ExprTree(vector<char> &tokens) {
  static unordered_map<char, int> precedence{{'>', 1}, {'=', 1}, {'^', 1},
                                             {'|', 2}, {'&', 2}, {'~', 3}};
  std::stack<ExprNode*> nodes;
  std::stack<char> ops; // operators stack
  for (const char t : tokens) {
    if (t == '(') {
      ops.push(t);
    } else if (t == ')') {
      while (ops.top() != '(') {
        add_operator_node(nodes, ops.top());
        ops.pop();
      }
      ops.pop(); // deletes the (
    } else if (precedence.contains(t)) { // t is an operator
      // removes operators of higher precedence and pushes t to the stack
      while (!ops.empty() && precedence[ops.top()] >= precedence[t]) {
        add_operator_node(nodes, ops.top());
        ops.pop();
      }
      ops.push(t);
    } else { // t is a LogicVar
      nodes.push(new ExprNode(t));
      leaves.push_back(nodes.top()); // populates the leaves vector
    }
  }
  while (!ops.empty()) {
    add_operator_node(nodes, ops.top());
    ops.pop();
  }
  root = nodes.top();
  nodes.pop();
}

// Returns a range iterator on leaves
IteratorProxy<vector<ExprNode*>> ExprTree::iter_leaves() {
  return IteratorProxy<vector<ExprNode*>>(leaves);
}

// Returns a range iterator which does a postorder traversal
// IteratorProxy<IteratorPostorder> ExprTree::iter_postorder() {
// TODO
// }
