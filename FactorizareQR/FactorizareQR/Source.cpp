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
		for (int j = 0; j < n; j++) {
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

void inmMatrix(float** A, float** B, float** C, int n) {
	float** Ct;

	Ct = allocateMatrix(n, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			Ct[i][j] = 0.0;
			for (int k = 0; k < n; k++) {
				Ct[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			C[i][j] = Ct[i][j];
		}
	}
}

void factorizareQR(float** A, float** Q, int n) {
	float sigma = 0.0, beta = 0.0, s = 0.0;
	float* v = (float*)malloc(n * sizeof(float));

	float** H;

	H = allocateMatrix(n, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			H[i][j] = 0.0;
		}
	}

	for (int i = 0; i < n; i++) {
		v[i] = 0.0;
	}

	identityMatrix(Q, n);

	for (int k = 0; k < n - 1; k++) {
		s = 0.0;
		for (int i = k; i < n; i++) {
			s += A[i][k] * A[i][k];
		}

		sigma = sqrt(s);

		if (sigma) {
			if (A[k][k] < 0) {
				sigma = -sigma;
			}

			v[k] = A[k][k] + sigma;
			for (int i = 0; i < k; i++) {
				v[i] = 0;
			}

			for (int i = k + 1; i < n; i++) {
				v[i] = A[i][k];
			}

			s = 0.0;
			for (int i = k; i < n; i++) {
				s += v[i] * v[i];
			}

			beta = s / 2;

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					if (i != j) {
						H[i][j] = -v[i] * v[j] / beta;
					}
					else {
						H[i][j] = 1 - v[i] * v[i] / beta;
					}
				}
			}

			inmMatrix(H, A, A, n);
			inmMatrix(Q, H, Q, n);
		}
	}

	freeMatrix(H, n);
	free(v);
}

int main() {
	int n;

	printf("Introduceti un numar de linii si coloane: ");
	scanf_s("%d", &n);

	if (n <= 0 || n >= 100) {
		return -1;
	}

	float** A, ** Q;

	A = allocateMatrix(n, n);
	Q = allocateMatrix(n, n);

	printf("Introduceti valori pentru matricea A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("A[%d][%d] = ", i, j);
			scanf_s("%f", &A[i][j]);
		}
	}

	factorizareQR(A, Q, n);

	printf("Matricea Q:\n");
	printMatrix(Q, n);

	printf("Matricea R:\n");
	printMatrix(A, n);

	return 0;
}