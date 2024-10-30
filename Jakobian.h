#pragma once
#include "Library.h"

struct Jacobian
{
	vector<vector<vector<double>>> J;
	vector<vector<vector<double>>> J_invert;
	vector<double> detJ;

	vector<vector<double>> dNdX;
	vector<vector<double>> dNdY;
	vector<vector<vector<double>>> ilustrative_matrixH;
	vector<vector<double>> matrixH;


	Jacobian(Node* n1, Node* n2, Node* n3, Node* n4, ElemUniv* elem, GlobalData* globalData);

	void dNdXY(ElemUniv* elem, GlobalData* globalData)
	{
		for (int i = 0; i < globalData->npc; i++)
		{
			vector<double> temp;
			temp.push_back(J_invert[i][0][0] * elem->ksi[i][0] + J_invert[i][0][1] * elem->eta[i][0]);
			temp.push_back(J_invert[i][0][0] * elem->ksi[i][1] + J_invert[i][0][1] * elem->eta[i][1]);
			temp.push_back(J_invert[i][0][0] * elem->ksi[i][2] + J_invert[i][0][1] * elem->eta[i][2]);
			temp.push_back(J_invert[i][0][0] * elem->ksi[i][3] + J_invert[i][0][1] * elem->eta[i][3]);
			dNdX.push_back(temp);
			temp.erase(temp.begin(), temp.end());

			temp.push_back(J_invert[i][1][0] * elem->ksi[i][0] + J_invert[i][1][1] * elem->eta[i][0]);
			temp.push_back(J_invert[i][1][0] * elem->ksi[i][1] + J_invert[i][1][1] * elem->eta[i][1]);
			temp.push_back(J_invert[i][1][0] * elem->ksi[i][2] + J_invert[i][1][1] * elem->eta[i][2]);
			temp.push_back(J_invert[i][1][0] * elem->ksi[i][3] + J_invert[i][1][1] * elem->eta[i][3]);
			dNdY.push_back(temp);
		}

	}

	void add_matrixH(ElemUniv* elem, GlobalData* globalData, Factor* factor)
	{
		int x, y;
		x = y = 0;
		bool p = true;
		for (int i = 0; i < globalData->npc; i++)
		{
			vector<vector<double>> temp2D;
			for (int k = 0; k < 4; k++)
			{
				vector<double> temp;
				for (int j = 0; j < 4; j++)
				{
					temp.push_back(globalData->conductivity * detJ[i] * ((dNdX[i][k] * dNdX[i][j]) + dNdY[i][k] * dNdY[i][j]) * factor->factor[x] * factor->factor[y]);
				}
				temp2D.push_back(temp);
			}
			if (p)
			{
				if (x < factor->factor.size() - 1)
				{
					x++;
				}
				else
				{
					y++;
					p = false;
				}
			}
			else
			{
				if (x > 0)
				{
					x--;
				}
				else
				{
					y++;
					p = true;
				}
			}
			ilustrative_matrixH.push_back(temp2D);
		}

		for (int i = 0; i < 4; i++)
		{
			vector<double> temp;
			for (int j = 0; j < 4; j++)
			{
				temp.push_back(0);
			}
			matrixH.push_back(temp);
		}
		
		for (int i = 0; i < globalData->npc; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					matrixH[j][k] += ilustrative_matrixH[i][j][k];
				}
			}
		}
	}

	void printData()
	{
		for (int i = 0; i < J.size(); i++)
		{
			cout << "Macierz Jacobiego dla pc" << i + 1 << endl << setw(6) << J[i][0][0] << ", " << setw(6) << J[i][0][1] << endl << setw(6) << J[i][1][0] << ", " << setw(6) << J[i][1][1] << "\n\n";
		}
		for (int i = 0; i < J.size(); i++)
		{
			cout << "Wyznacznik macierzy dla pc" << i + 1 << ": " << detJ[i] << "\n";
		}
		for (int i = 0; i < J.size(); i++)
		{
			cout << "\nMacierz odwrotna dla pc" << i + 1 << endl << setw(6) << J_invert[i][0][0] << ", " << setw(6) << J_invert[i][0][1] << endl << setw(6) << J_invert[i][1][0] << ", " << setw(6) << J_invert[i][1][1];
		}
		cout << endl;
	}

	void print_dNdXY()
	{
		cout << "\ndNi/dX\n";
		for (int i = 0; i < dNdX.size(); i++)
		{
			cout << "pc" << i + 1 << ": " << setw(7) << dNdX[i][0] << " " << setw(7) << dNdX[i][1] << " " << setw(7) << dNdX[i][2] << " " << setw(7) << dNdX[i][3] << endl;
		}

		cout << "\ndNi/dY\n";
		for (int i = 0; i < dNdY.size(); i++)
		{
			cout << "pc" << i + 1 << ": " << setw(7) << dNdY[i][0] << " " << setw(7) << dNdY[i][1] << " " << setw(7) << dNdY[i][2] << " " << setw(7) << dNdY[i][3] << endl;
		}
	}

	void print_matirxH()
	{
		cout << "\nMacierze H w punktach calkowania:\n";
		for (int i = 0; i < ilustrative_matrixH.size(); i++)
		{
			cout << "pc" << i + 1 << ":\n";
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					cout << setw(8) << ilustrative_matrixH[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << "\nMacierz H:\n";
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << setw(7) << matrixH[i][j] << " ";
			}
			cout << endl;
		}
	}
};

Jacobian::Jacobian(Node* n1, Node* n2, Node* n3, Node* n4, ElemUniv* elem, GlobalData* globalData)
{
	for (int i = 0; i < globalData->npc; i++)
	{
		vector<double> temp;
		vector<vector<double>> temp2D;
		temp.push_back((elem->ksi[i][0] * n1->x) + (elem->ksi[i][1] * n2->x) + (elem->ksi[i][2] * n3->x) + (elem->ksi[i][3] * n4->x));
		temp.push_back((elem->ksi[i][0] * n1->y) + (elem->ksi[i][1] * n2->y) + (elem->ksi[i][2] * n3->y) + (elem->ksi[i][3] * n4->y));
		temp2D.push_back(temp);
		temp.erase(temp.begin(), temp.end());

		temp.push_back((elem->eta[i][0] * n1->x) + (elem->eta[i][1] * n2->x) + (elem->eta[i][2] * n3->x) + (elem->eta[i][3] * n4->x));
		temp.push_back((elem->eta[i][0] * n1->y) + (elem->eta[i][1] * n2->y) + (elem->eta[i][2] * n3->y) + (elem->eta[i][3] * n4->y));
		temp2D.push_back(temp);
		temp.erase(temp.begin(), temp.end());
		J.push_back(temp2D);
	}

	for (int i = 0; i < globalData->npc; i++)
	{
		detJ.push_back(J[i][0][0] * J[i][1][1] - J[i][0][1] * J[i][1][0]);
	}

	for (int i = 0; i < globalData->npc; i++)
	{
		vector<double> temp;
		vector<vector<double>> temp2D;
		temp.push_back(J[i][1][1] * (1 / detJ[i]));
		temp.push_back(-(J[i][0][1] * (1 / detJ[i])));
		temp2D.push_back(temp);
		temp.erase(temp.begin(), temp.end());

		temp.push_back(-(J[i][1][0] * (1 / detJ[i])));
		temp.push_back(J[i][0][0] * (1 / detJ[i]));
		temp2D.push_back(temp);
		J_invert.push_back(temp2D);
	}

}