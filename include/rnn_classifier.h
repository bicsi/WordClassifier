#ifndef RNN_CL_H_
#define RNN_CL_H_

#include "model.h"

#include <string>
#include <map>
#include <armadillo>
#include <fstream>

class RNNClassifier : public Model {
	int hiddenSize;
	int vocabSize;
	float treshold;

	std::map<char, int> charToInt;

	arma::mat WXH, WHH, WHY;
	arma::vec bh, by;

	std::ifstream in;

private:
	// Read functions for arma::vec and arma::mat
	void ReadVector(arma::vec &v, int n);
	void ReadMatrix(arma::mat &M, int n, int m);

public:
	// Constructor
	RNNClassifier(float tres) : treshold(tres) {}

	// Loads data from file
	void LoadData(const char* FILENAME);
	// Computes loss of a word as float
	float ComputeLoss(std::string word) const;
	// Predicts a word
	bool Predict(std::string word) const;
};

#endif // RNN_CL_H_