// Implementation of BloomClassifier

#include "../include/bloom_classifier.h"
#include "../util/debug.h"

#include <fstream>
#include <queue>
#include <cassert>
#include <algorithm>

using namespace std;

int BloomClassifier::HashFun(int old_h, string word, int base, int prime) const {
	int h = 0;
	for(auto c : word)
		h = (1LL * h * base + c) % prime;
	return h;
}

void BloomClassifier::LoadConfig(const char* FILENAME) {
	debug("[BLOOM] Loading from file...\n");

	ifstream in(FILENAME);

	int countBases, base;
	in >> prime >> countBases;

	bases.clear();
	while(countBases--) {
		in >> base;
		bases.push_back(base);
	}

	bloomFilter.clear();
	bloomFilter.resize(prime + 8);

	for(int byte = 0; byte < prime; byte += 8) {
		char mask;
		in >> mask;

		for(int bit = 0; bit < 8; ++bit)
			if(mask & (1 << bit))
				bloomFilter[byte + bit].push_back(1);
	}

	bloomFilter.resize(prime);

	in.close();

	debug("[BLOOM] Loaded!\n\n");
}

void BloomClassifier::AssertEqual(const BloomClassifier &oth) {
	assert(prime == oth.prime);
	assert(bases == oth.bases);

	for(int i = 0; i < prime; ++i)
		assert((bloomFilter[i].size() == 0) == 
				(oth.bloomFilter[i].size() == 0));

	debug("[BLOOM] The two classifiers are identical!\n");
}

void BloomClassifier::SaveConfig(const char* FILENAME) {
	debug("[BLOOM] Saving to file...\n");
	
	ofstream out(FILENAME);

	out << prime << ' ' << bases.size() << ' ';
   	for(auto base : bases) 
   		out << base << ' ';

   	bloomFilter.resize(prime + 8);
	for(int byte = 0; byte < prime; byte += 8) {
		char mask = 0;
		for(int bit = 0; bit < 8; ++bit)
			if(bloomFilter[byte + bit].size())
				mask |= (1 << bit);
		out << mask;
	}
	bloomFilter.resize(prime);

	out.close();

	debug("[BLOOM] Saved!\n\n");
}

void BloomClassifier::LoadWordList(const char* FILENAME) {
	debug("[BLOOM] Loading word list...\n");

	ifstream in(FILENAME);

	string word;
	while(in >> word) {
		words.push_back(word);
	}

	debug("[BLOOM] Loaded %d words!\n\n", (int)words.size());
}

void BloomClassifier::AddWords() {
	debug("[BLOOM] Processing words...\n\n");

	// Resize bloom filter
	bloomFilter.clear();
	bloomFilter.resize(prime);

	// Add each word with each hash function
	for(size_t i = 0; i < words.size(); ++i) {
		int h = 0;
		for(auto base : bases) {
			h = HashFun(h, words[i], base, prime);
			bloomFilter[h].push_back(i);
		}
	}
}

void BloomClassifier::PruneFilter() {
	debug("[BLOOM] Pruning...\n\n");

	// Use a min-heap sorted by sizes in filter
	priority_queue<pair<int, int>> Q;
	for(int i = 0; i < prime; ++i)
		if((int)bloomFilter[i].size() <= lowBound)
			Q.emplace(-bloomFilter[i].size(), -i);

	// Assign deleted array for not duplicating deletions
	vector<bool> deleted(words.size(), 0);

	// Prune
	int remCount = 0;
	while(!Q.empty()) {
		int top = -Q.top().second;
		Q.pop();

		for(auto now : bloomFilter[top]) {
	
			if(deleted[now]) continue;
			deleted[now] = 1;
			++remCount;

			// Added upper bound check
			if(remCount >= 210000) {
				debug("[BLOOM] Removed too many words!\n\n");
				return;
			}
			
			// Prune all words that hash to top
			int h = 0;
			for(auto base : bases) {
				h = HashFun(h, words[now], base, prime);
				auto it = find(bloomFilter[h].begin(), bloomFilter[h].end(), now);
				assert(it != bloomFilter[h].end());

				bloomFilter[h].erase(it);
				if((int)bloomFilter[h].size() <= lowBound)
					Q.emplace(-bloomFilter[h].size(), -h);
			}
		}
	}

	debug("[BLOOM] Removed %d items!\n\n", remCount);
}

void BloomClassifier::Train(int prime, vector<int> bases, int lowBound = 1) {
	//ClearAll();

	this->prime = prime;
	this->bases = bases;
	this->lowBound = lowBound;

	debug("[BLOOM] Current prime: %d\n", prime);
	debug("[BLOOM] Current bases: ");
	for(auto base : bases)
		debug("%d ", base);
	debug("\n");


	AddWords();
	PruneFilter();

	// Done!
}

bool BloomClassifier::Predict(string word) const {
	int h = 0;
	for(auto base : bases) {
		h = HashFun(h, word, base, prime);
		if(bloomFilter[h].empty())
			return false;
	}
	return true;
}

