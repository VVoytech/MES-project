#pragma once
#include "Library.h"

void loadData(const string& filename, Grid* grid, GlobalData* globalData)
{
    vector<Node> nodes;
    vector<Element> element;
    string line;
    string temp;
    std::stringstream ss;  // Tworzenie strumienia string z wczytanej linii

    ifstream file(filename);

    auto readData = [&](int& data)  // Funkcja pomagaj�ca wczytywa� dane do poszczeg�lnych zmiennych
        {
            getline(file, line);
            ss.clear();
            ss.str(line);
            ss >> temp >> data;
        };

    readData(globalData->simulationTime);
    readData(globalData->simulationStepTime);
    readData(globalData->conductivity);
    readData(globalData->alfa);
    readData(globalData->tot);
    readData(globalData->initialTemp);
    readData(globalData->density);
    readData(globalData->specificHeat);

    getline(file, line);
    ss.clear();
    ss.str(line);
    ss >> temp >> temp >> globalData->nodeNumber;
    grid->nodeNumber = globalData->nodeNumber;

    getline(file, line);
    ss.clear();
    ss.str(line);
    ss >> temp >> temp >> globalData->elementNumber;
    grid->elementNumber = globalData->elementNumber;

    getline(file, line);  // Przeskoczenie nad jedn� linijk� w pliku .txt, kt�rej nie potrzebujemy wczyta�

    for (int i = 0; i < globalData->nodeNumber; i++)
    {
        getline(file, line);
        stringstream ss(line);
        Node node;
        char comma;  // Zmienna pomocnicza do wczytania przecinka
        int id;  // Zmienna pomocnicza do wczytania numeru w�z�a/elementu

        ss >> id >> comma >> node.x >> comma >> node.y;  // Wczytywanie numeru w�z�a, wsp�rz�dn� X i Y

        grid->nodes.push_back(node);  // Dodajemy w�ze� do wektora

    }

    getline(file, line);  // Przeskoczenie nad jedn� linijk� w pliku .txt, kt�rej nie potrzebujemy wczyta�

    for (int i = 0; i < globalData->elementNumber; i++)
    {
        getline(file, line);
        stringstream ss(line);
        int node;
        Element element;
        char comma;
        int id;

        ss >> id >> comma;

        while (ss >> node)
        {
            element.nodes.push_back(node);
            ss >> comma; // Ignorujemy przecinki pomi�dzy w�z�ami
        }

        grid->elements.push_back(element);
    }

    file.close();
}