#ifndef GF_main_h
#define GF_main_h
#define VERSION_INFO 0.0.1

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