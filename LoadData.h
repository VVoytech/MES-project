#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "Grid.h"
#include "GlobalData.h"
#include "Element.h"

using namespace std;

void loadData(const string& filename, Grid* grid, GlobalData* globalData);
