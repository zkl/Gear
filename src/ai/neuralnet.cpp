#include "neuralnet.h"

NeuralNet::NeuralNet() : 
	_fitness(0.0)
{
}

std::vector<double>& NeuralNet::calculate(const std::vector<double>& input)
{
	_output = input;
	std::vector<double> inputOutput;
	for (unsigned int i=0; i<_neurals.size(); i++)
	{		
		inputOutput = _output;
		_output.clear();
		
		for (unsigned int j=0; j<_neurals[i].size(); ++j)
		{
			double netinput = _neurals[i][j]->calculate(inputOutput);
			_output.push_back(netinput);
		}
	}

	return _output;
}

void NeuralNet::setFitness(double fitness)
{
	_fitness = fitness;
}

double NeuralNet::fitness()
{
	return _fitness;
}