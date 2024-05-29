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

int main() {
	int n;

	printf("Introduceti un numar de linii si coloane: ");
	scanf_s("%d", &n);

	float** A = allocateMatrix(n, 2 * n);
	float* u = (float*)malloc(5 * n * sizeof(float));
	float* v = (float*)malloc(5 * n * sizeof(float));

	for (int i = 0; i < n; i++) {
		u[i] = 0;
		v[i] = 0;
	}

	/*
	0 −1 1 1 0 0
	1 3 1 0 1 0
	1 1 2 0 0 1
	*/

	printf("\nIntroduceti elementele pentru matricea A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			scanf_s("%f", &A[i][j]);
		}
	}

	A[0][0] = 1 / A[0][0];

	for (int k = 0; k < n - 1; k++) {
		for (int i = 0; i < k; i++) {
			u[i] = A[i][k + 1];
			v[i] = A[k + 1][i];
		}

		double sum = 0.0;
		for (int i = 0; i < k; i++) {
			double sum2 = 0.0;

			for (int j = 0; j < k; j++) {
				sum2 += A[i][j] * u[j];
			}
			sum += v[i] * sum2;
		}

		A[k + 1][k + 1] = 1 / (A[k + 1][k + 1] - sum);

		for (int i = 0; i < k; i++) {
			sum = 0.0;

			for (int j = 0; j < k; j++) {
				sum += A[i][j] * u[j];
			}

			A[i][k + 1] = -A[k + 1][k + 1] * sum;
		}

		for (int j = 0; j < k; j++) {
			sum = 0.0;

			for (int i = 0; i < k; i++) {
				sum += v[i] * A[i][j];
			}

			A[k + 1][j] = -A[k + 1][k + 1] * sum;
		}

		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				A[i][j] += A[i][k + 1] * A[k + 1][j] / A[k + 1][k + 1];
			}
		}
	}

	printf("\nInversa matricei A este:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			printf("%.2f ", A[i][j]);
		}
		printf("\n");
	}

	freeMatrix(A, n);
	free(u);
	free(v);

	return 0;
}