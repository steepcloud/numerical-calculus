#include <stdlib.h>
#include <stdio.h>
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


void sistemLR(float** A, float* y, float* b, int n) {
	float* x = (float*)malloc(10 * sizeof(float));

	y[0] = b[0];

	for (int i = 1; i < n; i++) {
		y[i] = 0.0;

		for (int k = 0; k <= i - 1; k++) {
			y[i] += A[i][k] * y[k];
		}
		y[i] = b[i] - y[i];
	}

	x[n - 1] = y[n - 1] / A[n - 1][n - 1];
	for (int i = n - 1; i >= 0; i--) {
		x[i] = 0.0;

		for (int k = i + 1; k < n; k++) {
			x[i] += A[i][k] * x[k];
		}
		x[i] = (y[i] - x[i]) / A[i][i];
	}

	printf("Solutia sistemului este:\n");
	for (int i = 0; i < n; i++) {
		printf("\nx[%d] = %.2f", i, x[i]);
	}

	free(x);
}

void printMatrix(float** A, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.2f ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {
	int n;

	printf("Introduceti numar de linii si coloane pentru matrice: ");
	scanf_s("%d", &n);

	float** A = (float**)malloc(n * sizeof(float*));
	float** L = (float**)malloc(n * sizeof(float*));
	float** R = (float**)malloc(n * sizeof(float*));
	float** M = (float**)malloc(n * sizeof(float*));

	float* y = (float*)malloc(10 * sizeof(float));
	float* b = (float*)malloc(10 * sizeof(float));

	for (int i = 0; i < n; i++) {
		A[i] = (float*)malloc(n * sizeof(float));
		L[i] = (float*)malloc(n * sizeof(float));
		R[i] = (float*)malloc(n * sizeof(float));
		M[i] = (float*)malloc(n * sizeof(float));
	}

	printf("Introduceti elementele matricei:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("A[%d][%d] = ", i, j);
			scanf_s("%f", &A[i][j]);
		}
	}

	factorizareLR_Doolittle(A, L, R, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || i < j) {
				M[i][j] = R[i][j];
			}
			else {
				M[i][j] = L[i][j];
			}
		}
	}

	b[0] = 7;
	b[1] = 15;
	b[2] = 5;

	sistemLR(M, y, b, n);

	printf("\n\nMatricea factorizata L este:\n");
	printMatrix(L, n);

	printf("Matricea factorizata R este:\n");
	printMatrix(R, n);

	printf("Matricea A este:\n");
	printMatrix(A, n);

	for (int i = 0; i < n; i++) {
		free(A[i]);
		free(L[i]);
		free(R[i]);
		free(M[i]);
	}

	free(A);
	free(L);
	free(R);
	free(M);

	return 0;
}