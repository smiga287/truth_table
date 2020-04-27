#include "table.hpp"

Table::Table(const LogicExpression& expr) : vars(expr.get_vars()) {
  data.reserve(vars.size());
}

void Table::push_back(bool eval) {
  data.push_back(eval);
}

void Table::print() {
  std::cout << "\n\n";
  for (const char name : vars) {
    std::cout << name << " │ ";
  }
  std::cout << "*" << '\n';
  const int table_width = vars.size() * 4 + 2; // check out 4 i 2
  for (auto i = 0; i < table_width; i++) {
    std::cout << "─";
  }
  std::cout << '\n';
  // TODO: change iteration to Variation
  for (int mask = (1 << vars.size()) - 1; mask >= 0; mask--) {
    for (auto i = 0; i < vars.size(); i++) {
      bool is_set_ith_bit = mask & (1 << i);
      char truth_var = is_set_ith_bit ? 'T' : 'F';
      std::cout << truth_var << " │ ";
    }
    char truth_result = data[mask] ? 'T' : 'F';
    std::cout << truth_result << '\n';
  }
  std::cout << "\n\n";
}
