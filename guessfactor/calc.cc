

#include "calc.h"

// OpenMP Header
#ifdef _OPENMP
#include <omp.h>
#endif

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
/**
 * @brief Gets the closest values to goal from combining bases and exponents.
 *
 *
 * @tparam T std::vector<double> or std::array<double,N>
 * @tparam U std::vector<double> or std::array<double,M>
 * @param goal factor to reproduce with bases and expoenents
 * @param bases sorted list of bases
 * @param exponents sorted list of exponents
 * @return return_t
 */
template <typename T, typename U>
return_t flex_calc(const double goal, const T &bases, const U &exponents) {
  // const int THREADS = omp_get_num_threads();
  const int bases_size = bases.size();
  const int exponents_size = exponents.size();
  const int max = exponents_size;

  const int LOOPS = std::pow(exponents_size, OMP_LOOPS);

  std::map<double, hash_t> map[LOOPS];

#pragma omp parallel for
  for (int j = 0; j < LOOPS; ++j) {
    // int t = omp_get_thread_num();
    int t = j;
    auto ind = std::vector<int>(bases_size, 0);
    double best = -1.;
    auto preid = dehashit(j, exponents_size, OMP_LOOPS);
    for (int k = 0; k < OMP_LOOPS; ++k) {
      ind[k] = preid[k];
    }
    bool busy = true;

    // we use a while loop here to act as N for loops
    while (busy) {
#ifndef NDEBUG
      for (auto i : ind)
        printf("%2d ", i);
      printf("=> %lld ", hashit(ind, max));
#endif

      // compute value from bases X exponents
      double cvalue = 1.0;
      for (int i = ind.size() - 1; i >= 0; --i) {
        cvalue *= std::pow(bases[i], exponents[ind[i]]);
      }
      // store value if it is good
      double diff = abs(goal - cvalue);
      bool accepted = false;
      if (best == -1. || diff < std::prev(map[t].end())->first) {
        map[t][diff] = hashit(ind, max);
        best = diff;
        accepted = true;
        if (MAX_SIZE > 0 && map[t].size() > MAX_SIZE) {
          map[t].erase(std::prev(map[t].end()));
        }
#ifndef NDEBUG
        printf("map.size() %ld \n", map[t].size());
#endif
      }
#ifndef NDEBUG
      printf("=> %f \n", abs(goal - cvalue));
#endif

      // next (bases X exponents)
      int fin = OMP_LOOPS;
      for (int i = ind.size() - 1; i >= fin; --i) {
        ind[i] = (ind[i] + 1) % exponents_size;
        if (ind[i] != 0) {
          // bases are sorted so we can skip further evaluation if we are too
          // low/high.
          if (!accepted && bases[i] > 0 &&
              (cvalue > goal && bases[i] > 1. ||
               cvalue < goal && bases[i] < 1.)) {
            ind[i] = 0;
            accepted = true;
            /// break;
          } else {
            break;
          }
        }
        if (i == fin)
          busy = false;
      }
      // next
    }
  }
  // merge maps
  std::map<double, hash_t> total_map;
  for (int t = 0; t < LOOPS; ++t) {
    for (auto r : map[t]) {
      total_map[r.first] = r.second;
    }
  }
  // shrink map
  while (MAX_SIZE > 0 && total_map.size() > MAX_SIZE) {
    total_map.erase(std::prev(total_map.end()));
  }

  std::vector<std::vector<int>> results;
  for (auto const &kv : total_map) {
    auto ind = dehashit(kv.second, max, bases_size);
    results.push_back(ind);
  }

  return results;
}

template <typename T, typename U>
return_t sort_calc(const double goal, T &bases, U &exponents) {
  std::sort(exponents.begin(), exponents.end());
  std::sort(bases.begin(), bases.end());
  return flex_calc(goal, bases, exponents);
}
// deprecated
return_t const_calc(double goal) {
  auto bases = std::array<double, NUMARGS(BASES)>{BASES};
  auto exponents = std::array<double, NUMARGS(EXPONENTS)>{EXPONENTS};
  return sort_calc(goal, bases, exponents);
}

// Explicit template instatiation

template return_t sort_calc(const double goal, std::vector<double> &bases,
                            std::vector<double> &exponents);

template return_t flex_calc(const double goal, const std::vector<double> &bases,
                            const std::vector<double> &exponents);
