#include "truth_table.hpp"
#include "logic_expression.hpp"
#include "table.hpp"
#include "valuation.hpp"
#include "variation.hpp"

void truth_table(LogicExpression expr) {
  Valuation val(expr);
  Table results(expr);

  do {
    unordered_map<LogicVar, bool> valuation_map = val.get_mapping();
    results.insert(valuation_map, expr.evaluate(val));
  } while (val.next_valuation());

  results.print();
}
