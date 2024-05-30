#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorizareLR_Doolittle(float** A, float** L, float** R, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            L[i][j] = 0.0;
            R[i][j] = 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
    }
    
    if (A[0][0] == 0) {
        printf("Matricea nu poate fi factorizata cu formulele 1.\n");
        return;
    }
    else {
        for (int i = 0; i < n; i++) {
            L[i][0] = A[i][0] / A[0][0];
            R[0][i] = A[0][i];
        }

        for (int k = 1; k < n; k++) {
            for (int j = k; j < n; j++) {
                double sum = 0.0;
                for (int h = 0; h < k; h++) {
                    sum += L[k][h] * R[h][j];
                }

                R[k][j] = A[k][j] - sum;
            }

            if (R[k][k] == 0) {
                printf("Matricea nu poate fi factorizata cu formulele 1.\n");
                return;
            }
            else {
                for (int i = k + 1; i < n; i++) {
                    double sum = 0.0;
                    for (int h = 0; h < k; h++) {
                        sum += L[i][h] * R[h][k];
                    }

                    L[i][k] = (A[i][k] - sum) / R[k][k];
                }
            }
        }
        double sum = 0.0;
        for (int h = 0; h < n - 1; h++) {
            sum += L[n - 1][h] * R[h][n - 1];
        }
        R[n - 1][n - 1] = A[n - 1][n - 1] - sum;
    }
}

int main() {
    int n;

    printf("Introduceti numar de linii si coloane pentru matrice: ");
    scanf_s("%d", &n);

    float** A = (float**)malloc(n * sizeof(float*));
    float** L = (float**)malloc(n * sizeof(float*));
    float** R = (float**)malloc(n * sizeof(float*));

    for (int i = 0; i < n; i++) {
        A[i] = (float*)malloc(n * sizeof(float));
    }

    for (int i = 0; i < n; i++) {
        L[i] = (float*)malloc(n * sizeof(float));
    }

    for (int i = 0; i < n; i++) {
        R[i] = (float*)malloc(n * sizeof(float));
    }

    printf("Introduceti elementele matricei:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf_s("%f", &A[i][j]);
        }
    }

    factorizareLR_Doolittle(A, L, R, n);

    printf("Matricea factorizata L este:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", L[i][j]);
        }
        printf("\n");
    }

    printf("Matricea factorizata R este:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", R[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }

    for (int i = 0; i < n; i++) {
        free(L[i]);
    }

    for (int i = 0; i < n; i++) {
        free(R[i]);
    }

    free(A);
    free(L);
    free(R);
	return 0;
}