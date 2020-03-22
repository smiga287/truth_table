#ifndef LOGIC_EXPRESSION
#define LOGIC_EXPRESSION

#include "logic_table.hpp"
#include <stack>
#include <set>

class Valuation; // This should fix circular refferencing 
// #include "valuation.hpp"

class LogicExpression {
private:
  const vector<LogicVar> vars;
  const vector<char> postfix_expr;

  vector<LogicVar> extract_vars(vector<char> &tokens);
  vector<char> to_postfix(vector<char> &tokens);
  vector<char> set_valuation(Valuation &val);
  bool evaluate(vector<char> &expr);

public:
  LogicExpression(vector<char> &tokens);
  const vector<LogicVar> &get_vars() const;

  bool evaluate(Valuation &val);
};

#endif
