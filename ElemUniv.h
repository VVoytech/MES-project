#pragma once
#include<iostream>
#include <vector>
#include <iomanip>
#include "Factor.h"
#include "GlobalData.h"

using namespace std;

struct ElemUniv
{
    vector<vector<double>> ksi;
    vector<vector<double>> eta;
    vector<vector<vector<double>>> boundaryN;
    vector<vector<double>> N;

    void newElemUniv(int npc, Factor* factor, GlobalData* globalData);

    void print_KsiEta();

    void print_BoundaryN();

    void print_N();
};