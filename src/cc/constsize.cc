

#include "calc.h"

std::vector<std::vector<int>> const_calc(double goal) {
  double bases[] = {BASES};
  double exponents[] = {EXPONENTS};
  const int bases_size = sizeof(bases) / sizeof(*bases);
  const int exponents_size = sizeof(exponents) / sizeof(*exponents);
  const int max = exponents_size;

  std::array<int, bases_size> ind{0};
  std::map<double, hash_t> map;

  bool busy = true;
  while (busy) {
#ifndef NDEBUG
    for (auto i : ind)
      printf("%2d ", i);
    printf("=> %lld ", hashit(ind, max));
#endif

    double cvalue = 1.0;
    for (int i = ind.size() - 1; i >= 0; --i) {
      if ((i == 0 || i == 1) && exponents[ind[i]] != 0 &&
          exponents[ind[i]] != 1 && exponents[ind[i]] != -1) {
        cvalue = 1;
        break;
      }
      cvalue *= pow(bases[i], exponents[ind[i]]);
    }
    map[abs(goal - cvalue)] = hashit(ind, max);
#ifndef NDEBUG
    printf("=> %f \n", abs(goal - cvalue));
#endif

    // next
    // //TODO optimize looping so that less unnecesary calcs happen! by sortung
    // (bases X exponents)
    for (int i = ind.size() - 1; i >= 0; --i) {
      ind[i] = (ind[i] + 1) % exponents_size;
      if (ind[i] != 0) {
        break;
      }
      if (i == 0)
        busy = false;
    }
    // next
  }
  std::vector<std::vector<int>> results;
  for (auto const &kv : map) {
    auto ind = dehashit(kv.second, max, bases_size);
    results.push_back(ind);
  }
  return results;
}
