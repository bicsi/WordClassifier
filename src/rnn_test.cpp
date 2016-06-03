#include "../include/rnn_classifier.h"
#include "../include/model_tester.h"

#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, char **argv) {

	double tres = 2.8;
	if(argc >= 2)
		tres = atof(argv[1]);

	RNNClassifier model(tres);	
	ModelTester tester;


	model.LoadData("res/rnn_res");

	// Load test cases from res folder
	tester.LoadTestData("res/words-test.txt");	
	// Test the model on test cases
	tester.TestModel(model);
	// Dump results to stdout
	tester.DumpResults(cout);
	

	return 0;
}