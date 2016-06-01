// Declaration of BloomClassifier

#ifndef BLOOM_H_
#define BLOOM_H_

#include <vector>
#include <string>

class BloomClassifier {
	std::vector<std::vector<int>> bloomFilter;
	std::vector<std::string> words;
	std::vector<int> bases;
	int prime = 0;
	int lowBound = 1;


private:
	// HashFun hashed a word modulo a prime; base is just a parameter here
	int HashFun(int h, std::string word, int base, int prime);

	// AddWords adds words from the vector to the bloom filter
	void AddWords();

	// Prune prunes bloom filter to be more sparse
	void PruneFilter();

public:
	// LoadConfig loads saved data from a file
	void LoadConfig(const char* FILENAME);

	// SaveConfig saves current data to a file
	void SaveConfig(const char* FILENAME);

	// LoadWordList loads the word list from a file
	void LoadWordList(const char* FILENAME);

	// Train makes a filter from a prime number, and some bases
	// lowBound here is just a parameter
	void Train(int prime, std::vector<int> bases, int lowBound);

	// Predict tests a word and returns the prediction
	bool Predict(std::string word);

	// Asserts that the two BloomClassifiers are equal
	void AssertEqual(const BloomClassifier &oth);

};

#endif // BLOOM_H_