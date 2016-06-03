#include <iostream>

#include "../include/combined_model.h"
#include "../include/model_tester.h"
#include "../util/debug.h"

using namespace std;

int main(int argc, char **argv) {

	double tres = 2.8;
	if(argc >= 2)
		tres = atof(argv[1]);

	// Declare model and initialize
	CombinedModel model(tres);
	model.Init("res");

	debug("Testing...\n");

	// Declare tester and test
	ModelTester tester;
	tester.LoadTestData("res/words-test.txt");
	tester.TestModel(model);

	// Dump results to stdout
	tester.DumpResults(cout);

	return 0;
}