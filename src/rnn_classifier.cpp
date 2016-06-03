#include "../include/rnn_classifier.h"
#include "../util/debug.h"

#include <armadillo>
#include <string>
#include <fstream>

using namespace arma;
using namespace std;


void RNNClassifier::ReadMatrix(mat &M, int n, int m) {
	M.zeros(n, m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			in >> M(i, j);
}

void RNNClassifier::ReadVector(vec &v, int n) {
	v.zeros(n);
	for(int i = 0; i < n; ++i)
		in >> v(i);
}

void RNNClassifier::LoadData(const char *FILENAME) {
	debug("[RNN] Loading data...\n");
	// Open stream
	in = ifstream(FILENAME);

	// Read parameters and build charToInt[]
	in >> hiddenSize >> vocabSize;
	for(int i = 0; i < vocabSize; ++i) {
		char ch;
		in >> ch;
		charToInt[ch] = i;
	}

	// Read matrices
	ReadMatrix(WXH, hiddenSize, vocabSize);
	ReadMatrix(WHH, hiddenSize, hiddenSize);
	ReadMatrix(WHY, vocabSize, hiddenSize);
	ReadVector(bh, hiddenSize);
	ReadVector(by, vocabSize);

	// Close stream
	in.close();
	debug("[RNN] Loaded!\n");
}

float RNNClassifier::ComputeLoss(string word) const {
	vec hs, ys, xs, ps;

	// Initialize memory and loss
	hs.zeros(hiddenSize);
	float loss = 0;

	for(size_t i = 0; i < word.length() - 1; ++i) {
		int input = charToInt.at(word[i]);
		int target = charToInt.at(word[i + 1]);

		// Make xs
		xs.zeros(vocabSize);
		xs[input] = 1;

		// Update hidden state probs
		hs = tanh(WXH * xs + WHH * hs + bh);
		// Update class probs (unnormalized)
		ys = WHY * hs;
		// Update probabilities
		ps = exp(ys); ps /= sum(ps);

		// Update loss
		loss -= log(ps[target]);
	}

	return loss;
}

bool RNNClassifier::Predict(string word) const {
	return ComputeLoss(word) / (word.length() - 1) <= treshold;
}