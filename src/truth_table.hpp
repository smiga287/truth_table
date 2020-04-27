#ifndef LOGIC_TABLE
#define LOGIC_TABLE
#include <algorithm>
#include <cctype>
#include <string>
#include <unordered_map>
#include <vector>
#define debug(x) std::cout << #x << " is " << x << std::endl;

using std::pair;
using std::string;
using std::unordered_map;
using std::vector;

using LogicVar = char; // check out C++20 concepts to narrow down to letters

void truth_table();

#endif
