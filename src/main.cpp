#include "truth_table.hpp"
#include <iostream>
#include "logic_expression.hpp"

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

enum Option { INPUT = 1, TRUTH_TABLE, TO_DNF, TO_CNF, QUIT };

std::vector<char> get_tokens() {
  std::string infix;
  std::getline(std::cin, infix);
  return tokenize(infix);
}

void menu() {
  std::cout << "Welcome!" << '\n';
  LogicExpression* expr = nullptr;
  vector<char> tokens;
  bool should_quit = false;
  do {
    std::cout << "Enter option" << '\n';
    std::cout << "1) Input expression" << '\n';
    std::cout << "2) Display the truth table" << '\n';
    std::cout << "3) Convert to DNF" << '\n';
    std::cout << "4) Convert to CNF" << '\n';
    std::cout << "5) Quit" << '\n';

    int input_op;
    std::cin >> input_op;
    Option op = static_cast<Option>(input_op);
    std::cout << input_op << '\n';
    switch (op) {
      case INPUT:
        expr = new LogicExpression(get_tokens()); 
        break;
      case TRUTH_TABLE:
        if (expr) {
          truth_table((*expr));
        } else {
          std::cout << "You must first enter an expression" << '\n';
        }
        break;
      case TO_DNF:
        break;
      case TO_CNF:
        break;
      case QUIT:
        should_quit = true;
        break;
      default:
        std::cout << "Unknown option, enter an option number [1-5]";
    }

  } while (!should_quit);

}

int main() {
  menu();
}
