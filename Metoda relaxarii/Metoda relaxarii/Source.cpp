#include <stdlib.h>
#include <stdio.h>
#include <cmath>

#define EPSILON 1e-6
#define ITMAX 100

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

int main() {
	int n;

	printf("Introduceti ordinul sistemului: ");
	scanf_s("%d", &n);

	if (n <= 0 || n >= 100) {
		return -1;
	}

	float** A;

	A = allocateMatrix(n, n);

	printf("Introduceti valorile sistemului:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("A[%d][%d] = ", i, j);
			scanf_s("%f", &A[i][j]);
		}
	}

	// 1 0.1 0.1
	// 0.2 1 0.1
	// 0.2 0.2 1

	int m = 1;

	float* R = (float*)malloc(n * sizeof(float));
	float* b = (float*)malloc(n * sizeof(float));
	float* x = (float*)malloc(n * sizeof(float));

	b[0] = 1.2;
	b[1] = 1.3;
	b[2] = 1.4;

	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}

	double sum = 0.0;
	for (int i = 0; i < n; i++) {
		sum = 0.0;

		for (int j = 0; j < n; j++) {
			if (i != j) {
				sum += A[i][j] * x[j];
			}
		}
		R[i] = b[i] - x[i] + sum;
	}

	int p = 0;
	double maxi = 0.0;

	for (int i = 0; i < n; i++) {
		if (maxi < fabs(R[i])) {
			maxi = fabs(R[i]);
			p = i;
		}
	}
	while (maxi >= EPSILON && m <= ITMAX) {
		maxi = 0;
		for (int i = 0; i < n; i++) {
			if (maxi < fabs(R[i])) {
				maxi = fabs(R[i]);
				p = i;
			}
		}

		x[p] += R[p];
		for (int q = 0; q < n; q++) {
			if (q != p) {
				R[q] = R[q] + A[q][p] * R[p];
			}
		}
		R[p] = 0;

		m++;
	}

	if (m > ITMAX) {
		printf("\nIn %d iteratii nu este obtinuta aproximarea dorita.\n");
	}
	else {
		printf("Aproximarea obtinuta este:\n");
		for (int i = 0; i < n; i++) {
			printf("x[%d] = %.2f\n", i, x[i]);
		}
	}

	return 0;
}