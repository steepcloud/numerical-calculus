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

	freeMatrix(Ct, n);
}

int main() {
	int n;

	/*
	2 1 0 0
	3 2 0 0
	1 1 3 4
	2 −1 2 3
	*/

	printf("Introduceti un numar de linii si coloane: ");
	scanf_s("%d", &n);

	float** A = allocateMatrix(n, n),
		** B = allocateMatrix(n, n);

	printf("\nIntroduceti elementele matricei A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf_s("%f", &A[i][j]);
		}
	}

	float* s = (float*)malloc(n * sizeof(float));
	float* sigma = (float*)malloc(n * sizeof(float));

	for (int i = 0; i < n; i++) {
		s[i] = 0.0;
		sigma[i] = 0.0;
	}

	identityMatrix(B, n);

	for (int k = 0; k < n; k++) {
		inmMatrix(B, A, B, n);

		for (int i = 0; i < n; i++) {
			s[k] += B[i][i];
		}
	}

	sigma[0] = s[0];

	for (int k = 1; k < n; k++) {
		for (int i = 0; i < k; i++) {
			sigma[k] += pow(-1, i + 2) * s[i] * sigma[k - i - 1];
		}
		sigma[k] = (sigma[k] + pow(-1, k + 2) * s[k]) / (k + 1);
	}

	for (int i = 0; i < n; i++) {
		printf("%.2f ", sigma[i]);
	}
	return 0;
}