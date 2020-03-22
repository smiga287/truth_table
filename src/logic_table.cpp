#include "logic_table.hpp"
#include "logic_expression.hpp"
#include "valuation.hpp"
#include "table.hpp"

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
    if (!std::isspace(
            token)) { // consider adding whether allowed symbols were given
                      // insted of taking every non white-space char
      tokens.push_back(token);
    }
  }
  return tokens;
}

void logic_table() {
  std::string infix;
  std::getline(std::cin, infix);
  vector<char> tokens = tokenize(infix);

  LogicExpression expr(tokens);
  Valuation val(expr);
  Table results(expr);

  do {
    results.push_back(expr.evaluate(val));
  } while (val.next_valuation());

  results.print();
}

