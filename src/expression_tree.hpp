#ifndef EXPRESSION_TREE
#define EXPRESSION_TREE
#include "truth_table.hpp"
#include <memory>
#include <stack>
#include <vector>
#include "postorder_iterator.hpp"

// class PostorderIterator;

struct ExprNode {
    char code;
    ExprNode* left;
    ExprNode* right;
    ExprNode* postorder_link;
    ExprNode(char _code) : code(_code), left(nullptr), right(nullptr), postorder_link(nullptr) {};
    ExprNode(char _code, ExprNode* _left, ExprNode* _right)
        : code(_code), left(_left), right(_right), postorder_link(nullptr) {};
};

class ExprTree {
private:
  ExprNode* root;

  void add_operator_node(std::stack<ExprNode*>& nodes, char op_code);
  void create_postorder_links(ExprNode* root);

public:
  // typedef PostorderIterator const_iterator;
  // typedef const_iterator iterator;

  ExprTree(vector<char> &tokens);
  PostorderIterator begin() const;
  PostorderIterator end() const;
};

#endif
