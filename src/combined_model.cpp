#include "../include/combined_model.h"
#include "../include/bloom_classifier.h"
#include "../include/rnn_classifier.h"

#include <string>

using namespace std;

void CombinedModel::Init(const char* DIRPATH) {
	const string bloom_path = string(DIRPATH) + "/bloom_res";
	const string rnn_path = string(DIRPATH) + "/rnn_res";
	bloom.LoadConfig(bloom_path.c_str());
	rnn.LoadData(rnn_path.c_str());
}

bool CombinedModel::Predict(string word) const {
	if(!bloom.Predict(word)) 
		return false;
	return rnn.Predict(word);
}