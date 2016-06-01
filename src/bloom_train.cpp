#include "../include/bloom_classifier.h"
#include "../include/random_gen.h"

#include <ctime>
#include <iostream>

using namespace std;

const int kCountBases = 5;
const int kLowerBound = 400000;
const int kUpperBound = 500000;

int main() {
	srand(time(0));
	BloomClassifier bloom;
	RandomPrimeGenerator gen;
	
	// Load word list from res folder
	bloom.LoadWordList("res/wordlist.txt");
	
	vector<int> bases;
	for(int i = 0; i < kCountBases; ++i) {
		bases.push_back(gen.NextPrime(kLowerBound, kUpperBound));
	}
	int prime = gen.NextPrime(kLowerBound, kUpperBound);

	// Train the model on generated parameters
	bloom.Train(prime, bases, 2);

	// Save the results to file
	bloom.SaveConfig("res/bloom_res");

	BloomClassifier bloom2;
	bloom2.LoadConfig("res/bloom_res");

	bloom2.AssertEqual(bloom);


	return 0;
}