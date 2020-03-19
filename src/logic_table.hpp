#include <vector>
#include <string>
#define debug(x) std::cout << #x << " is " << x << std::endl;

std::vector<char> tokenize(std::string& x);

std::vector<char> get_variable_names(std::vector<char>& tokens);

void print_table(std::vector<char>& var_names, std::vector<bool>& results);
