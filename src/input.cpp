#include "input.hpp"

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

vector<char> get_tokens() {
  std::string infix;
  std::getline(std::cin, infix);
  vector<char> tokens = tokenize(infix);
  return tokens;
}