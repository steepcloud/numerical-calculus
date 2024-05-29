#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-6

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

	float* b = (float*)malloc(n * sizeof(float));
	float* x = (float*)malloc(n * sizeof(float));
	float* y = (float*)malloc(n * sizeof(float));

	b[0] = 1.2;
	b[1] = 1.3;
	b[2] = 1.4;

	for (int i = 0; i < n; i++) {
		x[i] = 0;
	}

	for (int i = 0; i < n; i++) {
		y[i] = 0;
	}

	double sum = 0.0, q = 0.0;

	double maxi = 0.0;
	for (int i = 0; i < n; i++) {
		sum = 0.0;

		for (int j = 0; j < n; j++) {
			if (i != j) {
				sum += fabs(A[i][j]);
			}
		}

		maxi = sum / fabs(A[i][i]);
		if (maxi > q) {
			q = maxi;
		}
	}

	int m = 0, k = 0;

	if (q < 1) {
		m = 1;

		for (int i = 0; i < n; i++) {
			sum = 0.0;

			for (int j = 0; j < n; j++) {
				if (i != j) {
					sum += A[i][j] * x[j];
				}
			}

			y[i] = (b[i] - sum) / A[i][i];
		}

		maxi = fabs(x[0] - y[0]);

		for (int i = 0; i < n; i++) {
			if (maxi < fabs(x[i] - y[i])) {
				maxi = fabs(x[i] - y[i]);
			}
		}

		k = 1;

		while (pow(q, k) * maxi / (1 - q) >= EPSILON) {
			k++;
		}

		for (m = 2; m <= k; m++) {
			for (int i = 0; i < n; i++) {
				x[i] = y[i];
			}

			for (int i = 0; i < n; i++) {
				sum = 0.0;

				for (int j = 0; j < n; j++) {
					if (i != j) {
						sum += A[i][j] * x[j];
					}
				}

				y[i] = (b[i] - sum) / A[i][i];
			}
		}
	}
	else {
		printf("\nNu este asigurata convergenta algoritmului.");
		return -1;
	}

	printf("\nUltima aproximatie calculata este:\n");
	for (int i = 0; i < n; i++) {
		printf("x[%d] = %.2f\n", i, y[i]);
	}

	printf("\nNumarul de iteratii efectuate este: %d\n", k);

	freeMatrix(A, n);

	free(b);
	free(x);
	free(y);

	return 0;
}