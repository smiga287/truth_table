#ifndef VARIATION
#define VARIATION

#include "truth_table.hpp"

class Variation {
private:
  vector<bool> state;

public:
  Variation(size_t n);
  const vector<bool> *next();
};

#endif
