#include <math.h>
#include <stdio.h>
#include <array>
#include <map>
#include <vector>
#include <chrono> 

#include "config.h"
#include "params.h"
#include "constsize.h"
#include "flexsize.h"

void usage(char* arg0) {
	printf("Usage: %s goal [divisor [configfile]]\n",arg0);
	exit(-1);
}

int main( int argc, char** argv)
{
	double goal =955.439/1.66896833e+01;
	std::string fname="";
	try {
		if(argc == 2) {
			goal = std::stof(argv[1]);
		}
		else if(argc == 3) {
			goal = std::stof(argv[1])/atof(argv[2]);
		}
		else if(argc == 4) {
			goal = std::stof(argv[1])/atof(argv[2]);
			fname = std::string(argv[3]);
		}
		else {
			usage(argv[0]);
		}
	}
	catch(const std::exception& e) {
		usage(argv[0]);
	}
	printf("Goal = %f\n",goal);
	using namespace std::chrono; 
	auto start = high_resolution_clock::now(); 
	if(fname == ""){
		const_calc(goal);
	}
	else {
		std::vector<double> bases, exponents;
		read_params("numbers.txt",bases, exponents,true);
		flex_calc(goal,bases,exponents);
	}
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<seconds>(stop - start); 
	std::cout << "runtime = " << duration.count() << " s" << std::endl; 
	
	exit(0);
}

