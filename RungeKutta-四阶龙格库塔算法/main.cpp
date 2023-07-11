#include <iostream>
#include <fstream>
#include "RungeKutta.hpp"

void func1(double t, double* y, double* dy, void* parameters) {
    dy[0] = y[1];
    dy[1] = 0.5 * ( - 3 * y[1] + 1.5 * y[3] - 100 * y[0] + 50 * y[2] - 2.0 * sin(3.754 * t));
    dy[2] = y[3];
    dy[3] = 0.5 * (1.5 * y[1] - 3 * y[3] + 1.5 * y[5] + 50 * y[0] - 100 * y[2] + 50 * y[4] - 2.0 * cos(2.2 * t));
    dy[4] = y[5];
    dy[5] = 0.5 * (-1.5 * y[3] - 3 * y[5] + 50 * y[2] - 100 * y[4] + sin(2.8 * t));
}

int main()
{
    RungeKutta rk;
    rk.setDifferentianEquation(func1,6);
    double y[] = {1,1,1,1,1,1};
    while (rk.run(y)) {
        std::cout << y[0] << "\n";
    }
    return 0;
}