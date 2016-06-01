// Implementation of BloomClassifier

#include "../include/bloom_classifier.h"
#include "../util/debug.h"

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

	bloomFilter.resize(prime);

	ifstream in("words.txt");
	debug("Adding words to bloom filter...\n");

	string word;
	while(in >> word) 
		words.push_back(word);
	vector<bool> deleted(words.size());
	in.close();

	for(int i = 0; i < words.size(); ++i) {
		int h = 0;
		for(auto base : bases) {
			h = hash_fun(h, words[i], base, prime);
			bloomFilter[h].push_back(i);
		}
	}

	debug("Pruning bloom filter...\n");

	std::priority_queue<pair<int, int>> Q;
	for(int i = 0; i < prime; ++i)
		if(bloomFilter[i].size() <= lowBound)
			Q.emplace(-bloomFilter[i].size(), -i);

	int remCount = 0;
	while(!Q.empty()) {
		int top = -Q.top().second;
		Q.pop();

		for(auto now : bloomFilter[top]) {
	
			if(deleted[now]) continue;
			deleted[now] = 1;
			++remCount;

			if(remCount >= 210000) {
				debug("Removed too many words!\n");
				bloomFilter.clear();
				return;
			}
		
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

bool Predict(string word) {
	int h = 0;
	for(auto base : bases) {
		h = HashFun(h, word, base, prime);
		if(bloomFilter[h].empty())
			return false;
	}
	return true;
}

