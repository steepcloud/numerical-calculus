#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swapRows(float** A, int row1, int row2, int n) {
    float aux;

    for (int i = 0; i < n; i++) {
        aux = A[row1][i];
        A[row1][i] = A[row2][i];
        A[row2][i] = aux;
    }
}

void triangularizare_2(float** A, int n) {
    int p;
    float max;

    for (int k = 0; k < n - 1; k++) {
        max = 0;
        for (int i = k; i < n; i++) {
            if (fabs(A[i][k]) > max) {
                max = fabs(A[i][k]);
                p = i;
            }
        }

        if (A[p][k] == 0) {
            printf("Matricea nu poate fi triangularizata!\n");
            exit(1);
        }

        if (p != k) {
            swapRows(A, p, k, n);
        }

        for (int i = k + 1; i < n; i++) {
            for (int j = k + 1; j < n; j++) {
                A[i][j] -= (A[i][k] * A[k][j]) / A[k][k];
            }
            A[i][k] = 0;
        }
    }
}

int main() {
    int n;

    printf("Introduceti linii si coloane pentru matrice: ");
    scanf_s("%d", &n);

    float** A = (float**)malloc(n * sizeof(float*));

    for (int i = 0; i < n; i++) {
        A[i] = (float*)malloc(n * sizeof(float));
    }

    printf("Introduceti elementele matricei:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("A[%d][%d] = ", i, j);
            scanf_s("%f", &A[i][j]);
        }
    }

    triangularizare_2(A, n);

    printf("Matricea triangularizata este:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", A[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }

    free(A);


    return 0;
}