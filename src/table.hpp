#ifndef TABLE
#define TABLE

#include "logic_expression.hpp"
#include "truth_table.hpp"
#include <algorithm>
#include <iostream>

class Table {
private:
  vector<pair<unordered_map<LogicVar, bool>, bool>> data;
  const vector<LogicVar> &vars;
  char TRUE = 'T';
  char FALSE = 'F';

public:
  Table(const LogicExpression &expr);
  void insert(unordered_map<LogicVar, bool> mapping, bool eval);
  void print();
  char get_truth_display(bool x);
  void set_truth_display(char f, char t);
};

#endif
