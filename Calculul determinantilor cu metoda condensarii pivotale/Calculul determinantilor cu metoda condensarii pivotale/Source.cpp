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

	printf("Introduceti numarul de linii si coloane: ");
	scanf_s("%d", &n);

	float** A = allocateMatrix(n, n),
		** B = allocateMatrix(n, n);

	printf("\nIntroduceti elementele pentru matricea A:\n");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//printf("A[%d][%d] = ", i, j);
			scanf_s("%f", &A[i][j]);
		}
	}

	/*
	0 1 0 −1 2 3
	1 2 1 −1 2 1
	2 0 3 1 2 2
	1 −1 2 0 2 1
	2 −2 1 −1 1 0
	3 2 2 1 0 −2
	*/

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			B[i][j] = 0;
		}
	}

	int t = 1, p, q;
	double maxi = 0.0;

	while (n >= 3) {
		maxi = 0.0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (maxi < fabs(A[i][j])) {
					maxi = fabs(A[i][j]);
					p = i;
					q = j;
				}
			}
		}

		if (A[p][q] == 0) {
			printf("\ndet(A) = 0\n");
			return -1;
		}
		else {
			if (p != 0) {
				//printf("\nSe permuta liniile 0 si %d\n", p);
				swapRows(A, 0, p, n);
				t = -t;
			}

			if (q != 0) {
				//printf("\nSe permuta coloanele 0 si %d\n", q);
				swapCols(A, 0, q, n);
				t = -t;
			}

			for (int i = 2; i < n; i++) {
				for (int j = 0; j < n; j++) {
					A[i][j] = A[i][j] / A[0][0];
				}
			}

			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - 1; j++) {
					B[i][j] = A[0][0] * A[i + 1][j + 1] - A[i + 1][0] * A[0][j + 1];
				}
			}

			n--;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					A[i][j] = B[i][j];
				}
			}
		}
	}

	printf("\ndet(A) = %0.f\n", t * (A[0][0] * A[1][1] - A[0][1] * A[1][0]));

	return 0;
}