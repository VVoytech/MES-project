#include "Library.h"

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

        //globalStructure->printGlobalHMatrix();
        //globalStructure->printGlobalPVector();
        //globalStructure->printGlobalTemp();

        //globalStructure->printGlobalTemp();
        globalStructure->printMinMax();
    }
}

int main()
{
    Grid* grid = new Grid;
    GlobalData* globalData = new GlobalData;
    loadData("Test2_4_4_MixGrid.txt", grid, globalData); // Wczytanie danych z pliku .txt do elementów
    globalData->npc = 16;

    Factor* factor = new Factor(4);
    ElemUniv* elem = new ElemUniv;
    elem->newElemUniv(globalData->npc, factor, globalData);
    GlobalStructure* globalStructure = new GlobalStructure;
    globalStructure->makeGlobalTempVector(globalData, grid);

    finalFunction(elem, globalData, globalStructure, grid, factor);

    return 0;
}