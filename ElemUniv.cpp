#include "ElemUniv.h"

// Tworzenie wartoœci tabeli dNi/dKsi oraz dNi/dEta
void ElemUniv::newElemUniv(int npc, Factor* factor)
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
