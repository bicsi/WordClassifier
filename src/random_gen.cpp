#include "../include/random_gen.h"

#include <cstdlib>

bool RandomPrimeGenerator::IsPrime(int p) {
	for(int d = 2; d * d <= p; ++d)
		if(p % d == 0)
			return false;
	return true;
}

int RandomPrimeGenerator::NextPrime(int lower_bound, int upper_bound) {
	int prime = lower_bound + rand() % (upper_bound - lower_bound);
	while(!IsPrime(prime))
		++prime;

	if(prime >= upper_bound)
		return NextPrime(lower_bound, upper_bound);
	return prime;
}