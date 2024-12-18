#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "ElemUniv.h"
#include "Factor.h"
#include "Jakobian.h"
#include "GlobalData.h"

struct MatrixC
{
	vector<vector<vector<double>>> ilustrative_matrixC;
	vector<vector<double>> matrixC;

	MatrixC();

	void addMatrixC(ElemUniv* elem, GlobalData* globalData, Factor* factor, vector<double> detJ);
};