#ifndef VALUATION
#define VALUATION

#include "truth_table.hpp"
#include "variation.hpp"
#include <cassert>

class LogicExpression;

class Valuation {
private:
  unordered_map<LogicVar, bool> mapping;
  const vector<LogicVar> &vars;
  Variation v; // will probably change v to var and vars to terms
  void set_mapping(const vector<bool> &values);

public:
  Valuation(const LogicExpression &expr);
  bool &operator[](LogicVar &var);
  bool next_valuation();
};

#endif
