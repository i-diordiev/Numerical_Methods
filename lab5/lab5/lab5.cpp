#include <iostream>
using namespace std;

void SplineInterpolation(double x[5], double y[5], int size);
double* Progon(double matrixA[5][5], double vectorB[5], int size);

int main()
{
    const int SIZE = 5;
    double X[SIZE] = { -4, -2, 0, 2, 4 };
    double Y[SIZE] = { -2.01, -1.958, 0, 1.958, 2.01 };

    double SepDifference1[SIZE - 1];
    double SepDifference2[SIZE - 2];
    double SepDifference3[SIZE - 3];
    double SepDifference4[SIZE - 4];

    for (int i = 0; i < SIZE - 1; i++) {
        SepDifference1[i] = (Y[i] - Y[i + 1]) / (X[i] - X[i + 1]);
    }
    for (int i = 0; i < SIZE - 2; i++) {
        SepDifference2[i] = (SepDifference1[i] - SepDifference1[i + 1]) / (X[i] - X[i + 2]);
    }
    for (int i = 0; i < SIZE - 3; i++) {
        SepDifference3[i] = (SepDifference2[i] - SepDifference2[i + 1]) / (X[i] - X[i + 3]);
    }
    for (int i = 0; i < SIZE - 4; i++) {
        SepDifference4[i] = (SepDifference3[i] - SepDifference3[i + 1]) / (X[i] - X[i + 4]);
    }

    cout << "Polynom of Newton" << endl;
    cout << Y[0] << " + " << SepDifference1[0] << "(x-" << X[0] << ") + " << SepDifference2[0] << "(x-" << X[0] << ")(x-" << X[1] << ") + " << SepDifference3[0] << "(x-" << X[0] << ")(x-" << X[1] << ")(x-" << X[2] << ") + " << SepDifference4[0] << "(x-" << X[0] << ")(x-" << X[1] << ")(x-" << X[2] << ")(x-" << X[3] << ")" << endl;

    cout << endl << endl << "Values of polynom" << endl;
    for (double num = X[0]; num <= X[4]; num += 0.4) {
        printf("Value for x=%4.1f : %9.6f\n", num, (Y[0] + SepDifference1[0] * (num - X[0]) + SepDifference2[0] * (num - X[0]) * (num - X[1]) + SepDifference3[0] * (num - X[0]) * (num - X[1]) * (num - X[2]) + SepDifference4[0] * (num - X[0]) * (num - X[1]) * (num - X[2]) * (num - X[3])));
    }

    cout << endl << endl << "Errors for polynom" << endl;
    for (int i = 0; i < SIZE; i++) {
        cout << "Error for x=" << X[i] << " : ";
        printf("%10.6f\n", Y[i] - (Y[0] + SepDifference1[0] * (X[i] - X[0]) + SepDifference2[0] * (X[i] - X[0]) * (X[i] - X[1]) + SepDifference3[0] * (X[i] - X[0]) * (X[i] - X[1]) * (X[i] - X[2]) + SepDifference4[0] * (X[i] - X[0]) * (X[i] - X[1]) * (X[i] - X[2]) * (X[i] - X[3])));
    }

    cout << endl << endl << "Spline interpolation" << endl;
    SplineInterpolation(X, Y, SIZE);

    system("pause");
    return 0;
}

void SplineInterpolation(double x[5], double y[5], int size) {
    double* a = new double[size - 1];
    double* b = new double[size - 1];
    double* c = new double[size - 1];
    double* d = new double[size - 1];
    double Matrix[4][5] = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };
    double H[4] = { 0,0,0,0 };
    double TempB[5] = { 0,0,0,0,0 };

    for (int i = 0; i < size - 1; i++) {
        a[i] = y[i];
        H[i] = x[i + 1] - x[i];
    }

    Matrix[0][0] = 1;
    Matrix[size - 2][size - 2] = 1;
    for (int i = 1; i < size - 2; i++) { // zapovnuu matrix A ta vector B dlya progonu
        Matrix[i][i - 1] = H[i - 1];
        Matrix[i][i] = 2 * (H[i] + H[i - 1]);
        Matrix[i][i + 1] = H[i];
        TempB[i] = 3 * (((y[i + 1] - y[i]) / H[i]) - ((y[i] - y[i - 1]) / H[i - 1]));
    }
    c = Progon(Matrix, TempB, size - 1); // metodom progonu obchislyuu znachennya C
    for (int i = 0; i < size - 1; i++) {
        d[i] = (c[i + 1] - c[i]) / (3 * H[i]); // dali vid nih obchislyuu zhachennya B i D
        b[i] = ((y[i + 1] - y[i]) / H[i]) - H[i] * (c[i + 1] + 2 * c[i]) / 3;
    }
    d[size - 2] = -c[size - 2] / (3 * H[size - 2]); // krayni znachennya B i D rahuyu vruchu
    b[size - 2] = ((y[size - 1] - y[size - 2]) / H[size - 2]) - H[size - 2] * (c[size - 1] + 2 * c[size - 2]) / 3;
    
    for (int i = 0; i < size - 1; i++) {
        printf("Interval [%2f;%2f]\n", x[i], x[i + 1]);
        printf("a = %9.6f\n", a[i]);
        printf("b = %9.6f\n", b[i]);
        printf("c = %9.6f\n", c[i]);
        printf("d = %9.6f\n", d[i]);
    }
}

double* Progon(double matrixA[5][5], double vectorB[5], int size) {
    double* VectorToReturn = new double[size];
    int n1 = size - 1;
    double KeyElement = matrixA[0][0];
    double* A_progon = new double[size];
    double* B_progon = new double[size];

    A_progon[0] = -matrixA[0][1] / KeyElement;
    B_progon[0] = vectorB[0] / KeyElement;
    for (int i = 1; i < n1; i++) { // pryamyi khid
        KeyElement = matrixA[i][i] + matrixA[i][i - 1] * A_progon[i - 1];
        A_progon[i] = -matrixA[i][i + 1] / KeyElement;
        B_progon[i] = (vectorB[i] - matrixA[i][i - 1] * vectorB[i - 1]) / KeyElement;
    }

    VectorToReturn[n1] = (vectorB[n1] - matrixA[n1][n1 - 1] * B_progon[n1 - 1]) / (matrixA[n1][n1] + matrixA[n1][n1 - 1] * A_progon[n1 - 1]);
    for (int i = n1 - 1; i >= 0; i--) { // zvorotnyi khid
        VectorToReturn[i] = A_progon[i] * VectorToReturn[i + 1] + B_progon[i];
    }

    return VectorToReturn;
}