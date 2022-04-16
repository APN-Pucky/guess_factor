

#include "calc.h"

std::vector<std::vector<int>> flex_calc(double goal,
                                        const std::vector<double> &bases,
                                        const std::vector<double> &exponents) {
  const int bases_size = bases.size();
  const int exponents_size = exponents.size();
  const int max = exponents_size;

  auto ind = std::vector<int>(bases_size, 0);
  std::map<double, hash_t> map;

  double best = -1.;

  bool busy = true;
  while (busy) {
#ifndef NDEBUG
    for (auto i : ind)
      printf("%2d ", i);
    printf("=> %lld ", hashit(ind, max));
#endif

    double cvalue = 1.0;
    for (int i = ind.size() - 1; i >= 0; --i) {
      cvalue *= std::pow(bases[i], exponents[ind[i]]);
    }
    double diff = abs(goal - cvalue);
    bool accepted = false;
    if (best == -1. || diff < std::prev(map.end())->first) {
      map[diff] = hashit(ind, max);
      best = diff;
      accepted = true;
      if (MAX_SIZE > 0 && map.size() > MAX_SIZE) {
        map.erase(std::prev(map.end()));
      }
#ifndef NDEBUG
      printf("map.size() %ld \n", map.size());
#endif
    }
#ifndef NDEBUG
    printf("=> %f \n", abs(goal - cvalue));
#endif

    // next
    // //TODO optimize looping so that less unnecesary calcs happen! by sortung
    // (bases X exponents)
    for (int i = ind.size() - 1; i >= 0; --i) {
      ind[i] = (ind[i] + 1) % exponents_size;
      if (ind[i] != 0) {
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
      if (i == 0)
        busy = false;
    }
    // next
  }
  std::vector<std::vector<int>> results;
  int ii = 0;
  for (auto const &kv : map) {
    auto ind = dehashit(kv.second, max, bases_size);
    results.push_back(ind);
  }

  return results;
}
