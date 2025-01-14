#include "Library.h"

void saveToVTK(Grid* grid, GlobalData* globalData, GlobalStructure* globalStructure, const std::string& fileName, int step) {
    std::ofstream vtkFile("heat_step_" + std::to_string(step) + ".vtk");

    if (!vtkFile.is_open()) {
        std::cerr << "Błąd otwarcia pliku do zapisu.\n";
        return;
    }

    int numNodes = globalData->nodeNumber;
    vtkFile << "# vtk DataFile Version 2.0\n";
    vtkFile << "Heat Simulation Results\n";
    vtkFile << "ASCII\n";
    vtkFile << "DATASET UNSTRUCTURED_GRID\n";
    vtkFile << "POINTS " << numNodes << " float\n";

    for (int i = 0; i < numNodes; i++) {
        double x, y;
        vtkFile << grid->nodes[i].x << " " << grid->nodes[i].y << " 0.0\n";
    }

    int numElements = globalData->elementNumber;
    vtkFile << "\nCELLS " << numElements << " " << numElements * 5 << "\n";
    for (int i = 0; i < numElements; i++) {
        std::vector<int> nodes = grid->elements[i].nodes;
        vtkFile << "4 ";
        for (int node : nodes) {
            vtkFile << node - 1 << " ";
        }
        vtkFile << "\n";
    }

    vtkFile << "\nCELL_TYPES " << numElements << "\n";
    for (int i = 0; i < numElements; i++) {
        vtkFile << "9\n";
    }

    vtkFile << "\nPOINT_DATA " << numNodes << "\n";
    vtkFile << "SCALARS Temperature float 1\n";
    vtkFile << "LOOKUP_TABLE default\n";
    for (int i = 0; i < numNodes; i++) {
        vtkFile << globalStructure->globalTemp[i] << "\n";
    }

    vtkFile.close();
    std::cout << "Plik heat_step_" << step << ".vtk zapisany poprawnie.\n";
}


void finalFunction(ElemUniv* elem, GlobalData* globalData, GlobalStructure* globalStructure, Grid* grid, Factor* factor)
{
    for (int i = globalData->simulationStepTime; i <= globalData->simulationTime; i += globalData->simulationStepTime)
    {
        
        
        
        cout << "Czas symulacji [" << i << "s]";
        grid->makeMatrixH(elem, globalData, factor);
        grid->makeHbc(elem, globalData, factor);
        grid->addHbcTomatrixH();
        grid->makeVectorP(elem, globalData, factor);
        grid->makeMatrixC(elem, globalData, factor);

        globalStructure->makeGlobalHMatrix(globalData, grid);
        globalStructure->makeGlobalCMatrix(globalData, grid);
        globalStructure->makeGlobalPVector(globalData, grid);

        globalStructure->globalH = globalStructure->addCtoH(globalData);
        globalStructure->globalP = globalStructure->addCtoP(globalData);

        globalStructure->gauss();
        globalStructure->printMinMax();

        saveToVTK(grid, globalData, globalStructure, "temperatury_out.vtk", i);
    }
}

int main()
{
    Grid* grid = new Grid;
    GlobalData* globalData = new GlobalData;
    loadData("Test1_4_4.txt", grid, globalData); // Wczytanie danych z pliku .txt do elementów
    globalData->npc = 4;

    Factor* factor = new Factor(2);
    ElemUniv* elem = new ElemUniv;
    elem->newElemUniv(globalData->npc, factor, globalData);
    GlobalStructure* globalStructure = new GlobalStructure;
    globalStructure->makeGlobalTempVector(globalData, grid);

    finalFunction(elem, globalData, globalStructure, grid, factor);

    return 0;
}