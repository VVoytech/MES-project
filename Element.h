#pragma once
#include<iostream>
#include "Element.h"
#include "Jakobian.h"
#include "VectorP.h"
#include "MatrixC.h"
#include <vector>

using namespace std;

struct Element
{
    vector<int> nodes;
    Jacobian jacobian;
    VectorP vectorP;
    MatrixC matrixC;

};