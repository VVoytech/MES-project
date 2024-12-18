#include "Library.h"

int main()
{
    Grid* grid = new Grid;
    GlobalData* globalData = new GlobalData;
    loadData("Test2_4_4_MixGrid.txt", grid, globalData); // Wczytanie danych z pliku .txt do elementów
    globalData->npc = 4;

    Factor* factor = new Factor(2);
    ElemUniv* elem = new ElemUniv;
    elem->newElemUniv(globalData->npc, factor, globalData);
    GlobalStructure* globalStructure = new GlobalStructure;
    globalStructure->makeGlobalTempVector(globalData, grid);

    for (int i = 0; i <= globalData->simulationTime; i += globalData->simulationStepTime)
    {
        globalStructure->globalH.clear();
        globalStructure->globalP.clear();
        globalStructure->globalC.clear();
        //cout << "Czas symulacji [" << i << "]\n";
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
        globalStructure->printMinMax();
    }


    //globalStructure->printGlobalHMatrix();
    //globalStructure->printGlobalPVector();

    return 0;
}