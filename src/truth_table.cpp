#include "truth_table.hpp"
#include "logic_expression.hpp"
#include "table.hpp"
#include "valuation.hpp"
#include "variation.hpp"
#include "input.hpp"

// TODO: Consider changing LogicVar to LogicTerm or Term
// TODO: Add input validation
// TODO: redesign iteration when C++20 ranges are ready

void truth_table() {
  vector<char> tokens = get_tokens();

  LogicExpression expr(tokens);
  Valuation val(expr);
  Table results(expr);

  do {
    unordered_map<LogicVar, bool> valuation_map = val.get_mapping();
    results.insert(valuation_map, expr.evaluate(val));
  } while (val.next_valuation());

  results.set_truth_display('0', '1');
  results.print();
}
