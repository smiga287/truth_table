#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <set>
#include <cctype>

#define debug(x) std::cout << #x << " is " << x << std::endl;

std::vector<char> tokenize(std::string &x) {
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

auto to_postfix(std::vector<char> tokens)
{
  std::unordered_map<char, int> precedence;
  precedence['('] = 0;
  precedence['|'] = 1;
  precedence['&'] = 2;
  precedence['~'] = 3;
  std::deque<char> q;
  std::stack<char> s;
  for (const char &t : tokens) {
    if (t == '(') {
      s.push(t);
    } else if (t == ')') {
      while (s.top() != '(') {
        q.push_back(s.top());
        s.pop();
      }
      s.pop(); // delete the (
    } else if (precedence.count(t)) { // is operator
      while (!s.empty() && precedence[s.top()] >= precedence[t]) {
        q.push_back(s.top());
        s.pop();
      }
      s.push(t);
    } else { // it's a variable
      q.push_back(t);
    }
  }
  while (!s.empty()) {
    q.push_back(s.top());
    s.pop();
  }
  return q;
}

auto get_variable_names(std::vector<char>& tokens) {
  std::set<char> var_names;
  for (const char t : tokens) {
    if (std::isalpha(t)) {
      var_names.insert(t);
    }
  }
  return std::vector<char>(var_names.begin(), var_names.end());
}

auto set_variable_mask(std::vector<char>& var_names, int mask) {
  std::unordered_map<char, bool> vars_mask;
  for (int i = 0; i < var_names.size(); i++) {
    bool is_set_ith_bit = (mask & (1 << i)) != 0;
    vars_mask[var_names[i]] = is_set_ith_bit;
  }
  return vars_mask;
}

std::deque<char> set_expression_value(std::deque<char> expr, std::unordered_map<char, bool>& vars_mask) {
  for (int i = 0; i < expr.size(); i++) {
    if (std::isalpha(expr[i])) {
        expr[i] = vars_mask[expr[i]] ? '1' : '0';
    }
  }
  return expr;
}

bool evaluate(std::deque<char> &expr) {
  std::stack<char> s;
  char el, L, R;
  for (const char &t : expr) {
    if (t == '0' || t == '1') {
      s.push(t);
    } else if (t == '~') {
      el = s.top();
      s.pop();
      s.push(el ^ 1);
    } else {
      R = s.top();
      s.pop();
      L = s.top();
      s.pop();
      if (t == '&') {
        el = L & R;
      } else if (t == '|') {
        el = L | R;
      }
      s.push(el);
    }
  }
  return s.top() - '0';
}

void print_table(std::vector<char>& var_names, std::vector<bool>& results) {
  std::cout << "\n\n";
  for (char name : var_names) {
    std::cout << name << " | ";
  }
  std::cout << "*" << '\n';
  for (int mask = (1 << var_names.size()) - 1; mask >= 0; mask--) {
    for (int i = 0; i < var_names.size(); i++) {
      bool is_set_ith_bit = mask & (1 << i);
      char truth_var = is_set_ith_bit ? 'T' : 'F';
      std::cout << truth_var << " | ";
    }
    char truth_result = results[mask] ? 'T' : 'F';
    std::cout << truth_result << '\n';
  }
  std::cout << "\n\n";
}

/*
 * Ideja je da parsira logički iskaz poput
 * p | ((~q) & r)
 * i da generiše istinosnu tablicu
*/

int main()
{
  std::string infix;
  std::getline(std::cin, infix);
  std::vector<char> tokens = tokenize(infix);
  auto postfix = to_postfix(tokens);
  auto var_names = get_variable_names(tokens);
  std::vector<bool> table_results;
  table_results.reserve(1 << var_names.size());
  for (int mask = (1 << var_names.size()) - 1; mask >= 0; mask--) {
    auto vars_mask = set_variable_mask(var_names, mask);
    auto expr = set_expression_value(postfix, vars_mask);
    bool result = evaluate(expr);
    table_results.push_back(result);
  }
  std::reverse(table_results.begin(), table_results.end());
  print_table(var_names, table_results);
}

