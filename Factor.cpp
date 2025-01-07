#include "Factor.h"

Factor::Factor(int nodeNum)
{
    switch (nodeNum)
    {
    case 1:
        node.push_back(0);
        factor.push_back(2);
        break;

    case 2:
        node.push_back(-(1.0 / sqrt(3.0)));
        node.push_back(1.0 / sqrt(3.0));
        factor.push_back(1);
        factor.push_back(1);
        break;

    case 3:
        node.push_back(-(sqrt(3.0 / 5.0)));
        node.push_back(0);
        node.push_back(sqrt(3.0 / 5.0));
        factor.push_back(5.0 / 9.0);
        factor.push_back(8.0 / 9.0);
        factor.push_back(5.0 / 9.0);
        break;
        
    case 4:
        node.push_back(-0.861136);
        node.push_back(-0.339981);
        node.push_back(0.339981);
        node.push_back(0.861136);
        factor.push_back(0.347855);
        factor.push_back(0.652145);
        factor.push_back(0.652145);
        factor.push_back(0.347855);
        break;

    default:
        cout << "Brak opcji z tylkoma punktami calkowania!" << endl;
        break;
    }
}

// Function to add factors to the provided Factor objects
void Factor::add_factor(Factor* factor1, Factor* factor2, Factor* factor3, Factor* factor4)
{
    // One-point quadrature
    factor1->node.push_back(0);
    factor1->factor.push_back(2);

    // Two-point quadrature
    factor2->node.push_back(-(1.0 / sqrt(3.0)));
    factor2->node.push_back(1.0 / sqrt(3.0));
    factor2->factor.push_back(1);
    factor2->factor.push_back(1);

    // Three-point quadrature
    factor3->node.push_back(-(sqrt(3.0 / 5.0)));
    factor3->node.push_back(0);
    factor3->node.push_back(sqrt(3.0 / 5.0));
    factor3->factor.push_back(5.0 / 9.0);
    factor3->factor.push_back(8.0 / 9.0);
    factor3->factor.push_back(5.0 / 9.0);

    // Four-point quadrature
    factor4->node.push_back(-0.861136);
    factor4->node.push_back(-0.339981);
    factor4->node.push_back(0.339981);
    factor4->node.push_back(0.861136);
    factor4->factor.push_back(0.347855);
    factor4->factor.push_back(0.652145);
    factor4->factor.push_back(0.652145);
    factor4->factor.push_back(0.347855);
}
