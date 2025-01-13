#include "ElemUniv.h"

// Tworzenie wartoœci tabeli dNi/dKsi oraz dNi/dEta
void ElemUniv::newElemUniv(int npc, Factor* factor, GlobalData* globalData)
{
    for (int i = 0; i < factor->node.size(); i++)
    {
        for (int j = 0; j < factor->node.size(); j++)
        {
            vector<double> ksiTemp;
            ksiTemp.push_back(-0.25 * (1 - factor->node[i]));
            ksiTemp.push_back(0.25 * (1 - factor->node[i]));
            ksiTemp.push_back(0.25 * (1 + factor->node[i]));
            ksiTemp.push_back(-0.25 * (1 + factor->node[i]));
            ksi.push_back(ksiTemp);
        }

        for (int j = 0; j < factor->node.size(); j++)
        {
            vector<double> etaTemp;
            etaTemp.push_back(-0.25 * (1 - factor->node[j]));
            etaTemp.push_back(-0.25 * (1 + factor->node[j]));
            etaTemp.push_back(0.25 * (1 + factor->node[j]));
            etaTemp.push_back(0.25 * (1 - factor->node[j]));
            eta.push_back(etaTemp);
        }
    }
    boundaryN.resize(4, std::vector<std::vector<double>>(factor->node.size(), std::vector<double>(4, 0.0)));

    for (int i = factor->node.size() - 1; i >= 0; i--)
    {
        //Górna œciana
        boundaryN[0][factor->node.size() - 1 - i][0] = 0.25 * (1 - factor->node[i]) * (1 - 1);
        boundaryN[0][factor->node.size() - 1 - i][1] = 0.25 * (1 + factor->node[i]) * (1 - 1);
        boundaryN[0][factor->node.size() - 1 - i][2] = 0.25 * (1 + factor->node[i]) * (1 + 1);
        boundaryN[0][factor->node.size() - 1 - i][3] = 0.25 * (1 - factor->node[i]) * (1 + 1);

        //Lewa œciana
        boundaryN[1][factor->node.size() - 1 - i][0] = 0.25 * (1 - (-1)) * (1 - factor->node[i]);
        boundaryN[1][factor->node.size() - 1 - i][1] = 0.25 * (1 + (-1)) * (1 - factor->node[i]);
        boundaryN[1][factor->node.size() - 1 - i][2] = 0.25 * (1 + (-1)) * (1 + factor->node[i]);
        boundaryN[1][factor->node.size() - 1 - i][3] = 0.25 * (1 - (-1)) * (1 + factor->node[i]);

        //Dolna œciana
        boundaryN[2][factor->node.size() - 1 - i][0] = 0.25 * (1 - factor->node[factor->node.size() - 1 - i]) * (1 - (-1));
        boundaryN[2][factor->node.size() - 1 - i][1] = 0.25 * (1 + factor->node[factor->node.size() - 1 - i]) * (1 - (-1));
        boundaryN[2][factor->node.size() - 1 - i][2] = 0.25 * (1 + factor->node[factor->node.size() - 1 - i]) * (1 + (-1));
        boundaryN[2][factor->node.size() - 1 - i][3] = 0.25 * (1 - factor->node[factor->node.size() - 1 - i]) * (1 + (-1));

        //Prawa œciana
        boundaryN[3][factor->node.size() - 1 - i][0] = 0.25 * (1 - 1) * (1 - factor->node[factor->node.size() - 1 - i]);
        boundaryN[3][factor->node.size() - 1 - i][1] = 0.25 * (1 + 1) * (1 - factor->node[factor->node.size() - 1 - i]);
        boundaryN[3][factor->node.size() - 1 - i][2] = 0.25 * (1 + 1) * (1 + factor->node[factor->node.size() - 1 - i]);
        boundaryN[3][factor->node.size() - 1 - i][3] = 0.25 * (1 - 1) * (1 + factor->node[factor->node.size() - 1 - i]);
    }

    int x, y;
    x = y = 0;
    bool p = true;
    for (int i = 0; i < globalData->npc; i++)
    {
        y = i / (globalData->npc / sqrt(globalData->npc));
        x = i % (globalData->npc / static_cast<int>(sqrt(globalData->npc)));

        vector<double> NTemp;
        NTemp.push_back(0.25 * (1 - factor->node[x]) * (1 - factor->node[y]));
        NTemp.push_back(0.25 * (1 + factor->node[x]) * (1 - factor->node[y]));
        NTemp.push_back(0.25 * (1 + factor->node[x]) * (1 + factor->node[y]));
        NTemp.push_back(0.25 * (1 - factor->node[x]) * (1 + factor->node[y]));
        N.push_back(NTemp);
    }
}

// Wypisywanie wartoœci tabeli dNi/dKsi oraz dNi/dEta
void ElemUniv::print_KsiEta()
{
    cout << "Ksi\n\n";
    for (int i = 0; i < ksi.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(6) << ksi[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Eta\n\n";
    for (int i = 0; i < eta.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(6) << eta[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void ElemUniv::print_BoundaryN()
{
    cout << "Funkcje ksztaltu na krawedziach:\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < boundaryN[i].size(); j++)
        {
            for (int k = 0; k < 4; k++)
            {
                cout << boundaryN[i][j][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
}

void ElemUniv::print_N()
{
    cout << "Funkcje ksztaltu\n\n";
    for (int i = 0; i < N.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(6) << N[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
