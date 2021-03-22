#include <iostream>
using namespace std;

void PrintMatrix(double matrix[4][4], int size);

int main()
{
    const int SIZE = 4;
    double matrixA[SIZE][SIZE] = {
        {6.48, 1.3, 0.77, 1.21},
        {1.3, 3.94, 1.3, 0.16},
        {0.77, 1.3, 5.66, 2.1},
        {1.21, 0.16, 2.1, 5.88}
    };
    double matrixM[SIZE][SIZE] = {
        {0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00}
    };
    double matrixM_1[SIZE][SIZE] = {
        {0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00}
    };

    cout << "Matrix A:" << endl;
    PrintMatrix(matrixA, SIZE);

    for (int iteration = 1; iteration < SIZE; iteration++) {
        cout << "Iteration #" << iteration << endl;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (i == SIZE - iteration - 1) {
                    matrixM_1[i][j] = matrixA[i + 1][j];
                    if (i == j) {
                        matrixM[i][j] = 1. / matrixA[i + 1][i];
                    }
                    else {
                        matrixM[i][j] = -matrixA[i + 1][j] / matrixA[i + 1][i];
                    }
                }
                else {
                    if (i == j) {
                        matrixM[i][j] = 1;
                        matrixM_1[i][j] = 1;
                    }
                    else {
                        matrixM[i][j] = 0;
                        matrixM_1[i][j] = 0;
                    }
                }
            }
        }

        double matrixA_1[SIZE][SIZE] = {
            {0.00, 0.00, 0.00, 0.00},
            {0.00, 0.00, 0.00, 0.00},
            {0.00, 0.00, 0.00, 0.00},
            {0.00, 0.00, 0.00, 0.00}
        };

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrixA_1[i][j] = 0;
                for (int k = 0; k < SIZE; k++) {
                    matrixA_1[i][j] += matrixM_1[i][k] * matrixA[k][j];
                }
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrixA[i][j] = 0;
                for (int k = 0; k < SIZE; k++) {
                    matrixA[i][j] += matrixA_1[i][k] * matrixM[k][j];
                }
            }
        }

        cout << "Matrix A:" << endl;
        PrintMatrix(matrixA, SIZE);
        cout << "Matrix M:" << endl;
        PrintMatrix(matrixM, SIZE);
        cout << "Matrix M^-1:" << endl;
        PrintMatrix(matrixM_1, SIZE);
    }

    cout << "\n\n\nMatrix P:" << endl;
    PrintMatrix(matrixA, SIZE);

    cout << "Characteristic equation:" << endl;
    cout << "-n^4";
    for (int i = 0; i < 3; i++) {
        int current = 3 - i;
        if (matrixA[0][i] >= 0) {
            cout << " +" << matrixA[0][i] << "n^" << current;
        }
        else {
            cout << " " << matrixA[0][i] << "n^" << current;
        }
    }
    cout << matrixA[0][3] << " = 0"<< endl;
    system("pause");
    return 0;
}

void PrintMatrix(double matrix[4][4], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size;j++) {
            printf("%12.6f", matrix[i][j]);
        }
        cout << endl;
    }
}
