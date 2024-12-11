#include "GlobalStructure.h"

void GlobalHMatrix::makeGlobalHMatrix(GlobalData* globalData, Grid* grid)
{
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

void GlobalHMatrix::makeGlobalPVector(GlobalData* globalData, Grid* grid)
{
	globalP.resize(globalData->nodeNumber, 0);
	for (int i = 0; i < grid->elementNumber; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			globalP[grid->elements[i].nodes[j] - 1] += grid->elements[i].vectorP.vectorP[j];
		}
	}
}

void GlobalHMatrix::gauss()
{
	for (int k = 0; k < globalH.size() - 1; k++)
	{
		for (int i = k + 1; i < globalH.size(); i++)
		{
			double m = globalH[i][k] / globalH[k][k];
			// cout << m << endl;
			for (int j = 0; j < globalH.size(); j++)
			{
				globalH[i][j] = globalH[i][j] - globalH[k][j] * m;
			}
			globalP[i] = globalP[i] - globalP[k] * m;
		}
	}


	for (int i = globalH.size() - 1; i >= 0; i--)
	{

		double x = globalP[i] / globalH[i][i];

		cout << x << endl;

		for (int j = i - 1; j >= 0; j--)
		{
			globalP[j] -= globalH[j][i] * x;
			globalH[j][i] = 0;
		}
	}
}

void GlobalHMatrix::printGlobalHMatrix()
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

void GlobalHMatrix::printGlobalPVector()
{
	cout << "\nGlobalny wektor P\n";
	for (int i = 0; i < globalP.size(); i++)
	{
		cout << setprecision(11) << globalP[i] << "\n";
	}
	cout << endl;
}

