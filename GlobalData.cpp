#include "GlobalData.h"

// Method to print global data
void GlobalData::print_globalData()
{
    cout << "Simulation Time: " << simulationTime << endl;
    cout << "Simulation Step Time: " << simulationStepTime << endl;
    cout << "Conductivity: " << conductivity << endl;
    cout << "Alfa: " << alfa << endl;
    cout << "Tot: " << tot << endl;
    cout << "Initial Temp: " << initialTemp << endl;
    cout << "Density: " << density << endl;
    cout << "Specific Heat: " << specificHeat << endl;
    cout << "Node Number: " << nodeNumber << endl;
    cout << "Element Number: " << elementNumber << endl << endl;
}
