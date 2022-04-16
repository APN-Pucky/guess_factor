#ifndef GF_util_h
#define GF_util_h

#include <array>
#include <utility>
#include <vector>

template <std::size_t SIZE>
std::vector<int> to_vector(std::array<int, SIZE> &arr) {
  return std::vector<int>(arr.begin(), arr.end());
}

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
template <typename T, typename U>
void print_result(double goal, T bases, U exponents,
                  std::vector<std::vector<int>> &results) {
  for (int ii = 0; ii < std::min(25, static_cast<int>(results.size())); ii++) {
    auto ind = results[ii];
    for (auto i : ind)
      printf("%2d ", i);
    printf(" == ");
    double cvalue = 1.0;
    for (int i = 0; i < ind.size(); i++) {
      printf(" %.8f**", bases[i]);
      printf("%.8f *", exponents[ind[i]]);
      cvalue *= pow(bases[i], exponents[ind[i]]);
    }
    printf(" = %.8f ", cvalue);
    printf("=> %.8f (%8f%%)\n", goal - cvalue, (goal - cvalue) / goal * 100);
  }
}
#endif