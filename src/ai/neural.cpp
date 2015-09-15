#include "neural.h"

#define RAND_DOUBLE (rand()/(RAND_MAX+1.0)) 

void Neural::mutate()
{
	for (unsigned int i=0; i < _weight.size(); ++i)
	{
		if (RAND_DOUBLE < _mutationRate)
			_weight[i] += (RAND_DOUBLE - RAND_DOUBLE)*_maxPerturbtion;
	}
}

double Neural::Sigmoid(double input, double response)
{
	return (1.0/(1+exp(-input/response)));
}

double Neural::calculate(const std::vector<double>& input)
{
	double netinput = 0;
	unsigned int i = 0;

	for(i = 0; i<_weight.size()-1 && i<input.size(); i++)
		netinput += _weight[i] * input[i];

	netinput += _weight[i]*_bias;
	return Sigmoid(netinput, _activationResponse);
}