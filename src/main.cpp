#include "truth_table.hpp"
#include "logic_expression.hpp"
#include "table.hpp"
#include "valuation.hpp"
#include "variation.hpp"
#include "input.hpp"

int main() {
  auto tokens = get_tokens(); 
  ExprTree tree(tokens);


  for (ExprNode& node : tree) {
    std::cout << node.code << ' ';
  }
  std::cout << '\n';
  // truth_table();
}
