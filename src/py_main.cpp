#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "calc.h"
#include "info.h"
#include "util.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

std::vector<std::vector<std::pair<double, double>>>
py_calc(double goal, std::vector<double> &bases, std::vector<double> &exps) {
  auto res = sort_calc(goal, bases, exps);
  return resolve_indices(bases, exps, res);
}

std::vector<double> py_calc_values(double goal, std::vector<double> &bases,
                                   std::vector<double> &exps) {
  auto res = sort_calc(goal, bases, exps);
  return values(bases, exps, res);
}

void py_calc_print(double goal, std::vector<double> &bases,
                   std::vector<double> &exps) {
  auto res = sort_calc(goal, bases, exps);
  print_result(goal, bases, exps, res);
}

PYBIND11_MODULE(guessfactor, m) {
  m.doc() = R"pbdoc(
        Pybind11 guess factor plugin
        -------------------------------
        .. currentmodule:: guessfactor
        .. autosummary::
	   :toctree: _autosummary

	   calc
	   calc_indices
	   calc_values
	   calc_print

    )pbdoc";

  m.def("calc", &py_calc, R"pbdoc(
        Guess the factor from bases and exponents.
	First parameter is the goal.

	second parameter are the bases and then the exponents. 

	Returns an ordered list with indices of the exponents.
    )pbdoc");

  m.def("calc_values", &py_calc_values, R"pbdoc(
        Guess the factor from bases and exponents.
	First parameter is the goal.

	second parameter are the bases and then the exponents. 

	Returns an ordered list with indices of the exponents.
    )pbdoc");

  m.def("calc_print", &py_calc_print, R"pbdoc(
          Guess the factor from bases and exponents.
          First parameter is the goal.

          second parameter are the bases and then the exponents.

          Returns an ordered list with indices of the exponents.
      )pbdoc");
  m.def("get_max_threads", &omp_get_max_threads,
        "Returns max number of threads");
  m.def("set_num_threads", &omp_set_num_threads, "Set number of threads");

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}