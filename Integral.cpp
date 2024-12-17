#include "Integral.h"

// 1D ca³ka
void gauss_1D(Factor* factor, FunctionPointer1D func, double a, double b)
{
    double integral = 0;

    for (int i = 0; i < factor->factor.size(); i++)
    {
        integral += factor->factor[i] * func(factor->node[i]);
    }
    cout << "Wynik calkowania metoda Gaussa w przestrzeni 1d stosujac " << factor->node.size() << " punktowy schemat calkowania: " << integral << endl;
}

// 2D ca³ka
void gauss_2D(Factor* factor, FunctionPointer2D func, double a, double b, double c, double d)
{
    double integral = 0;

    for (int i = 0; i < factor->factor.size(); i++)
    {
        for (int j = 0; j < factor->factor.size(); j++)
        {
            integral += factor->factor[i] * factor->factor[j] * func(factor->node[i], factor->node[j]);
        }
    }
    cout << "Wynik calkowania metoda Gaussa w przestrzeni 2d stosujac " << factor->node.size() << " punktowy schemat calkowania: " << integral << endl;
}

double function1(double x) { return 5 * pow(x, 2) + 3 * x + 6; }

double function2(double x, double y) { return 5 * pow(x, 2) * pow(y, 2) + 3 * x * y + 6; }
