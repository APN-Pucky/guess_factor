#ifndef GF_calc_h
#define GF_calc_h

#include <algorithm>
#include <array>
#include <assert.h>
#include <map>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "config.h"
#include "util.h"

#define NUMARGS(...) (sizeof((double[]){__VA_ARGS__}) / sizeof(double))

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

template <typename T, typename U>
std::vector<std::vector<int>> flex_calc(double goal, const T &bases,
                                        const U &exponents);

template <typename T, typename U>
std::vector<std::vector<int>> sort_calc(double goal, T bases, U exponents);

std::vector<std::vector<int>> const_calc(double goal);

#endif