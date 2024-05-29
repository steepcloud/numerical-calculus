#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITMAX 100
#define EPSILON 1e-3

double bernoulli_method(double* coefficients, int n, double epsilon, int* iterations) {
	double* y = (double*)malloc((n + 1) * sizeof(double));

	if (y == NULL) {
		printf("Memorie insuficienta!\n");
		return 1;
	}

	y[0] = n;
	y[1] = -coefficients[1] / coefficients[0];

	for (int i = 2; i <= n - 1; i++) {
		double sum = 0;
		for (int j = 1; j <= i - 1; j++) {
			sum += y[j] * coefficients[i - j];
		}
		y[i] = -(coefficients[i] / coefficients[0] + sum) / y[1];
	}

	int m = 0;
	double yn = y[n], yn1 = 0;
	double x;
	
	do {
		yn1 = yn;
		double sum = 0;
		for (int i = 0; i <= n; i++) {
			sum += y[i] * pow(yn1, n - i);
		}

		yn = yn1 - sum / (n * coefficients[0] * pow(yn1, n - 1));
		x = yn / yn1;
		m++;
	} while (fabs(coefficients[0] * pow(yn, n) + coefficients[1] * pow(yn, n - 1) + coefficients[2]) >= epsilon && m < ITMAX);

	*iterations = m;

	if (m > ITMAX) {
		printf("Numarul maxim de iteratii ajuns.\n");
		return -1;
	}
	else {
		printf("x = %.13lf\n", x);
		return yn;
	}
}

int main() {
	int n;

	printf("Introduceti gradul ecuatiei: ");
	scanf_s("%d", &n);

	double* coefficients = (double*)malloc((n + 1) * sizeof(double));
	
	printf("Introduceti coeficientii ecuatiei: ");
	for (int i = 0; i <= n; i++) {
		scanf_s("%lf", &coefficients[i]);
	}

	double epsilon;
	printf("Introduceti eroarea epsilon: ");
	scanf_s("%lf", &epsilon);

	int iterations;
	double root = bernoulli_method(coefficients, n, epsilon, &iterations);

	if (root != -1) {
		printf("Aproximatia: %.13lf\n", root);
		printf("Numarul de iteratii: %d\n", iterations);
	}

	free(coefficients);

	return 0;
}