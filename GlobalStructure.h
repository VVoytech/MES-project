#pragma once
#include "Grid.h"

using namespace std;

struct GlobalStructure
{
	vector<vector<double>> globalH;
	vector<vector<double>> globalC;
	vector<double> globalP;
	vector<double> globalTemp;

	void makeGlobalHMatrix(GlobalData* globalData, Grid* grid);

	void makeGlobalCMatrix(GlobalData* globalData, Grid* grid);

	void makeGlobalPVector(GlobalData* globalData, Grid* grid);

	void makeGlobalTempVector(GlobalData* globalData, Grid* grid);

	vector<double> addCtoP(GlobalData* globalData);

	vector<vector<double>> addCtoH(GlobalData* globalData);

	void printGlobalHMatrix();

	void printGlobalCMatrix();

	void gauss();

	void printGlobalPVector();

	void printGlobalTemp();

	void printMinMax();
};