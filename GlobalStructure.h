#pragma once
#include "Grid.h"

using namespace std;

struct GlobalStructure
{
	vector<vector<double>> globalH;
	vector<double> globalP;
	vector<double> globalTemp;

	void makeGlobalHMatrix(GlobalData* globalData, Grid* grid);

	void makeGlobalPVector(GlobalData* globalData, Grid* grid);

	void printGlobalHMatrix();

	void gauss();

	void printGlobalPVector();

	void printGlobalTemp();
};