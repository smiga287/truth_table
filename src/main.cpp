#include "truth_table.hpp"
#include "logic_expression.hpp"
#include "table.hpp"
#include "valuation.hpp"
#include "variation.hpp"
#include "input.hpp"

int main() {
  auto tokens = get_tokens(); 
  ExprTree tree(tokens);

  for (auto node : tree.iter_leaves()) {
    std::cout << node->code << '\n';
  }

  // truth_table();
}
