#ifndef NEURAL_H
#define NEURAL_H

#include <vector>
#include <stdlib.h>

class Neural
{
public:
	void mutate();
	double calculate(const std::vector<double>& input);

private:
	static double Sigmoid(double input, double response);

	std::vector<double> _weight;

	double _bias;
	double _activationResponse;
	double _mutationRate;
	double _maxPerturbtion;
};

#endif