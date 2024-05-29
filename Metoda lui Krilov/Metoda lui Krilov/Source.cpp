#include <stdlib.h>
#include <stdio.h>
#include <math.h>

float** allocateMatrix(int rows, int cols) {
	float** A = (float**)malloc(rows * sizeof(float*));
	for (int i = 0; i < rows; i++) {
		A[i] = (float*)malloc(cols * sizeof(float));
	}

	return A;
}

void freeMatrix(float** A, int n) {
	for (int i = 0; i < n; i++) {
		free(A[i]);
	}
	free(A);
}

void swapRows(float** A, int row1, int row2, int n) {
	float aux;

	for (int i = 0; i < n; i++) {
		aux = A[row1][i];
		A[row1][i] = A[row2][i];
		A[row2][i] = aux;
	}
}

void swapCols(float** A, int col1, int col2, int n) {
	float aux;

	for (int j = 0; j < n; j++) {
		aux = A[j][col1];
		A[j][col1] = A[j][col2];
		A[j][col2] = aux;
	}
}

void triangularizare_3(float** A, int n) {
	int p, q;
	float max;

	for (int k = 0; k < n - 1; k++) {
		max = 0;
		for (int i = k; i < n; i++) {
			for (int j = k; j < n; j++) {
				if (fabs(A[i][j]) > max) {
					max = fabs(A[i][j]);
					p = i;
					q = j;
				}
			}
		}

		if (A[p][q] == 0) {
			printf("Matricea nu poate fi triangularizata!\n");
			exit(1);
		}

		if (p != k) {
			swapRows(A, p, k, n);
		}

		if (q != k) {
			swapCols(A, q, k, n);
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

	/*
	2 1 1
	−1 2 −1
	1 −1 2
	*/

	printf("Introduceti un numar de linii si coloane: ");
	scanf_s("%d", &n);

	float** A = allocateMatrix(n, n),
		** Y = allocateMatrix(n + 1, n + 1);

	printf("\nIntroduceti elementele matricei A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf_s("%f", &A[i][j]);
			Y[i][j] = 0.0;
		}
	}

	for (int i = 0; i < n; i++) {
		Y[i][3] = 0.0;
	}

	float det = 1.0;

	do {
		det = 1.0;

		printf("\nIntroduceti un vector nenul de componente:\n");
		for (int i = 0; i < n; i++) {
			printf("Y[%d][0] = ", i);
			scanf_s("%f", &Y[i][0]);
		}

		for (int i = 1; i <= n; i++) {
			for (int k = 0; k < n; k++) {
				for (int j = 0; j < n; j++) {
					Y[k][i] += A[k][j] * Y[j][i - 1];
				}
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				Y[i][j] = Y[i][j + 1];
			}
		}

		triangularizare_3(Y, n);

		for (int i = 0; i < n; i++) {
			det *= Y[i][i];
		}

		printf("\nDeterminant Y: %.2f\n", det);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= n; j++) {
				Y[i][j] = 0.0;
			}
		}

	} while (det == 0);

	return 0;
}
