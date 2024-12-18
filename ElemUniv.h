#pragma once
#include<iostream>
#include <vector>
#include <iomanip>
#include "Factor.h"
#include "GlobalData.h"

using namespace std;

struct ElemUniv
{
    vector<vector<double>> ksi; // Ksi values
    vector<vector<double>> eta; // Eta values
    vector<vector<vector<double>>> boundaryN;
    vector<vector<double>> N;

    // Function to initialize the ksi and eta vectors based on the number of nodes
    void newElemUniv(int npc, Factor* factor, GlobalData* globalData);

    // Function to print the ksi and eta values
    void print_KsiEta();

    void print_BoundaryN();

    void print_N();
};