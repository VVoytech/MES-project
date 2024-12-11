#pragma once
#include <iostream>
#include <vector>
#include "Node.h"
#include "ElemUniv.h"
#include "Factor.h"
#include "GlobalData.h"

using namespace std;

struct Jacobian
{
    vector<vector<vector<double>>> J;
    vector<vector<vector<double>>> J_invert;
    vector<double> detJ;

    vector<vector<double>> dNdX;
    vector<vector<double>> dNdY;
    vector<vector<vector<double>>> ilustrative_matrixH;
    vector<vector<double>> matrixH;
    vector<vector<double>> Hbc;

    Jacobian();

    Jacobian(Node* n1, Node* n2, Node* n3, Node* n4, ElemUniv* elem, GlobalData* globalData);

    void dNdXY(ElemUniv* elem, GlobalData* globalData);
    void add_matrixH(ElemUniv* elem, GlobalData* globalData, Factor* factor);
    void add_boundary(int side, double detJ, ElemUniv* elem, GlobalData* globalData, Factor* factor);
    void printData();
    void print_dNdXY();
    void print_matirxH();
    void printHbc();
};
