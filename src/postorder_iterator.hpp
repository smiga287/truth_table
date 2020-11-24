#ifndef POSTORDER_ITERATOR
#define POSTORDER_ITERATOR
#include <iterator>

class ExprTree;
class ExprNode;

class PostorderIterator : std::iterator<std::forward_iterator_tag, ExprNode*> {
private:
    friend class ExprTree;
    const ExprTree* tree;
    ExprNode* current_node;
    PostorderIterator(const ExprTree* tree, ExprNode* root);

public:
    PostorderIterator();

    bool operator== (const PostorderIterator& rhs) const;
    bool operator!= (const PostorderIterator& rhs) const;

    ExprNode& operator*();
    ExprNode* operator->();

    // Preincrement
    PostorderIterator& operator++();
    // Postincrement
    PostorderIterator operator++(int);
};

#endif