// Model is an abstract class that implements method
// Predict()

#ifndef MODEL_H_
#define MODEL_H_

#include <string>

class Model {
public:
	virtual bool Predict(std::string word) const = 0;
};

#endif