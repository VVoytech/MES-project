#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "Grid.h"
#include "Node.h"
#include "Element.h"

using namespace std;

struct Grid
{
    int nodeNumber;
    int elementNumber;
    vector<Node> nodes;
    vector<Element> elements;

    // Method to print nodes
    void print_nodes();

    // Method to print elements
    void print_elements();
};
