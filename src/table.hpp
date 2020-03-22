#ifndef TABLE
#define TABLE

#include "logic_expression.hpp"
#include "logic_table.hpp"
#include <iostream>

class Table {
private:
  vector<bool> data;
  const vector<LogicVar>& vars;

public:
  Table(const LogicExpression& expr);
  void push_back(bool eval);
  void print();
};

#endif

