// Implementation of ModelTester

#include "../include/model_tester.h"
#include "../include/model.h"

#include <vector>
#include <fstream>
#include <string>

using namespace std;

void ModelTester::LoadTestData(const char *FILENAME) {
	ifstream in(FILENAME);
	string word, value;

	testData.clear();
	while(in >> word >> value) {
		testData.emplace_back(word, value == "True");
	}
}

void ModelTester::TestModel(const Model &model) {
	
	correctCount = totalCount = 0;
	falsePosCount = falseNegCount = 0;

	for(auto test : testData) {
		bool correctResult = test.second;
		bool modelResult = model.Predict(test.first);

		if(correctResult == modelResult)
			correctCount += 1;
		else {
			if(modelResult == true) falsePosCount += 1;
			else falseNegCount += 1;
		}

		totalCount += 1;
	}

	accuracy = 1.0 * correctCount / totalCount;
}

void ModelTester::DumpResults(ostream &out) {
	out << "Current results: " << endl;
	out << "Accuracy: " << accuracy;
	out << "(" << correctCount << "/" << totalCount << 
	        ")" << endl;
	out << "False positives: " << falsePosCount << endl;
	out << "False negatives: " << falseNegCount << endl;
	out << endl;
}