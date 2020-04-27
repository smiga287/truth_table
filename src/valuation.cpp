#include "valuation.hpp"
#include "logic_expression.hpp"
#include "variation.hpp"

Valuation::Valuation(const LogicExpression &expr)
    : vars(expr.get_vars()), v(expr.get_vars().size()) {
  vector<bool> init(vars.size(), false);
  set_mapping(init);
}

void Valuation::set_mapping(const vector<bool> &values) {
  for (auto i = 0; i < values.size(); i++) {
    mapping[vars[i]] = values[i];
  }
}

bool &Valuation::operator[](LogicVar &var) {
  assert(mapping.contains(var));
  return mapping[var];
}

bool Valuation::next_valuation() {
  const vector<bool> *variation = v.next();
  if (variation == nullptr) {
    return false;
  }
  set_mapping(*variation);
  return true;
}
