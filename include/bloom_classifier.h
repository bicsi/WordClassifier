#ifndef BLOOM_H_
#define BLOOM_H_

#include <fstream>
#include "../util/debug.h"

class BloomClassifier {
	vector<vector<int>> bloomFilter;
	vector<string> words;
	vector<int> bases;
	int prime = 0;
	int lowBound = 1;


private:
	// HashFun hashed a word modulo a prime; base is just a parameter here
	int HashFun(int h, string word, int base, int prime);

public:
	// LoadConfig loads saved data from a file
	void LoadConfig(const char* FILENAME);

	// SaveConfig saves current data to a file
	void SaveConfig(const char* FILENAME);

	// LoadWordList loads the word list from a file
	void LoadWordList(const char* FILENAME);

	// Train makes a filter from a prime number, and some bases
	// lowBound here is just a parameter
	void Train(int prime, vector<int> bases, int lowBound = 1);

	// Predict tests a word and returns the prediction
	bool Predict(string word);

};

#endif // BLOOM_H_