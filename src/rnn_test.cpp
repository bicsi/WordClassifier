#include "../include/rnn_classifier.h"

using namespace std;

int main() {
	RNNClassifier model;
	model.LoadData("res/rnn-data.txt");
	model.Predict("apple");

	return 0;
}