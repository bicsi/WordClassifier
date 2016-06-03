// Declaration of ModelTester

#ifndef MODEL_TESTER_H_
#define MODEL_TESTER_H_

#include "model.h"

#include <vector>
#include <string>

class ModelTester {

	std::vector<std::pair<std::string, bool>> testData;

public:

	double accuracy;
	int correctCount, totalCount;
	int falsePosCount, falseNegCount;

	// Dumps results to console
	void DumpResults(std::ostream &out);

	// Loads the test data from file
	void LoadTestData(const char *FILENAME);

	// Tests a model
	void TestModel(const Model &model);

};

#endif // MODEL_TESTER_H_