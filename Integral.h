#pragma once
#include <iostream>
#include <cmath>
#include "Factor.h"

using namespace std;

typedef double (*FunctionPointer1D)(double);
typedef double (*FunctionPointer2D)(double, double);

// Function declarations
void gauss_1D(Factor* factor, FunctionPointer1D func, double a, double b);
void gauss_2D(Factor* factor, FunctionPointer2D func, double a, double b, double c, double d);

// Sample functions for integration
double function1(double x);
double function2(double x, double y);
