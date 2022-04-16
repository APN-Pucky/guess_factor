#ifndef GF_calc_h
#define GF_calc_h

#include <array>
#include <assert.h>
#include <map>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "config.h"
#include "util.h"

typedef unsigned long long hash_t;

template <typename T> hash_t hashit(const T &ind, const int max) {
  hash_t r = 0;
  for (int i = ind.size() - 1; i >= 0; --i) {
    r += ind[i] * std::pow(max, i);
  }
  return r;
}
// template <typename T> hash_t hashit(const T &ind, const int max);

std::vector<int> dehashit(const hash_t &hash, const int &max, const int SIZE);

#endif