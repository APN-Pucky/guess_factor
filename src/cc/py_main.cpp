#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "flexsize.h"
#include "main.h"
#include "util.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

std::vector<std::vector<int>> py_calc_indices(double goal,
                                              std::vector<double> &bases,
                                              std::vector<double> &exps) {
  auto res = flex_calc(goal, bases, exps);
  return res;
}

std::vector<std::vector<std::pair<double, double>>>
py_calc(double goal, std::vector<double> &bases, std::vector<double> &exps) {
  auto res = flex_calc(goal, bases, exps);
  return resolve_indices(bases, exps, res);
}

std::vector<double> py_calc_values(double goal, std::vector<double> &bases,
                                   std::vector<double> &exps) {
  auto res = flex_calc(goal, bases, exps);
  return values(bases, exps, res);
}

void py_calc_print(double goal, std::vector<double> &bases,
                   std::vector<double> &exps) {
  auto res = flex_calc(goal, bases, exps);
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

  m.def("calc_indices", &py_calc_indices, R"pbdoc(
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

#ifdef VERSION_INFO
  m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
  m.attr("__version__") = "dev";
#endif
}