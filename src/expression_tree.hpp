#ifndef EXPRESSION_TREE
#define EXPRESSION_TREE
#include "truth_table.hpp"
#include <memory>
#include <stack>
#include <vector>

template<typename Container>
class IteratorProxy {
  private:
    Container& _container;
  public:
    IteratorProxy(Container& container) : _container(container) {};

    typename Container::iterator begin() {
      return _container.begin();
    }

    typename Container::iterator end() {
      return _container.end();
    }
};

struct ExprNode {
    bool valuation;
    char code;
    ExprNode* left;
    ExprNode* right;
    vector<ExprNode*> leaves;
    ExprNode(char _code) : code(_code){};
    ExprNode(char _code, ExprNode* _left, ExprNode* _right)
        : code(_code), left(_left), right(_right){};
};

// TODO
class IteratorPostorder {
};

class ExprTree {
private:

  ExprNode* root;
  vector<ExprNode*> leaves;

  void add_operator_node(std::stack<ExprNode*> &nodes, char op_code);

public:
  ExprTree(vector<char> &tokens);
  IteratorProxy<vector<ExprNode*>> iter_leaves();
  // IteratorProxy<IteratorPostorder> iter_postorder();
};


#endif
