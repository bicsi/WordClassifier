#include "../include/bloom_classifier.h"
#include "../include/random_gen.h"
#include "../include/model_tester.h"
#include "../util/debug.h"

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
	ModelTester tester;

	// Load word list from res folder
	bloom.LoadWordList("res/wordlist.txt");

	// Load test cases from res folder
	tester.LoadTestData("res/words-test.txt");

	double bestAccuracy = 0.0;

	for(int i = 0; ; ++i) {
		debug("At iteration #%d\n", i);
		debug("----------------------\n\n");

		// Train and test

		vector<int> bases;
		for(int i = 0; i < kCountBases; ++i) {
			bases.push_back(gen.NextPrime(kLowerBound, kUpperBound));
		}
		int prime = gen.NextPrime(kLowerBound, kUpperBound);

		// Train the model on generated parameters
		bloom.Train(prime, bases, 3);
	
		// Test the model on test cases
		tester.TestModel(bloom);

		if(tester.accuracy > bestAccuracy) {
			bestAccuracy = tester.accuracy;
			bloom.SaveConfig("res/bloom_res");
		}

		// Dump results to stdout
		tester.DumpResults(cout);
	}


	return 0;
}