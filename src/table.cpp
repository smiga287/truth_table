#include "table.hpp"
#include "truth_table.hpp"
#include "variation.hpp"

Table::Table(const LogicExpression &expr) : vars(expr.get_vars()) {
  data.reserve(vars.size());
}

void Table::insert(unordered_map<LogicVar, bool> mapping, bool eval) {
  data.emplace_back(mapping, eval);
}

char Table::display_truth(bool x) { return x ? 'T' : 'F'; }

void Table::print() {
  std::cout << "\n\n";

  for (const LogicVar var : vars) {
    std::cout << var << " │ ";
  }
  std::cout << "*" << '\n';

  const int table_width = vars.size() * 4 + 1; // check out 4 and 2
  for (int i = 0; i < table_width; i++) {
    std::cout << "─";
  }
  std::cout << '\n';

  std::reverse(data.begin(), data.end());
  for (auto [mapping, eval] : data) {
    for (LogicVar var : vars) {
      std::cout << display_truth(mapping[var]) << " │ ";
    }
    std::cout << display_truth(eval) << '\n';
  }

  std::cout << "\n\n";
}
