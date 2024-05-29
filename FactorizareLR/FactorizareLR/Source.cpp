#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void factorizareLR(float** A, float** L, float** R, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			L[i][j] = (i == j) ? 1.0 : 0.0;
			R[i][j] = A[i][j];
		}
	}

	for (int k = 0; k < n - 1; k++) {
		if (R[k][k] != 0) {
			for (int i = k + 1; i < n; i++) {
				for (int j = k + 1; j < n; j++) {
					R[i][j] -= (R[i][k] * R[k][j]) / R[k][k];
				}
				R[i][k] = R[i][k] / R[k][k];
			}
		}
		else {
			printf("Matricea nu poate fi factorizata LR cu acest algoritm.\n");
			return;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			L[i][j] = R[i][j];
			R[i][j] = 0.0;
		}
	}
}

int main() {
	int n;

	printf("Introduceti numar de linii si coloane pentru matrice: ");
	scanf_s("%d", &n);

	float** A = (float**)malloc(n * sizeof(float*));
	float** L = (float**)malloc(n * sizeof(float*));
	float** R = (float**)malloc(n * sizeof(float*));

	for (int i = 0; i < n; i++) {
		A[i] = (float*)malloc(n * sizeof(float));
	}

	for (int i = 0; i < n; i++) {
		L[i] = (float*)malloc(n * sizeof(float));
	}

	for (int i = 0; i < n; i++) {
		R[i] = (float*)malloc(n * sizeof(float));
	}
	printf("Introduceti elementele matricei:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("A[%d][%d] = ", i, j);
			scanf_s("%f", &A[i][j]);
		}
	}

	factorizareLR(A, L, R, n);

	printf("Matricea factorizata L este:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.2f ", L[i][j]);
		}
		printf("\n");
	}

	printf("\nMatricea factorizata R este:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.2f ", R[i][j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n; i++) {
		free(A[i]);
		free(L[i]);
		free(R[i]);
	}

	free(A);
	free(L);
	free(R);

	return 0;
}