#include <array>
#include <map>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "config.h"
template <std::size_t SIZE> int hashit(std::array<int, SIZE> &ind, int max) {
  int r = 0;
  for (int i = ind.size() - 1; i >= 0; --i) {
    r += ind[i] * pow(max, i);
  }
  return r;
}

template <std::size_t SIZE>
std::vector<int> to_vector(std::array<int, SIZE> &arr) {
  return std::vector<int>(arr.begin(), arr.end());
}

template <std::size_t SIZE>
std::array<int, SIZE> dehashit(const int &hash, const int &max) {
  std::array<int, SIZE> ind{0};
  for (int i = SIZE - 1; i >= 0; --i) {
    for (int j = max - 1; j >= 0; --j) {
      if (hash - hashit(ind, max) - pow(max, i) * j >= 0) {
        ind[i] = j;
        break;
      }
    }
  }
  if (hashit(ind, max) != hash)
    printf("Err");
  return ind;
}
std::vector<std::vector<int>> const_calc(double goal) {
  double bases[] = {BASES};
  double exponents[] = {EXPONENTS};
  const int bases_size = sizeof(bases) / sizeof(*bases);
  const int exponents_size = sizeof(exponents) / sizeof(*exponents);
  const int max = exponents_size;

  std::array<int, bases_size> ind{0};
  std::map<double, int> map;

  bool busy = true;
  while (busy) {
#ifndef NDEBUG
    for (auto i : ind)
      printf("%2d ", i);
    printf("=> %d ", hashit(ind, max));
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
    auto ind = dehashit<bases_size>(kv.second, max);
    results.push_back(to_vector<bases_size>(ind));
  }
  return results;
}
