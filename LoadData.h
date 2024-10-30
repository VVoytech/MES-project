#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Grid.h"
#include "GlobalData.h"

using namespace std;

// Function declaration
void loadData(const string& filename, Grid* grid, GlobalData* globalData);
