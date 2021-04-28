#include <iostream>
using namespace std;

double function(double x);
double function_poh(double x);

double BisectionMethod(double a, double b, double eps, int& iter);
double ChordMethod(double a, double b, double eps, int& iter);
double NewtonMethod(double x, double eps, int& iter);

int a5 = 1,
a4 = -3,
a3 = 0,
a2 = 7,
a1 = 0,
a0 = -12;

int main() {
    int iter = 0;
    double a = 1, b = 3;
    const double EPS = 0.00001;

    double x = BisectionMethod(a, b, EPS, iter);
    cout << endl << "Bisection method" << endl;
    cout << "x = " << x << endl;
    cout << "Number of iterations: " << iter << endl;

    x = ChordMethod(a, b, EPS, iter);
    cout << endl << "Chord method" << endl;
    cout << "x = " << x << endl;
    cout << "Number of iterations: " << iter << endl;

    x = NewtonMethod(b, EPS, iter);
    cout << endl << "Newton method" << endl;
    cout << "x = " << x << endl;
    cout << "Number of iterations: " << iter << endl;

    system("pause");
    return 0;
}

double function(double x) {
    return a5 * pow(x, 5) + a4 * pow(x, 4) + a3 * pow(x, 3) + a2 * pow(x, 2) + a1 * x + a0;
}

double function_poh(double x) {
    return 5 * a5 * pow(x, 4) + 4 * a4 * pow(x, 3) + 3 * a3 * pow(x, 2) + 2 * a2 * x + a1;
}

double BisectionMethod(double a, double b, double eps, int& iter) {
    double x, c;
    iter = 0;
    do {
        c = (a + b) / 2;
        if (function(a) * function(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        x = c;
        iter++;
    } while (fabs(b - a) > eps && fabs(function(x)) > eps);

    return x;
}

double ChordMethod(double a, double b, double eps, int& iter) {
    double x, c;
    double x_prev = a;
    iter = 0;
    x = a;
    do {
        x_prev = x;
        c = (a * function(b) - b * function(a)) / (function(b) - function(a));
        if (function(a) * function(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
        x = c;
        iter++;
    } while (fabs(x - x_prev) > eps && fabs(function(x)) > eps);
    return x;
}

double NewtonMethod(double x, double eps, int& iter) {
    double x_prev;
    iter = 0;
    do {
        x_prev = x;
        x = x_prev - (function(x) / function_poh(x));
        iter++;
    } while (fabs(x - x_prev) > eps && fabs(x) > eps);
    return x;
}