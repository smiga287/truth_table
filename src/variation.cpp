#include "variation.hpp"

Variation::Variation(size_t n) : state(n, 0) {}

// Works only on variations of 0 and 1 which give subsets
const vector<bool> *Variation::next() {
  int i;
  for (i = state.size() - 1; i >= 0 && state[i] == 1; i--) {
    state[i] = 0;
  }
  if (i < 0) {
    return nullptr;
  }
  state[i] = 1;
  return &state;
}
