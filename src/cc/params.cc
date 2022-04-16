#include <algorithm> // for std::copy
#include <iterator>
#include <vector>

#include <fstream>
#include <iostream>
#include <string>

#include <sstream>
void read_line(std::string line, std::string key, std::vector<double> &ret,
               bool print = true) {
  auto str = line;
  auto ff = str.find(key);
  if (ff != std::string::npos) {
    auto f = str.find("=");
    auto in = str.substr(f + 1);
    std::istringstream iss(in);
    std::istream_iterator<double> start(iss), end;
    std::vector<double> numbers(start, end);
    if (print) {
      std::cout << key << " = ";
      for (auto i : numbers)
        std::cout << i << " ";
      std::cout << std::endl;
    }
    ret = numbers;
  }
}
void read_params(std::string fn, std::vector<double> &bases,
                 std::vector<double> &exponents, bool print) {
  std::ifstream file(fn);
  std::string str;
  while (std::getline(file, str)) {
    read_line(str, "bases", bases, print);
    read_line(str, "exponents", exponents, print);
  }

}

void main2() {
  std::vector<double> bases;
  std::vector<double> exponents;
  read_params("numbers.txt", bases, exponents, true);
}
