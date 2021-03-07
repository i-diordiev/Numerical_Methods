#include <iostream>


using namespace std;

void PrintMatrix(double matrix[5][5], int size);
void PrintVector(double vector[], int size);
void CheckPrecision(double matrix[5][5], double b[], double x[], int size);

int main()
{
    const int SIZE = 5;
    double matrixA[SIZE][SIZE] = {
        {5.43, 1.12, 0.95, 1.32, 0.83},
        {0.00, 3.79, 1.93, 0.30, 0.74},
        {0.00, 1.93, 6.22, 1.07, 1.43},
        {0.00, 0.30, 1.07, 4.00, 1.05},
        {0.00, 0.74, 1.43, 1.05, 5.34}
    };
    double vectorB[SIZE] = { 6.54, 1.84, 2.82, 4.68, 4.32 };
    double vectorX[SIZE] = { 0,0,0,0,0 };

    double matrixC[SIZE][SIZE] = {
        {0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00},
        {0.00, 0.00, 0.00, 0.00, 0.00}
    };
    double vectorD[SIZE] = { 0.00, 0.00, 0.00, 0.00, 0.00 };
    double vectorX_prev[SIZE] = { 0.00, 0.00, 0.00, 0.00, 0.00 };

    const double EPS = 0.000001;
    double diff = 0;
    int iteration = 0;

    cout << "Matrix A: " << endl;
    PrintMatrix(matrixA, SIZE);
    cout << "Vector B:" << endl;
    PrintVector(vectorB, SIZE);

    for (int i = 0; i < SIZE; i++) {
        vectorX[i] = vectorB[i];
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (i != j) {
                matrixC[i][j] = -(matrixA[i][j] / matrixA[i][i]);
            }
            else {
                matrixC[i][j] = 0;
            }
        }
        vectorD[i] = vectorB[i] / matrixA[i][i];
    }

    cout << "Matrix C: " << endl;
    PrintMatrix(matrixC, SIZE);
    cout << "Vector D:" << endl;
    PrintVector(vectorD, SIZE);

    do {
        iteration++;
        for (int i = 0; i < SIZE; i++) {
            double sum = 0;
            for (int j = 0; j < SIZE; j++) {
                sum += matrixC[i][j] * vectorX_prev[j];
            }
            vectorX[i] = sum + vectorD[i];
        }

        for (int i = 0; i < SIZE; i++) {
            if (fabs(vectorX - vectorX_prev) > diff) {
                diff = fabs(vectorX[i] - vectorX_prev[i]);
            }
        }

        for (int i = 0; i < SIZE; i++) {
            vectorX_prev[i] = vectorX[i];
        }

        cout << endl <<  "Iteration #" << iteration << endl;
        cout << "Inconsistency vector:" << endl;
        CheckPrecision(matrixA, vectorB, vectorX, SIZE);
    } while (diff >= EPS);

    cout << endl << "Vector X:" << endl;
    PrintVector(vectorX, SIZE);
    cout << "Inconsistency vector:" << endl;
    CheckPrecision(matrixA, vectorB, vectorX, SIZE);

    system("pause");
    return 0;
}

void PrintMatrix(double matrix[5][5], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size;j++) {
            printf("%10.6f", matrix[i][j]);
        }
        cout << endl;
    }
}

void PrintVector(double vector[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%10.6f\n", vector[i]);
    }
}

void CheckPrecision(double matrix[5][5], double b[], double x[], int size) {
    for (int i = 0; i < size; i++) {
        double current_sum = 0;
        for (int j = 0; j < size; j++) {
            current_sum += matrix[i][j] * x[j];
        }
        printf("Value for %i row: %10.6f\n", i + 1, b[i] - current_sum);
    }
}