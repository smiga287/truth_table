#include <vector>
#include <cctype>
#include <string>
#include <set>

std::vector<char> tokenize(std::string& x) {
  std::vector<char> tokens;
  // after each operator/operand one space is most common
  const unsigned aprox_token_count = x.size() / 2 + 1;
  tokens.reserve(aprox_token_count);
  for (const char token : x) {
    if (!std::isspace(token)) {
      tokens.push_back(token);
    }
  }
  return tokens;
}

// Gets all variables that are used in the expression and lexicographically sorts them
std::vector<char> get_variable_names(std::vector<char>& tokens) {
  std::set<char> var_names;
  for (const char t : tokens) {
    if (std::isalpha(t)) {
      var_names.insert(t);
    }
  }
  return std::vector<char>(var_names.begin(), var_names.end());
}
