#include <iostream>
#include <vector>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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

auto get_variables(std::vector<char> tokens) {
  std::unordered_map<char, bool> vars;
  for (const char &t : tokens) {
    if (std::isalpha(t)) {
      vars.insert({ t, false });
    }
  }
  return vars;
}

void set_variable_mask(std::unordered_map<char, bool>& vars, int mask) {
  for (auto &v : vars) {
    vars[v.first] = false;
  }
  auto idx = std::begin(vars);
  for (int i = 0; i < vars.size(); i++) {
    if (mask & (1 << i)) {
      std::advance(idx, i);
      idx->second = true;
    }
  }
}

std::deque<char> set_expression_value(std::deque<char> expr, std::unordered_map<char, bool>& vars) {
  for (int i = 0; i < expr.size(); i++) {
    if (std::isalpha(expr[i])) {
        expr[i] = vars[expr[i]] ? '1' : '0';
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
/*
 * Ideja je da parsira logički iskaz poput
 * p | ((~q) & r)
 * i da generiše sve moguće istinosne tablice
*/
int main()
{
  std::string infix;
  std::getline(std::cin, infix);
  std::vector<char> tokens = tokenize(infix);
  auto postfix = to_postfix(tokens);
  auto vars = get_variables(tokens);
  for (int mask = (1 << vars.size()) - 1; mask >= 0; mask--) {
    debug(mask);
    set_variable_mask(vars, mask);
    // auto expr = set_expression_value(postfix, vars);
    // bool result = evaluate(expr);
    // std::cout << result << '\n';
  }
}

