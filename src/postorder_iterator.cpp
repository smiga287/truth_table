#include "postorder_iterator.hpp"
#include "expression_tree.hpp"

PostorderIterator::PostorderIterator(const ExprTree* tree, ExprNode* root) : tree(tree), current_node(root) {}

PostorderIterator& PostorderIterator::operator++() {
    current_node = current_node->postorder_link;
    return *this;
}

bool PostorderIterator::operator==(const PostorderIterator& rhs) const {
    return *this == rhs;
}

bool PostorderIterator::operator!=(const PostorderIterator& rhs) const {
    return *this != rhs;
}

ExprNode& PostorderIterator::operator*() {
    return *current_node;
}

ExprNode* PostorderIterator::operator->() {
    return current_node;
}
