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

int main() {
	int n;

	printf("Introduceti un numar de linii si coloane: ");
	scanf_s("%d", &n);

	float** A = allocateMatrix(n, 2 * n),
		** S = allocateMatrix(n, n),
		** alfa = allocateMatrix(n, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			alfa[i][j] = 0.0;
		}
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

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][n + j] = (i != j) ? 0 : 1;
			S[i][j] = (i != j) ? 0 : 1;
		}
	}




	double maxi = 0.0;
	int p, q;

	for (int k = 0; k < n - 1; k++) {
		maxi = -INT_MAX;

		for (int i = k; i < n; i++) {
			for (int j = k; j < n; j++) {
				if (maxi < fabs(A[i][j])) {
					maxi = fabs(A[i][j]);
					p = i;
					q = j;
				}
			}
		}



		printf("\nmaxi: %.2f\n", maxi);
		if (A[p][q]) {
			if (p != k) {
				swapRows(A, p, k, 2 * n);
			}

			if (q != k) {
				swapCols(A, q, k, n);
				swapCols(S, q, k, n);
			}


			for (int i = 0; i < n; i++)
				if (i != k)
				{
					for (int j = k + 1; j < 2 * n; j++) {
						A[i][j] = A[i][j] - (A[i][k] * A[k][j]) / A[k][k];
					}
					A[i][k] = 0;
				}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					printf("%.0f ", A[i][j]);
				}
				printf("\n");
			}

			for (int j = 2 * n - 1; j >= k; j--) {
				A[k][j] /= A[k][k];
			}

		}
		else {
			printf("\nMatricea A nu este inversabila.\n");
			return -1;
		}
	}

	if (A[n - 1][n - 1]) {
		for (int i = 0; i < n - 1; i++) {
			for (int j = n; j < 2 * n; j++) {
				A[i][j] = A[i][j] - (A[i][n - 1] * A[n - 1][j]) / A[n - 1][n - 1];
			}
			A[i][n - 1] = 0;
		}

		for (int j = 2 * n - 1; j >= n; j--) {
			A[n - 1][j] /= A[n - 1][n - 1];
		}
	}
	else {
		printf("\nMatricea A nu este inversabila.\n");
		return -1;
	}



	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			for (int k = 0; k < n; k++) {
				alfa[i][j] += S[i][k] * A[k][n + j];
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.2f ", alfa[i][j]);
		}
		printf("\n");
	}

	freeMatrix(A, n);

	return 0;
}