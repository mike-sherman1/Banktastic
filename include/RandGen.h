#pragma once

#include <ctime>

using namespace std;

class RandGen {

public:
		RandGen() {
			srand(time(NULL));
		}
		
		int getInt(int lo, int hi) {
			return (rand() % (hi-lo) + lo); 
		}
		
		double getDouble(double lo, double hi) {
			double x = (double)rand() / RAND_MAX;
			return lo + x * (lo - hi);
		}

};