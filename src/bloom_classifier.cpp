// Implementation of BloomClassifier

#include "../include/bloom_classifier.h"
#include "../util/debug.h"

using namespace std;

int BloomClassifier::HashFun(int old_h, string word, int base, int prime) {
	h = 0;
	for(auto c : word)
		h = (1LL * h * base + c) % prime;
	return h;
}

void BloomClassifier::LoadConfig(const char* FILENAME) {
	debug("Loading from file...\n");

	ifstream in(FILENAME);

	debug("Loaded!\n");
}

void BloomClassifier::SaveConfig(const char* FILENAME) {
	debug("Saving to file...\n");
	
	ofstream out(FILENAME);

	char x = 0;

	out << prime << ' ' << bases.size() << ' ';
   	for(auto base : bases) 
   		out << base << ' ';

	for(int i = 0; i < prime; ++i) {
		if(bloomFilter[i].size())
			x |= (1 << (i % 8));
		
		if(i % 8 == 7) {
			out << x;
			x = 0;
		}
	}
	out << x;

	out.close();

	debug("Saved!\n");
}

void BloomClassifier::LoadWordList(const char* FILENAME) {
	debug("Loading word list...\n");

	ifstream in(FILENAME);

	while(in >> word) {
		words.push_back(word);
	}

	debug("Loaded!\n");
}

void BloomClassifier::AddWords() {
	debug("Processing words...\n");

	// Resize bloom filter
	bloomFilter.resize(words.size());

	// Add each word with each hash function
	for(int i = 0; i < words.size(); ++i) {
		int h = 0;
		for(auto base : bases) {
			h = HashFun(h, words[i], base, prime);
			bloomFilter[h].push_back(i);
		}
	}
}

void BloomClassifier::PruneFilter() {
	debug("Pruning...\n");


	// Use a min-heap sorted by sizes in filter
	std::priority_queue<pair<int, int>> Q;
	for(int i = 0; i < prime; ++i)
		if(bloomFilter[i].size() <= lowBound)
			Q.emplace(-bloomFilter[i].size(), -i);

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
				debug("Removed too many words!\n");
				bloomFilter.clear();
				return;
			}
			
			// Prune all words that hash to top
			int h = 0;
			for(auto base : bases) {
				h = hash_fun(h, words[now], base, prime);
				auto it = find(bloomFilter[h].begin(), bloomFilter[h].end(), now);
				assert(it != bloomFilter[h].end());

				bloomFilter[h].erase(it);
				if(bloomFilter[h].size() <= lowBound)
					Q.emplace(-bloomFilter[h].size(), -h);
			}
		}
	}

	debug("Removed %d items!\n", remCount);
}

void BloomClassifier::Train(int prime, vector<int> bases, int lowBound = 1) {
	//ClearAll();

	this->prime = prime;
	this->bases = bases;
	this->lowBound = lowBound;

	debug("Current prime: %d\n", prime);
	debug("Current bases: ");
	for(auto base : bases)
		debug("%d ", base);
	debug("\n");


	AddWords();
	Prune();

	debug("Done training!\n");
}

bool BloomClassifier::Predict(string word) {
	int h = 0;
	for(auto base : bases) {
		h = HashFun(h, word, base, prime);
		if(bloomFilter[h].empty())
			return false;
	}
	return true;
}

