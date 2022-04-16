#ifndef GF_params_h
#define GF_params_h

#include <algorithm> // for std::copy
#include <iterator>
#include <vector>

#include <fstream>
#include <iostream>
#include <string>

#include <sstream>
void read_params(std::string fn, std::vector<double> &bases,
                 std::vector<double> &exponents, bool print = false);
#endif