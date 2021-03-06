#include <math.h>
#include <stdio.h>
#include <array>
#include <map>
#include <vector>


#include "config.h"


int hashit(std::vector<int>& ind,int max) {
	int r = 0;
	for(int  i=ind.size()-1; i >=0;--i){
		r += ind[i]*pow(max,i);
	}
	return r;
}

std::vector<int> dehashit(const int& hash, const int& max, const int SIZE){
	std::vector<int> ind(SIZE);
	for(int  i=SIZE-1; i >=0;--i){
		for(int  j=max-1; j >=0;--j){
			if(hash-hashit(ind,max)-pow(max,i)*j>=0) 
			{
				ind[i] = j;
				break;
			}
		}
	}
	if(hashit(ind,max)!=hash)printf("Err");
	return ind;
}
void flex_calc( double goal, const std::vector<double>& bases, const std::vector<double>& exponents)
{
	//double bases[] = BASES ;//{6.28520451e-02, 5.60898409e+05,0.10305006, 1.78737774e-11,2.0,3.0,3.14159265};
	//double exponents[] = EXPONENTS ;//{0,1,-1,2,-2,3,-3,4,-4,5,-5};
	const int bases_size = bases.size();//sizeof(bases)/sizeof(*bases);
	const int exponents_size = exponents.size(); //sizeof(exponents)/sizeof(*exponents);
	const int max = exponents_size;
	
	auto ind = std::vector<int>(bases_size,0);
	//std::fill(ind.begin(), ind.end(), 0);
	std::map<double,int> map;

	bool debug = false;
	bool busy = true;
	while(busy){
		for( auto i : ind)
			if(debug)printf("%2d ",i);
		if(debug)printf("=> %d ",hashit(ind,max));
		
		double cvalue=1.0;
		for(int  i=ind.size()-1; i >=0;--i){
			if((i == 0 || i == 1 ) && exponents[ind[i]] != 0 && exponents[ind[i]] != 1&& exponents[ind[i]] != -1) {cvalue = 1; break;}
			cvalue *= pow(bases[i],exponents[ind[i]]);
		}
		map[abs(goal-cvalue)]=hashit(ind,max);
		if(debug)printf("=> %f \n",abs(goal-cvalue));



		// next
		// //TODO optimize looping so that less unnecesary calcs happen! by sortung (bases X exponents)
		for(int  i=ind.size()-1; i >=0;--i){
			ind[i]=(ind[i]+1)%exponents_size;
			if(ind[i]!=0)
			{
				break;
			}
			if(i==0)
				busy = false;
		}
		// next
	}
	printf("\n\nRESULT: \n\n");
	int ii = 0;
	for(auto const &kv : map){
		auto ind = dehashit(kv.second,max,bases_size);
		for(auto i : ind)
			printf("%2d ",i);
		printf(" == ");
		for(int  i=0; i < ind.size();i++){
			printf(" %8f**",bases[i]);
			printf("%8f *",exponents[ind[i]]);
		}
		double cvalue=1.0;
		for(int  i=ind.size()-1; i >=0;--i){
			cvalue *= pow(bases[i],exponents[ind[i]]);
		}
		printf(" = %8f ",cvalue);
		printf("=> %8f \n",kv.first);
		ii++;
		if(ii==25)break;
	}

	
}

