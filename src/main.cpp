#include "../include/bloom_classifier.h"

using namespace std;

int main() {
	BloomClassifier bloom;

	bloom.LoadWordList("res/wordlist.txt");
	
	return 0;
}