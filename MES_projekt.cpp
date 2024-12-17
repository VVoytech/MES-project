#include "Library.h"

int main()
{
    Grid* grid = new Grid;
    GlobalData* globalData = new GlobalData;
    loadData("Test2_4_4_MixGrid.txt", grid, globalData); // Wczytanie danych z pliku .txt do elementów
    globalData->npc = 4;

    Factor* factor = new Factor(2);
    ElemUniv* elem = new ElemUniv;

    //globalData->print_globalData();  // Wypisanie danych z początku pliku .txt
    grid->print_nodes();  // Wypisanie węzłów z siatki
    grid->print_elements();  // Wypisanie węzłów należących do poszczególnych elementów

    elem->newElemUniv(globalData->npc, factor);
    elem->print_BoundaryN();

    grid->makeMatrixH(elem, globalData, factor);
    grid->makeHbc(elem, globalData, factor);
    grid->addHbcTomatrixH();
    //grid->printHbc();
    //grid->printMatrixH();
    grid->makeVectorP(elem, globalData, factor);
    grid->printVectorP();

    GlobalStructure* globalStructure = new GlobalStructure;
    globalStructure->makeGlobalHMatrix(globalData, grid);
    globalStructure->makeGlobalPVector(globalData, grid);
    globalStructure->printGlobalHMatrix();
    globalStructure->printGlobalPVector();

    globalStructure->gauss();
    globalStructure->printGlobalTemp();
    //globalH->printGlobalHMatrix();
    //globalH->printGlobalPVector();

    return 0;
}