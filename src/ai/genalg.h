#ifndef GEN_ALG_H
#define GEN_ALG_H

#include <vector>
#include "neural.h"

class GenAlg
{
public:
	GenAlg();

	void Epoch();
private:
	void crossover(const std::vector<double>& mum, const std::vector<double>& dad, 
		std::vector<double> &baby1, std::vector<double>& baby2);

};

#endif