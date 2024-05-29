#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EPSILON 1e-9

float** allocateMatrix(int rows, int cols) {
	float** A = (float**)malloc(rows * sizeof(float*));
	for (int i = 0; i < rows; i++) {
		A[i] = (float*)malloc(cols * sizeof(float));
	}

	return A;
}

int main() {
	int n, k;

	printf("Dati ordinul sistemului: ");
	scanf_s("%d", &n);

	float** A = allocateMatrix(n, n);
	float* b = (float*)malloc(n * sizeof(float));
	float* x = (float*)malloc(n * sizeof(float));
	float* y = (float*)malloc(n * sizeof(float));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("A[%d][%d] = ", i, j);
			scanf_s("%f", &A[i][j]);
		}
	}

	b[0] = -1.2;
	b[1] = -1.3;
	b[2] = -1.4;

	// vector aproximare initiala a solutiei?
	for (int i = 0; i < n; i++) {
		printf("x[%d] = ", i);
		scanf_s("%f", &x[i]);
	}

	double sum = 0.0;
	for (int j = 0; j < n; j++) {
		if (j != 1) {
			sum += fabs(A[1][j]);
		}
	}
	
	double q = sum / fabs(A[1][1]);
	double maxi = 0.0;

	for (int i = 1; i < n; i++) {
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

	if (q < 1) {
		int m = 1;

		for (int i = 0; i < n; i++) {
			sum = 0.0;
			for (int j = 0; j < i - 1; j++) {
				sum += A[i][j] * y[j];
			}
			for (int j = i + 1; j < n; j++) {
				sum += A[i][j] * x[j];
			}

			y[i] = (b[i] - sum) / A[i][i];
		}

		maxi = fabs(x[0] - y[0]);

		for (int i = 1; i < n; i++) {
			if (maxi < fabs(x[i] - y[i])) {
				maxi = fabs(x[i] - y[i]);
			}
		}

		k = 1;

		while (pow(q, k) * maxi / (1 - q) > EPSILON) {
			k++;
		}

		for (m = 1; m < k; m++) {
			for (int i = 0; i < n; i++) {
				x[i] = y[i];
			}
			for (int i = 0; i < n; i++) {
				sum = 0.0;
				for (int j = 0; j < i; j++) {
					sum += A[i][j] * y[j];
				}
				for (int j = i + 1; j < n; j++) {
					sum += A[i][j] * x[j];
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

	printf("Numarul de iteratii efectuate este: %d", k);

	return 0;
}