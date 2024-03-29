#include <algorithm>
#include <array>
#include <chrono>
#include <map>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "calc.h"
#include "config.h"
#include "info.h"
#include "params.h"
#include "util.h"

void usage(char *arg0) {
  printf("Usage: %s goal [divisor [configfile]]\n", arg0);
  exit(-1);
}

void print_config() {
  printf("bases = ");
  for (double d : {BASES}) {
    printf("%f ", d);
  }
  printf("\nexponents = ");
  for (double d : {EXPONENTS}) {
    printf("%f ", d);
  }
  printf("\n");
}
void print_config(std::vector<double> &bases, std::vector<double> &exponents) {
  printf("bases = ");
  for (double d : bases) {
    printf("%f ", d);
  }
  printf("\nexponents = ");
  for (double d : exponents) {
    printf("%f ", d);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  double goal = 955.439 / 1.66896833e+01;
  std::string fname = "";
  try {
    if (argc == 2) {
      goal = std::stof(argv[1]);
    } else if (argc == 3) {
      goal = std::stof(argv[1]) / atof(argv[2]);
    } else if (argc == 4) {
      goal = std::stof(argv[1]) / atof(argv[2]);
      fname = std::string(argv[3]);
    } else {
      usage(argv[0]);
    }
  } catch (const std::exception &e) {
    usage(argv[0]);
  }
  printf("Goal = %f\n", goal);
  using namespace std::chrono;
  auto start = high_resolution_clock::now();
  if (fname == "") {
    print_config();
    auto res = const_calc(goal);
    print_result(goal, std::array<double, NUMARGS(BASES)>{BASES},
                 std::array<double, NUMARGS(EXPONENTS)>{EXPONENTS}, res);
  } else {
    std::vector<double> bases, exponents;
    read_params(fname, bases, exponents, false);
    print_config(bases, exponents);
    auto res = flex_calc<std::vector<double>, std::vector<double>>(goal, bases,
                                                                   exponents);
    print_result(goal, bases, exponents, res);
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<seconds>(stop - start);
  std::cout << "runtime = " << duration.count() << " s" << std::endl;

  exit(0);
}
