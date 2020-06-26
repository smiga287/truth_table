#include "expression_tree.hpp"

class ExpressionTree {
private:
  struct Node {
    char val;
    Node* left;
    Node* right;
    Node(char _val) : val(_val){};
    Node(char _val, Node *_left, Node *_right)
        : val(_val), left(_left), right(_right){};
  };

  Node* root;

  void add_node(std::stack<Node*> &nodes, char op);

public:
  ExpressionTree(vector<char> &tokens);
};

void ExpressionTree::add_node(std::stack<Node*> &nodes, char op) {
  Node *right = nodes.top();
  nodes.pop();
  Node *left = nodes.top();
  nodes.pop();
  nodes.push(new Node(op, left, right));
}

ExpressionTree::ExpressionTree(vector<char> &tokens) {
  static unordered_map<char, int> precedence{{'>', 1}, {'=', 1}, {'^', 1},
                                             {'|', 2}, {'&', 2}, {'~', 3}};
  std::stack<Node*> nodes;
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
      nodes.push(new Node(t));
    }
  }
  while (!ops.empty()) {
    add_node(nodes, ops.top());
    ops.pop();
  }
  root = nodes.top();
  nodes.pop();
}
