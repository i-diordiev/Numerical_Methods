#include <iostream>
#include <cmath>
using namespace std;

double Function(double x, double y);
void MethodRungeKutta(double a, double b);
void MethodAdams(double a, double b);

int main() {
    int a = 0, b = 6;
    cout << "Function: 1 + 1.8 * y * sin(x) - y^2" << endl;
    cout << "Interval [0;6], x0 = 0, y0 = 0" << endl;

    cout << "Method of Runge-Kutta" << endl;
    MethodRungeKutta(a, b);

    cout << "\nMethod of Adams" << endl;
    MethodAdams(a, b);

    system("pause");
    return 0;
}

double Function(double x, double y) {  // function by condition
    return 1 + (1.8 * y * sin(x)) - (y * y);
}

void MethodRungeKutta(double a, double b) {  // Runge-Kutta method
    double k1, k2, k3, k4;  // intermediate values
    double h = 0.1;  // step
    double eps;  // value of error, calculated by Runge's formula

    double x[1000];  // arrays with values
    double y[1000];

    x[0] = a;
    y[0] = 0;

    int i = 0;
    cout << "x\t y\t\terror" << endl;

    do {
        do {
            x[i + 1] = x[i] + h;

            k1 = Function(x[i], y[i]);  // calculating intermediate values
            k2 = Function(x[i] + (h / 2), y[i] + ((h * k1) / 2));
            k3 = Function(x[i] + (h / 2), y[i] + ((h * k2) / 2));
            k4 = Function(x[i] + h, y[i] + (h * k3));
            
            eps = (pow(y[i], h) - pow(y[i], h / 2)) / (pow(2, 4) - 1);  // calculating error using Runge's formula

            if (abs((k2 - k3) / (k1 - k2)) > 0.09)  // if value of error is too big, make step smaller and repeat cycle
                h /= 2;

        } while (abs((k2 - k3) / (k1 - k2)) > 0.09);
        y[i + 1] = y[i] + (h / 6) * (k1 + (2 * k2) + (2 * k3) + k4);  // calculate value of y
        printf("%4.2f\t%7.4f\t\t%7.5f\n", x[i], y[i], eps);
        i++;
    } while (x[i] < b);
}

void MethodAdams(double a, double b) {
    double k1, k2, k3, k4;  // intermediate values
    double h = 0.1;  // step
    double eps;  // value of error, calculated by Runge's formula

    double x[1000];  
    double y[1000];
    x[0] = a;
    y[0] = 0;

    int i = 0;
    cout << "x\t y\t\terror" << endl;

    // calculating first 3 values using Runge-Kutta's method
    do {
        do {
            x[i + 1] = x[i] + h;

            k1 = Function(x[i], y[i]);
            k2 = Function(x[i] + (h / 2), y[i] + ((h * k1) / 2));
            k3 = Function(x[i] + (h / 2), y[i] + ((h * k2) / 2));
            k4 = Function(x[i] + h, y[i] + (h * k3));
            eps = (pow(y[i], h) - pow(y[i], h / 2)) / (pow(2, 4) - 1);

            if (abs((k2 - k3) / (k1 - k2)) > 0.09)
                h /= 2;

        } while (abs((k2 - k3) / (k1 - k2)) > 0.09);
        y[i + 1] = y[i] + (h / 6) * (k1 + (2 * k2) + (2 * k3) + k4);
        printf("%4.2f\t%7.4f\t\t%7.5f\n", x[i], y[i], eps);
        i++;
    } while (i < 3);

    double y_interp;  // value of y, calculated with interpolation formula

    do {
        do {
            x[i + 1] = x[i] + h;
            y[i + 1] = y[i] + (h / 24) * (55 * Function(x[i], y[i]) - 59 * Function(x[i - 1], y[i - 1])  // calc. y using extrapolation
                + 37 * Function(x[i - 2], y[i - 2]) - 9 * Function(x[i - 3], y[i - 3]));
            y_interp = y[i] + (h / 24) * (9 * Function(x[i + 1], y[i + 1]) + 19 * Function(x[i], y[i])  // calc. y using interpolation formula
                - 5 * Function(x[i - 1], y[i - 1]) + Function(x[i - 2], y[i - 2]));

            if (abs(y_interp - y[i + 1]) > 0.09)  // if value of error is too big, make step smaller and repeat cycle
                h /= 2;

        } while (abs(y_interp - y[i + 1]) > 0.09);
        eps = (pow(y[i], h) - pow(y[i], h / 2)) / (pow(2, 4) - 1);  // calculating error using Runge's formula
        printf("%4.2f\t%7.4f\t\t%7.5f\n", x[i], y[i], eps);
        i++;
    } while (x[i] < b);
}