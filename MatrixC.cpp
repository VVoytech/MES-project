#include "MatrixC.h"

MatrixC::MatrixC()
{
}

void MatrixC::addMatrixC(ElemUniv* elem, GlobalData* globalData, Factor* factor, vector<double> detJ)
{
    ilustrative_matrixC.clear();
    matrixC.clear();
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
                temp.push_back(globalData->specificHeat * globalData->density * (elem->N[i][k] * elem->N[i][j]) * detJ[i]);
            }
            temp2D.push_back(temp);
        }
        ilustrative_matrixC.push_back(temp2D);
    }

    matrixC.resize(4, vector<double>(4, 0));
    for (int i = 0; i < globalData->npc; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                matrixC[j][k] += (ilustrative_matrixC[i][j][k] * factor->factor[x] * factor->factor[y]);
            }
        }
        if (p)
        {
            if (x < factor->node.size() - 1)
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
    }
}

void MatrixC::print_matirxc()
{
    cout << "\nMacierz C:\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(7) << matrixC[i][j] << " ";
        }
        cout << endl;
    }
}
