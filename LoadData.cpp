#include "LoadData.h"

void loadData(const string& filename, Grid* grid, GlobalData* globalData)
{
    vector<Node> nodes;
    vector<Element> element;
    string line;
    string temp;
    std::stringstream ss;  // Tworzenie strumienia string z wczytanej linii

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Funkcja pomagajaca wczytywac dane do poszczególnych zmiennych
    auto readData = [&](int& data)
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

    getline(file, line);  // Przeskoczenie nad jedna linijka w pliku .txt, której nie potrzebujemy wczytac

    // Read nodes
    for (int i = 0; i < globalData->nodeNumber; i++)
    {
        getline(file, line);
        stringstream ss(line);
        Node node;
        char comma;  // Zmienna pomocnicza do wczytania przecinka
        int id;  // Zmienna pomocnicza do wczytania numeru wezla/elementu

        ss >> id >> comma >> node.x >> comma >> node.y;  // Wczytywanie numeru wezla, wspolrzedna X i Y

        grid->nodes.push_back(node);  // Dodajemy wezel do wektora
    }

    getline(file, line);  // Przeskoczenie nad jedna linijka w pliku .txt, której nie potrzebujemy wczytac

    // Read elements
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
            ss >> comma; // Ignorowanie przecinka miedzy wezlami
        }

        grid->elements.push_back(element);
    }

    getline(file, line);

    getline(file, line);
    ss.clear();
    ss.str(line);
    int node;
    char comma;

    while (ss >> node)
    {
        grid->nodes[node - 1].BC = true;
        ss >> comma; // Ignorowanie przecinka miedzy wezlami
    }

    file.close();
}
