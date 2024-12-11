#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "ElemUniv.h"
#include "Factor.h"
#include "GlobalData.h"

using namespace std;

struct VectorP
{
	vector<double> vectorP;

	void addVectorP(int side, double detJ, ElemUniv* elem, GlobalData* globalData, Factor* factor);

	void printVectorP();
};