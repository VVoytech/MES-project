#include "LoadData.h"

// Load data from a specified file into Grid and GlobalData structures
void loadData(const string& filename, Grid* grid, GlobalData* globalData)
{
    vector<Node> nodes;
    vector<Element> element;
    string line;
    string temp;
    std::stringstream ss;  // Creating a string stream from the read line

    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    // Helper lambda to read data into specified variables
    auto readData = [&](int& data)
        {
            getline(file, line);
            ss.clear();
            ss.str(line);
            ss >> temp >> data;
        };

    // Read global data
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

    getline(file, line);  // Skip one line in the .txt file

    // Read nodes
    for (int i = 0; i < globalData->nodeNumber; i++)
    {
        getline(file, line);
        stringstream ss(line);
        Node node;
        char comma;  // Helper variable to read the comma
        int id;      // Helper variable to read node/element number

        ss >> id >> comma >> node.x >> comma >> node.y;  // Read node number, X and Y coordinates
        grid->nodes.push_back(node);  // Add the node to the vector
    }

    getline(file, line);  // Skip one line in the .txt file

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
            ss >> comma; // Ignore commas between nodes
        }

        grid->elements.push_back(element);
    }

    file.close();
}
