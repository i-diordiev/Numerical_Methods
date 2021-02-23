#include <iostream>

using namespace std;

void PrintMatrix(double matrix[][4], int n, int m);
void PrintVector(double vector[], int n);
void FindMax(double matrix[][4], int n, int m, int& i_max, int& j_max);
void SwapElements(double matrix[][4], double vectorB[], int n, int m, int i_max, int j_max);
void GaussForward(double matrix[][4], double vectorB[], int n, int m);
void GaussBackward(double matrix[][4], double b[], double x[], int n, int m);
void CheckPrecision(double matrix[][4], double b[], double x[], int n, int m);

int main()
{
    const int N = 4;
    const int M = 4;
    double matrixA[N][M] = {
        {3.81, 0.25, 1.28, 1.25},
        {2.25, 1.32, 5.08, 0.49},
        {5.31, 6.78, 0.98, 1.04},
        {9.89, 2.45, 3.35, 2.28}
    };
    double vectorB[N] = { 4.21, 6.97, 2.38, 10.98 };
    double vectorX[N] = { 0, 0, 0, 0 };
    int I_MAX = 0, J_MAX = 0;

    cout << "Start matrix A: " << endl;
    PrintMatrix(matrixA, N, M);
    cout << endl << "Start vector B: " << endl;
    PrintVector(vectorB, N);

    FindMax(matrixA, N, M, I_MAX, J_MAX);
    SwapElements(matrixA, vectorB, N, M, I_MAX, J_MAX);
    cout << endl << "Matrix A after choosing main element: " << endl;
    PrintMatrix(matrixA, N, M);
    cout << endl << "Vector B after choosing main element: " << endl;
    PrintVector(vectorB, N);


    GaussForward(matrixA, vectorB, N, M);
    cout << endl << "Matrix A after straight course of Gaussian method: " << endl;
    PrintMatrix(matrixA, N, M);
    cout << endl << "Vector B after straight course of Gaussian method: " << endl;
    PrintVector(vectorB, N);

    GaussBackward(matrixA, vectorB, vectorX, N, M);
    cout << endl << "Vector X:" << endl;
    for (int i = 0; i < M; i++) {
        printf("x%i = %10.6f\n", i + 1, vectorX[i]);
    }
    
    cout << endl << "Inconsistency vector:" << endl;
    CheckPrecision(matrixA, vectorB, vectorX, N, M);

    system("pause");
    return 0;
}

void PrintMatrix(double matrix[][4], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m;j++) {
            printf("%10.6f", matrix[i][j]);
        }
        cout << endl;
    }
}

void PrintVector(double vector[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%10.6f\n", vector[i]);
    }
}

void FindMax(double matrix[][4], int n, int m, int& i_max, int& j_max) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] > max) {
                i_max = i;
                j_max = j;
            }
        }
    }
}

void SwapElements(double matrix[][4], double vectorB[], int n, int m, int i_max, int j_max) {
    swap(matrix[0], matrix[i_max]);
    for (int i = 0; i < n; i++) {
        swap(matrix[i][0], matrix[i][j_max]);
    }
    swap(vectorB[0], vectorB[i_max]);
}

void GaussForward(double matrix[][4], double vector[], int n, int m) {
    for (int i = 0; i < n; i++) {
        double main_element = matrix[i][i];
        for (int j = i; j < m; j++) {
            matrix[i][j] /= main_element;
        }

        vector[i] /= main_element;

        for (int k = i + 1; k < n; k++) {
            double current_main = matrix[k][i];
            for (int j = 0; j < m; j++) {
                matrix[k][j] -= (current_main * matrix[i][j]);
            }
            vector[k] -= current_main * vector[i];
        }
        cout << endl;
        PrintMatrix(matrix, 4, 4);
    }
}


void GaussBackward(double matrix[][4], double b[], double x[], int n, int m) {
    double prev_sum = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j < m; j++) {
            prev_sum += x[j] * matrix[i][j];
        }
        x[i] = (b[i] - prev_sum) / matrix[i][i];
        prev_sum = 0;
    }
}

void CheckPrecision(double matrix[][4], double b[], double x[], int n, int m) {
    for (int i = 0; i < n; i++) {
        double current_sum = 0;
        for (int j = 0; j < m; j++) {
            current_sum += matrix[i][j] * x[j];
        }
        printf("Value for %i row: %10.6f\n", i + 1, b[i] - current_sum);
    }
}