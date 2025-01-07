#pragma once
#include<iostream>
#include <vector>
#include "Factor.h"

using namespace std;

struct Factor
{
    vector<double> node;
    vector<double> factor;

    Factor(int nodeNum);

    void add_factor(Factor* factor1, Factor* factor2, Factor* factor3, Factor* factor4);
};


