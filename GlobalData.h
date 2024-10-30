#pragma once
#include <iostream>
#include "GlobalData.h"

using namespace std;

struct GlobalData
{
    int simulationTime;
    int simulationStepTime;
    int conductivity;
    int alfa;
    int tot;
    int initialTemp;
    int density;
    int specificHeat;
    int nodeNumber;
    int elementNumber;
    int npc;

    // Method to print global data
    void print_globalData();
};
