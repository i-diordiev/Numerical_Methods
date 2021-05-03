#include <iostream>
#include <cmath>

using namespace std;

double Function(double x);  // функція для обчислення значення початкової функції у точці х
double Trapezium(double a, double b, double eps, int& count);  // функція для знаходження значення інтегралу методом трапеції
double Gauss(double a, double b);  // функція для знаходження значення інтегралу за квадратурною формулою Гауса

int main() {
    int a = 1, b = 3;  // межі інтегрування
    int counter = 0;  // лічильник ітерацій
    const double EPS = 0.0001;  // похибка
    cout << "Function: (cos(x)) / (x + 1) in range [" << a << ";" << b << "]" << endl;

    cout << endl << "Trapezium method" << endl;  // викликаємо функцію для пошуку інтеграла методом трапеції
    printf("Result: %6.4f\n", Trapezium(a, b, EPS, counter));
    cout << "Count of iterations: " << counter << endl;

    cout << endl << "Gaussian method" << endl;  // викликаємо функцію для пошуку інтеграла квадратурною формулою Гауса
    printf("Result: %6.4f\n", Gauss(a, b));
    cout << "m = 4" << endl;

    system("pause");
    return 0;
}

double Function(double x) {
    return (cos(x)) / (x + 1);
}


double Trapezium(double a, double b, double eps, int& count) {
    int n = 2;  // кількість проміжків
    double result = 1, result_prev = 0;  // початкові значення
    do {
        result_prev = result;  // перезаписуємо значення інтеграла
        result = 0;
        double h = (b - a) / n;  // різниця між лівим та середнім значення поточного проміжка
        double x = a;  // початковий х - ліве значення початкового проміжку
        for (int i = 0; i < n - 1; i++) {  // обчислюємо суму значень f(x) на кожному проміжку
            result += (Function(x) + Function(x + h)) / 2;
            x += h;
        }
        result *= h;  // домножаємо суму y на h
        n *= 2; // розбиваємо кожен поточний проміжок на 2
        count++;  // збільшуємо лічильник
    } while (fabs(result - result_prev) > eps);  // цикл продовжується, поки різниця між попереднім та поточним значенням інтеграла менше ніж похибка
    return result;
}

double Gauss(double a, double b) {
    int m = 4;  // кількість ітерацій
    double X[4] = {-0.861136, -0.339981, 0.339981, 0.861136};  // значення вузлів xi
    double A[4] = {0.347855, 0.652145, 0.652145, 0.347855};  // значення коефіцієнтів Ai
    double x;  // значення вузла 
    double result = 0;  // значення інтеграла - сума значень кожного вузла помноженого на ваговий коефіцієнт
    for (int i = 0; i < m; i++) {
        x = (a + b) / 2 + X[i] * (b - a) / 2;  // заміна змінної для зміни проміжку інтегрування і правильної роботи функції
        result += A[i] * Function(x);
    }
    return result;
}