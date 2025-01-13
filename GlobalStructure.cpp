#include "GlobalStructure.h"

void GlobalStructure::makeGlobalHMatrix(GlobalData* globalData, Grid* grid)
{
	globalH.clear();
	globalH.resize(globalData->nodeNumber, vector<double>(globalData->nodeNumber, 0));
	for (int k = 0; k < grid->elementNumber; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			vector<double> temp;
			for (int j = 0; j < 4; j++)
			{
				globalH[grid->elements[k].nodes[i] - 1][grid->elements[k].nodes[j] - 1] += grid->elements[k].jacobian.matrixH[i][j];
			}
		}
	}
}

void GlobalStructure::makeGlobalCMatrix(GlobalData* globalData, Grid* grid)
{
	globalC.clear();
	globalC.resize(globalData->nodeNumber, vector<double>(globalData->nodeNumber, 0));
	for (int k = 0; k < grid->elementNumber; k++)
	{
		for (int i = 0; i < 4; i++)
		{
			vector<double> temp;
			for (int j = 0; j < 4; j++)
			{
				globalC[grid->elements[k].nodes[i] - 1][grid->elements[k].nodes[j] - 1] += grid->elements[k].matrixC.matrixC[i][j];
			}
		}
	}
}

void GlobalStructure::makeGlobalPVector(GlobalData* globalData, Grid* grid)
{
	globalP.clear();
	globalP.resize(globalData->nodeNumber, 0);
	for (int i = 0; i < grid->elementNumber; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			globalP[grid->elements[i].nodes[j] - 1] += grid->elements[i].vectorP.vectorP[j];
		}
	}
}

void GlobalStructure::makeGlobalTempVector(GlobalData* globalData, Grid* grid)
{
	globalTemp.resize(globalData->nodeNumber, 0);
	for (int i = 0; i < globalData->nodeNumber; i++)
	{
		globalTemp[i] = grid->nodes[i].temp;
	}
}

vector<double> GlobalStructure::addCtoP(GlobalData* globalData)
{
	vector<double> result(globalP.size(), 0.0);

	for (int i = 0; i < globalC.size(); ++i) {
		for (int j = 0; j < globalC.size(); ++j) {
			result[i] += (globalC[i][j] / globalData->simulationStepTime) * globalTemp[j];
		}
		result[i] += globalP[i];
	}

	return result;
}

vector<vector<double>> GlobalStructure::addCtoH(GlobalData* globalData)
{
	vector<vector<double>> result(globalH.size(), vector<double>(globalH.size(), 0));

	for (int i = 0; i < globalH.size(); i++)
	{
		for (int j = 0; j < globalH.size(); j++)
		{
			result[i][j] = globalH[i][j] + (globalC[i][j] / globalData->simulationStepTime);
		}
	}

	return result;
}

void GlobalStructure::gauss()
{
	vector<vector<double>> tempH = globalH;
	vector<double> tempP = globalP;
	globalTemp.resize(globalP.size(), 0);
	for (int k = 0; k < globalH.size() - 1; k++)
	{
		for (int i = k + 1; i < tempH.size(); i++)
		{
			double m = tempH[i][k] / tempH[k][k];
			// cout << m << endl;
			for (int j = 0; j < tempH.size(); j++)
			{
				tempH[i][j] = tempH[i][j] - tempH[k][j] * m;
			}
			tempP[i] = tempP[i] - tempP[k] * m;
		}
	}


	for (int i = tempH.size() - 1; i >= 0; i--)
	{

		globalTemp[i] = tempP[i] / tempH[i][i];

		for (int j = i - 1; j >= 0; j--)
		{
			tempP[j] -= tempH[j][i] * globalTemp[i];
			tempH[j][i] = 0;
		}
	}
}

void GlobalStructure::printGlobalHMatrix()
{
	cout << "\nGlobalna macierz H\n";
	for (int i = 0; i < globalH.size(); i++)
	{
		for (int j = 0; j < globalH.size(); j++)
		{
			cout/* << setw(6)*/ << setprecision(4) << globalH[i][j] << "  ";
		}
		cout << endl;
	}
}

void GlobalStructure::printGlobalCMatrix()
{
	cout << "\nGlobalna macierz C\n";
	for (int i = 0; i < globalC.size(); i++)
	{
		for (int j = 0; j < globalC.size(); j++)
		{
			cout/* << setw(6)*/ << setprecision(4) << globalC[i][j] << "  ";
		}
		cout << endl;
	}
}

void GlobalStructure::printGlobalPVector()
{
	cout << "\nGlobalny wektor P\n";
	for (int i = 0; i < globalP.size(); i++)
	{
		cout << setprecision(11) << globalP[i] << "\n";
	}
	cout << endl;
}

void GlobalStructure::printGlobalTemp()
{
	cout << "\nGlobalne temperatury:\n";
	for (int i = 0; i < globalTemp.size(); i++)
	{
		cout << "wezel [" << i + 1 << "] = " << globalTemp[i] << "\370C\n";
	}
	cout << endl;
}

void GlobalStructure::printMinMax()
{
	double min = globalTemp[0];
	double max = globalTemp[0];
	cout << "\nmin i max: ";
	for (int i = 0; i < globalTemp.size(); i++)
	{
		if (globalTemp[i] < min) min = globalTemp[i];
		if (globalTemp[i] > max) max = globalTemp[i];
	}
	cout << setw(7) << min << "  " << setw(7) << max << "\n";
}

