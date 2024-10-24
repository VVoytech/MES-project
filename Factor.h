#pragma once
#include "Library.h"

struct Factor
{
	vector<double> node;
	vector<double> factor;

};

void add_factor(Factor* factor1, Factor* factor2, Factor* factor3)
{
	// Jednopunktowy
	factor1->node.push_back(0);
	factor1->factor.push_back(2);

	// Dwupunktowy
	factor2->node.push_back(-(1.0 / sqrt(3.0)));
	factor2->node.push_back(1.0 / sqrt(3.0));
	factor2->factor.push_back(1);
	factor2->factor.push_back(1);

	// Trójpunktowy
	factor3->node.push_back(-(sqrt(3.0 / 5.0)));
	factor3->node.push_back(0);
	factor3->node.push_back(sqrt(3.0 / 5.0));
	factor3->factor.push_back(5.0 / 9.0);
	factor3->factor.push_back(8.0 / 9.0);
	factor3->factor.push_back(5.0 / 9.0);
}