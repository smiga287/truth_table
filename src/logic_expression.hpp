#ifndef LOGIC_EXPRESSION
#define LOGIC_EXPRESSION

#include "truth_table.hpp"
#include <set>
#include <stack>

class Valuation; // This should fix circular refferencing

class LogicExpression {
private:
  const vector<LogicVar> vars;
  const vector<char> postfix_expr;

  vector<LogicVar> extract_vars(vector<char> &tokens);
  vector<char> to_postfix(vector<char> &tokens);
  vector<char> set_valuation(Valuation &val);
  bool evaluate(vector<char> &expr);
  bool apply_binary_logic_operator(char op, char L, char R);

public:
  LogicExpression(vector<char> tokens);
  const vector<LogicVar> &get_vars() const;

  bool evaluate(Valuation &val);
};

#endif
