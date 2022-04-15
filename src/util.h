#ifndef GF_util_h
#define GF_util_h

#include <utility>
#include <vector>

template <typename T, typename U>
std::vector<std::vector<std::pair<double, double>>>
resolve_indices(T &bases, U &exps, std::vector<std::vector<int>> &res) {
  std::vector<std::vector<std::pair<double, double>>> list;
  for (auto ind : res) {
    std::vector<std::pair<double, double>> elem;
    for (int i = 0; i < ind.size(); i++) {
      auto p = std::make_pair(bases[i], exps[ind[i]]);
      elem.push_back(p);
    }
    list.push_back(elem);
  }
  return list;
}

template <typename T, typename U>
std::vector<double> values(T &bases, U &exps,
                           std::vector<std::vector<int>> &res) {
  std::vector<double> list;
  for (auto ind : res) {
    double cvalue = 1.0;
    for (int i = 0; i < ind.size(); i++) {
      cvalue *= pow(bases[i], exps[ind[i]]);
    }
    list.push_back(cvalue);
  }
  return list;
}
#endif