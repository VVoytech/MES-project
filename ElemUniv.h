#pragma once
#include<iostream>
#include <vector>
#include <iomanip>
#include "Factor.h"

using namespace std;

struct ElemUniv
{
    vector<vector<double>> ksi; // Ksi values
    vector<vector<double>> eta; // Eta values

    // Function to initialize the ksi and eta vectors based on the number of nodes
    void newElemUniv(int npc, Factor* factor);

    // Function to print the ksi and eta values
    void print_KsiEta();
};