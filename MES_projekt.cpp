#include "Library.h"

int main()
{
    Grid* grid = new Grid;
    GlobalData* globalData = new GlobalData;

    Factor* factor1 = new Factor;
    Factor* factor2 = new Factor;
    Factor* factor3 = new Factor;
    Factor* factor4 = new Factor;
    add_factor(factor1, factor2, factor3, factor4);

    ElemUniv* elem = new ElemUniv;

    loadData("Test1_4_4.txt", grid, globalData); // Wczytanie danych z pliku .txt do elementów

    //globalData->print_globalData();  // Wypisanie danych z początku pliku .txt
    grid->print_nodes();  // Wypisanie węzłów z siatki
    grid->print_elements();  // Wypisanie węzłów należących do poszczególnych elementów

    globalData->npc = 4;
    elem->newElemUniv(globalData->npc, factor2);
    elem->print_BoundaryN();

    grid->makeMatrixH(elem, globalData, factor2);
    grid->makeHbc(elem, globalData, factor2);
    grid->addHbcTomatrixH();
    //grid->printHbc();
    //grid->printMatrixH();
    grid->makeVectorP(elem, globalData, factor2);
    grid->printVectorP();

    GlobalHMatrix* globalH = new GlobalHMatrix;
    globalH->makeGlobalHMatrix(globalData, grid);
    globalH->makeGlobalPVector(globalData, grid);
    globalH->printGlobalHMatrix();
    globalH->printGlobalPVector();

    globalH->gauss();
    //globalH->printGlobalHMatrix();
    //globalH->printGlobalPVector();

    return 0;
}