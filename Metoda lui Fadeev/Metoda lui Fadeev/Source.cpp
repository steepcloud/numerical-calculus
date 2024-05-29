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
		** Aux = allocateMatrix(n, n),
		** B = allocateMatrix(n, n);

	printf("\nIntroduceti elementele matricei A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf_s("%f", &A[i][j]);
			Aux[i][j] = A[i][j];
			B[i][j] = 0.0;
		}
	}

	float* sigma = (float*)malloc(n * sizeof(float));

	for (int i = 0; i < n; i++) {
		sigma[i] = 0.0;
	}

	for (int i = 0; i < n; i++) {
		sigma[0] += Aux[i][i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = (i != j) ? -Aux[i][j] : sigma[0] - Aux[i][j];
		}
	}

	for (int k = 1; k < n - 1; k++) {
		inmMatrix(A, B, Aux, n);

		for (int i = 0; i < n; i++) {
			sigma[k] += Aux[i][i];
		}

		sigma[k] /= (k + 1);

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				B[i][j] = (i != j) ? -Aux[i][j] : sigma[k] - Aux[i][j];
			}
		}
	}

	inmMatrix(A, B, Aux, n);

	for (int i = 0; i < n; i++) {
		sigma[n - 1] += Aux[i][i];
	}

	sigma[n - 1] /= n;

	for (int i = 0; i < n; i++) {
		printf("%.2f ", sigma[i]);
	}

	if (sigma[n - 1]) {
		printf("\n\nInversa matricei A este:\n\n");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("%.2f ", 1 / sigma[n - 1] * B[i][j]);
			}
			printf("\n");
		}
	}
	else {
		printf("\nMatricea A nu este inversabila\n");
	}

	freeMatrix(A, n);
	freeMatrix(Aux, n);
	freeMatrix(B, n);

	free(sigma);

	return 0;
}