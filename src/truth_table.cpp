#include "truth_table.hpp"
#include "logic_expression.hpp"
#include "table.hpp"
#include "valuation.hpp"
#include "variation.hpp"

// TODO: Consider changing LogicVar to LogicTerm or Term
// TODO: Add input validation
// TODO: redesign iteration when C++20 ranges are ready

// Splits the input string into a vector of tokens
std::vector<char> tokenize(std::string &x) {
  std::vector<char> tokens;
  // after each operator/operand one space is most common
  const size_t aprox_token_count = x.size() / 2 + 1;
  tokens.reserve(aprox_token_count);
  for (const char token : x) {
    // consider adding whether allowed symbols were given
    // insted of taking every non white-space char
    if (!std::isspace(token)) {
      tokens.push_back(token);
    }
  }
  return tokens;
}

void truth_table() {
  std::string infix;
  std::getline(std::cin, infix);
  vector<char> tokens = tokenize(infix);

  LogicExpression expr(tokens);
  Valuation val(expr);
  Table results(expr);

  do {
    unordered_map<LogicVar, bool> valuation_map = val.get_mapping();
    results.insert(valuation_map, expr.evaluate(val));
  } while (val.next_valuation());

  results.print();
}
