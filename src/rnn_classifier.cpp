#include "../include/rnn_classifier.h"
#include <armadillo>
#include <string>

using namespace arma;
using namespace std;

const float RNNClassifier::kLearningRate = 1.0e-1;
const int RNNClassifier::kHiddenSize = 25;


void RNNClassifier::LoadData(const char *FILENAME) {

	int ind = 0;
	for(char c = 'a'; c <= 'z'; ++c)
		charToInt[c] = ind++;
	vocabSize = charToInt.size();

	WXH = randu<mat>(kHiddenSize, vocabSize);
	WHH = randu<mat>(kHiddenSize, kHiddenSize);
	WHY = randu<mat>(vocabSize, kHiddenSize);
	bh = randu<vec>(kHiddenSize);
	by = randu<vec>(vocabSize);
}

float RNNClassifier::ComputeLoss(string word) const {
	vec hs, ys, xs, ps;

	hs.zeros(kHiddenSize);
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
		ps = exp(ys);
		ps /= sum(ps);

		// Update loss
		loss -= log(ps[target]);
	}

	cerr << loss << '\n';
	return loss;
}

bool RNNClassifier::Predict(string word) const {
	return ComputeLoss(word) <= 5;
}