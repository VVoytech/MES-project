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
    //grid->print_nodes();  // Wypisanie węzłów z siatki
    //grid->print_elements();  // Wypisanie węzłów należących do poszczególnych elementów

    /*gauss_1D(factor1, function1, -1, 1);
    gauss_1D(factor2, function1, -1, 1);
    gauss_1D(factor3, function1, -1, 1);

    gauss_2D(factor1, function2, -1, 1, -1, 1);
    gauss_2D(factor2, function2, -1, 1, -1, 1);
    gauss_2D(factor3, function2, -1, 1, -1, 1);*/

    Node* n1 = new Node;
    Node* n2 = new Node;
    Node* n3 = new Node;
    Node* n4 = new Node;

    n1->x = 0;
    n2->x = 0.025;
    n3->x = 0.025;
    n4->x = 0;

    n1->y = 0;
    n2->y = 0;
    n3->y = 0.025;
    n4->y = 0.025;

    globalData->conductivity = 30;

    elem->newElemUniv(globalData->npc, factor3);
    globalData->npc = 9;

    Jacobian jacobi(n1, n2, n3, n4, elem, globalData);
    jacobi.dNdXY(elem, globalData);;
    jacobi.add_matrixH(elem, globalData, factor3);


    elem->print_KsiEta();
    jacobi.printData();
    jacobi.print_dNdXY();
    jacobi.print_matirxH();

    return 0;
}