#include "Grid.h"

void Grid::print_nodes()
{
    cout << "Nodes:\n";
    for (int i = 0; i < nodeNumber; i++)
    {
        cout << setw(3) << i + 1 << ": " << setw(10) << nodes[i].x << ", " << setw(10) << nodes[i].y << "' " << nodes[i].BC << endl;
    }
    cout << endl;
}

void Grid::print_elements()
{
    cout << "Elements:\n";
    for (int i = 0; i < elementNumber; i++)
    {
        cout << setw(3) << i + 1 << ": ";
        for (int j = 0; j < elements[i].nodes.size(); j++)
        {
            cout << setw(3) << elements[i].nodes[j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

void Grid::makeMatrixH(ElemUniv* elem, GlobalData* globalData, Factor* factor)
{
    for (int i = 0; i < elements.size(); i++)
    {
        Node* n1 = new Node;
        Node* n2 = new Node;
        Node* n3 = new Node;
        Node* n4 = new Node;

        n1 = &nodes[elements[i].nodes[0]-1];
        n2 = &nodes[elements[i].nodes[1]-1];
        n3 = &nodes[elements[i].nodes[2]-1];
        n4 = &nodes[elements[i].nodes[3]-1];

        elements[i].jacobian = Jacobian::Jacobian(n1, n2, n3, n4, elem, globalData);
        elements[i].jacobian.dNdXY(elem, globalData);
        elements[i].jacobian.add_matrixH(elem, globalData, factor);
    }
}

void Grid::makeHbc(ElemUniv* elem, GlobalData* globalData, Factor* factor)
{
    double detJ;
    for (int i = 0; i < elements.size(); i++)
    {
        elements[i].jacobian.Hbc.resize(4, vector<double>(4, 0));
        if (nodes[elements[i].nodes[0] - 1].BC == 1 && nodes[elements[i].nodes[1] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[0] - 1].x - nodes[elements[i].nodes[1] - 1].x, 2) + pow(nodes[elements[i].nodes[0] - 1].y - nodes[elements[i].nodes[1] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].jacobian.add_boundary(2, detJ, elem, globalData, factor);
        }

        if (nodes[elements[i].nodes[1] - 1].BC == 1 && nodes[elements[i].nodes[2] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[1] - 1].x - nodes[elements[i].nodes[2] - 1].x, 2) + pow(nodes[elements[i].nodes[1] - 1].y - nodes[elements[i].nodes[2] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].jacobian.add_boundary(3, detJ, elem, globalData, factor);
        }

        if (nodes[elements[i].nodes[2] - 1].BC == 1 && nodes[elements[i].nodes[3] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[2] - 1].x - nodes[elements[i].nodes[3] - 1].x, 2) + pow(nodes[elements[i].nodes[2] - 1].y - nodes[elements[i].nodes[3] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].jacobian.add_boundary(0, detJ, elem, globalData, factor);
        }

        if (nodes[elements[i].nodes[3] - 1].BC == 1 && nodes[elements[i].nodes[0] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[3] - 1].x - nodes[elements[i].nodes[0] - 1].x, 2) + pow(nodes[elements[i].nodes[3] - 1].y - nodes[elements[i].nodes[0] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].jacobian.add_boundary(1, detJ, elem, globalData, factor);
        }
    }
}

void Grid::makeVectorP(ElemUniv* elem, GlobalData* globalData, Factor* factor)
{
    double detJ;
    for (int i = 0; i < elements.size(); i++)
    {
        elements[i].vectorP.vectorP.clear();
        elements[i].vectorP.vectorP.resize(4, 0);
        if (nodes[elements[i].nodes[0] - 1].BC == 1 && nodes[elements[i].nodes[1] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[0] - 1].x - nodes[elements[i].nodes[1] - 1].x, 2) + pow(nodes[elements[i].nodes[0] - 1].y - nodes[elements[i].nodes[1] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].vectorP.addVectorP(2, detJ, elem, globalData, factor);
        }

        if (nodes[elements[i].nodes[1] - 1].BC == 1 && nodes[elements[i].nodes[2] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[1] - 1].x - nodes[elements[i].nodes[2] - 1].x, 2) + pow(nodes[elements[i].nodes[1] - 1].y - nodes[elements[i].nodes[2] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].vectorP.addVectorP(3, detJ, elem, globalData, factor);
        }

        if (nodes[elements[i].nodes[2] - 1].BC == 1 && nodes[elements[i].nodes[3] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[2] - 1].x - nodes[elements[i].nodes[3] - 1].x, 2) + pow(nodes[elements[i].nodes[2] - 1].y - nodes[elements[i].nodes[3] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].vectorP.addVectorP(0, detJ, elem, globalData, factor);
        }

        if (nodes[elements[i].nodes[3] - 1].BC == 1 && nodes[elements[i].nodes[0] - 1].BC == 1)
        {
            detJ = sqrt(pow(nodes[elements[i].nodes[3] - 1].x - nodes[elements[i].nodes[0] - 1].x, 2) + pow(nodes[elements[i].nodes[3] - 1].y - nodes[elements[i].nodes[0] - 1].y, 2)) / 2;
            //cout << detJ << endl;
            elements[i].vectorP.addVectorP(1, detJ, elem, globalData, factor);
        }
    }
}

void Grid::makeMatrixC(ElemUniv* elem, GlobalData* globalData, Factor* factor)
{
    for (int i = 0; i < elements.size(); i++)
    {
        elements[i].matrixC.addMatrixC(elem, globalData, factor, elements[i].jacobian.detJ);
    }
}

void Grid::addHbcTomatrixH()
{
    for (int i = 0; i < elements.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                elements[i].jacobian.matrixH[j][k] = elements[i].jacobian.matrixH[j][k] + elements[i].jacobian.Hbc[j][k];
            }
        }
    }
}

void Grid::printMatrixH()
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << "\nDane dla elementu " << i + 1 << ":\n";
        elements[i].jacobian.print_matirxH();
    }
}

void Grid::printHbc()
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << "\nDane dla elementu " << i + 1 << ":\n";
        elements[i].jacobian.printHbc();
    }
}

void Grid::printVectorP()
{
    for (int i = 0; i < elements.size(); i++)
    {
        cout << "\nDane dla elementu " << i + 1 << ":\n";
        elements[i].vectorP.printVectorP();
    }
}
