#pragma once
#include "Library.h"

struct Grid
{
    int nodeNumber;
    int elementNumber;
    vector<Node> nodes;
    vector<Element> elements;

    void print_nodes()
    {
        cout << "Nodes:\n";
        for (int i = 0; i < nodeNumber; i++)
        {
            cout << setw(3) << i + 1 << ": " << setw(10) << nodes[i].x << ", " << setw(10) << nodes[i].y << endl;
        }
        cout << endl;
    }

    void print_elements()
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
};
