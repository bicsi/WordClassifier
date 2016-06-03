#ifndef COMBINED_MODEL_H_
#define COMBINED_MODEL_H_

#include "bloom_classifier.h"
#include "rnn_classifier.h"

#include <string>

class CombinedModel : public Model {
	BloomClassifier bloom;
	RNNClassifier rnn;

public:
	CombinedModel(double tres) : rnn(tres) {}
	void Init(const char* DIRPATH);
	bool Predict(std::string word) const;
};

#endif // COMBINED_MODEL_H_