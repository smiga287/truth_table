#ifndef VARIATION
#define VARIATION

#include "logic_table.hpp"

class Variation {
private:
  vector<bool> state;

public:
  Variation(size_t n);
  const vector<bool> *next();
};

#endif
