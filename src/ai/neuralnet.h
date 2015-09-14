#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <vector>
#include "neural.h"

class NeuralNet
{
public:
	NeuralNet();

	void   setFitness(double fitness);
	bool   operator<(const NeuralNet& other);
	double fitness();

	std::vector<double>& calculate(const std::vector<double>& input);

private:
	double _fitness;
	std::vector<double> _output;
	std::vector<std::vector<Neural*>> _neurals;
};

inline bool NeuralNet::operator<(const NeuralNet& other)
{
	return _fitness < other._fitness;
}

#endif