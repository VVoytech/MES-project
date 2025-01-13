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

    void print_nodes();

    void print_elements();

    void makeMatrixH(ElemUniv* elem, GlobalData* globalData, Factor* factor);

    void makeHbc(ElemUniv* elem, GlobalData* globalData, Factor* factor);

    void makeVectorP(ElemUniv* elem, GlobalData* globalData, Factor* factor);

    void makeMatrixC(ElemUniv* elem, GlobalData* globalData, Factor* factor);

    void addHbcTomatrixH();

    void printMatrixH();

    void printHbc();

    void printVectorP();

    void printMatrixC();
};
