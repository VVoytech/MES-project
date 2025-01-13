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
};


