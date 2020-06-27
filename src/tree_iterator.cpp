#include "expression_tree.hpp"

class TreeIterator {
    friend class ExprTree;

public:
    TreeIterator(const ExprTree* instance, ExprNode* initialNode);

    TreeIterator(const TreeIterator&);

    TreeIterator(TreeIterator&&);

    ~TreeIterator() = default;

    TreeIterator& operator=(const TreeIterator&);
    TreeIterator& operator=(TreeIterator&&);

    TreeIterator& operator++();
    TreeIterator operator++(int);

    ExprNode& operator*();
    ExprNode* operator->();
    const ExprNode* operator->() const;

    bool operator==(const TreeIterator&) const;
    bool operator!=(const TreeIterator&) const;

    /** Used by the tree to generate begin() iterator */
    static TreeIterator begin(ExprTree* instance, ExprNode* rootNode);

private:
    const ExprTree* instance;
    ExprNode* currentNode;
};

TreeIterator::TreeIterator(const ExprTree* instance, ExprNode* initialNode)
  : instance(instance)
  , currentNode(initialNode) {
}

TreeIterator::TreeIterator(const TreeIterator& other)
  : instance(other.instance)
  , currentNode(other.currentNode) {
}

TreeIterator::TreeIterator(TreeIterator&& other)
  : instance(other.instance)
  , currentNode(other.currentNode) {
    other.instance = nullptr;
    other.currentNode = nullptr;
}

TreeIterator& TreeIterator::operator=(const TreeIterator& other) {
    this->instance = other.instance;
    this->currentNode = other.currentNode;
    return *this;
}

TreeIterator& TreeIterator::operator=(TreeIterator&& other) {
    this->instance = other.instance;
    this->currentNode = other.currentNode;

    other.instance = nullptr;
    other.currentNode = nullptr;
    return *this;
}