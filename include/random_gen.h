#ifndef RANDOMP_H_
#define RANDOMP_H_

class RandomPrimeGenerator {
private:
	// Checks if p is prime
	bool IsPrime(int p);

public:
	// Gets a prime number within [lower_bound, upper_bound)
	int NextPrime(int lower_bound = 50, int upper_bound = 500000);
};

#endif // RANDOMP_H_