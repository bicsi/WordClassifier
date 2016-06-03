#ifndef RNN_CL_H_
#define RNN_CL_H_

#include "model.h"

#include <string>
#include <map>
#include <armadillo>

class RNNClassifier : public Model {
	const static float kLearningRate;
	const static int kHiddenSize;
	int vocabSize;

	std::map<int, int> charToInt;

	arma::mat WXH, WHH, WHY;
	arma::vec bh, by;

public:
	void LoadData(const char* FILENAME);
	float ComputeLoss(std::string word) const;
	bool Predict(std::string word) const;
};

#endif // RNN_CL_H_