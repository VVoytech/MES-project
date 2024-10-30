#pragma once
#include<iostream>
#include <vector>
#include "Factor.h"

using namespace std;

struct Factor
{
    vector<double> node;   // Nodes for the quadrature
    vector<double> factor; // Weights for the quadrature
};

// Function to add factors to the provided Factor objects
void add_factor(Factor* factor1, Factor* factor2, Factor* factor3, Factor* factor4);
