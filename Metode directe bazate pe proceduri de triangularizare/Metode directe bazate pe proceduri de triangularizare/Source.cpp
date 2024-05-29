#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float** allocateMatrix(int rows, int cols) {
    float** A = (float**)malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++) {
        A[i] = (float*)malloc(cols * sizeof(float));
    }

    return A;
}

void printMatrix(float** A, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void freeMatrix(float** A, int n) {
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
}

void identityMatrix(float** I, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            I[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}

void swapCols(float** A, int n, int col1, int col2) {
    float aux;

    for (int i = 0; i < n; i++) {
        aux = A[i][col1];
        A[i][col1] = A[i][col2];
        A[i][col2] = aux;
    }
}

void directMethod(float** A, float** S, int n) {
    float maxi = 0.0;
    int p = 0, q = 0;

    float* y = (float*)malloc(n * sizeof(float));
    float* x = (float*)malloc(n * sizeof(float));

    identityMatrix(S, n);

    for (int k = 0; k < n - 1; k++) {
        maxi = 0.0;
        for (int i = k; i < n; i++) {
            for (int j = k; j < n; j++) {
                if (maxi < fabs(A[i][j])) {
                    maxi = fabs(A[i][j]);
                    p = i;
                    q = j;
                }
            }
        }
        if (A[p][q] != 0) {
            if (p != k) {
                for (int j = k; j <= n + 1; j++) {
                    float aux = A[k][j];
                    A[k][j] = A[p][j];
                    A[p][j] = aux;
                }
            }
            if (q != k) {
                swapCols(A, n, q, k);
                swapCols(S, n, q, k);
            }
            for (int i = k + 1; i < n; i++) {
                for (int j = k + 1; j <= n; j++) {
                    A[i][j] -= A[i][k] * A[k][j] / A[k][k];
                }
                A[i][k] = 0;
            }
        }
        else {
            printf("Sistemul Ax = b nu poate fi rezolvat prin acest algoritm.");
            exit(1);
        }
    }
    
    float sum = 0.0;

    y[n - 1] = A[n - 1][n] / A[n - 1][n - 1];

    for (int i = n - 1; i >= 0; i--) {
        sum = 0.0;
        for (int k = i + 1; k < n; k++) {
            sum += A[i][k] * y[k];
        }
        y[i] = (A[i][n] - sum) / A[i][i];
    }
    
    for (int i = 0; i < n; i++) {
        x[i] = 0.0;

        for (int k = 0; k < n; k++) {
            x[i] += S[i][k] * y[k];
        }
    }

    printf("Solutia sistemului este:\n");
    for (int i = 0; i < n; i++) {
        printf("\nx[%d] = %.2f", i, x[i]);
    }
    

    free(y);
    free(x);
}

int main()
{
    int n;

    printf("Introduceti ordinul sistemului: ");
    scanf_s("%d", &n);

    if (n < 0) {
        return -1;
    }

    float** A, ** S;

    A = allocateMatrix(n, n + 1);
    S = allocateMatrix(n, n);

    printf("Introduceti sistemul:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf_s("%f", &A[i][j]);
        }
        //printf("b[%d] = ", i);
        //scanf_s("%f", &A[i][n]);
    }

    directMethod(A, S, n);

    freeMatrix(A, n);
    freeMatrix(S, n);
    free(A);
    free(S);

    return 0;
}