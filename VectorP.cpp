#include "VectorP.h"

void VectorP::addVectorP(int side, double detJ, ElemUniv* elem, GlobalData* globalData, Factor* factor)
{
    for (int i = 0; i < factor->factor.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            vectorP[j] += (elem->boundaryN[side][i][j] * factor->factor[i] * globalData->tot * detJ * globalData->alfa);
        }
    }
}

void VectorP::printVectorP()
{

    for (int i = 0; i < 4; i++)
    {
        cout << vectorP[i] << " ";
    }
    cout << endl;
}
