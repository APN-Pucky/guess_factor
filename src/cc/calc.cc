
#include "calc.h"



std::vector<int> dehashit(const hash_t &hash, const int &max, const int SIZE) {
  std::vector<int> ind(SIZE);
  for (int i = SIZE - 1; i >= 0; --i) {
    for (int j = max - 1; j >= 0; --j) {
      if (hash - hashit(ind, max) - pow(max, i) * j >= 0) {
        ind[i] = j;
        break;
      }
    }
  }
  assert(hashit(ind, max) == hash);
  return ind;
}
