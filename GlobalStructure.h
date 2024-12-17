#pragma once
#include "Grid.h"

using namespace std;

struct GlobalHMatrix
{
	vector<vector<double>> globalH;
	vector<double> globalP;

	void makeGlobalHMatrix(GlobalData* globalData, Grid* grid);

	void makeGlobalPVector(GlobalData* globalData, Grid* grid);

	void printGlobalHMatrix();

	void gauss();

	void printGlobalPVector();
};