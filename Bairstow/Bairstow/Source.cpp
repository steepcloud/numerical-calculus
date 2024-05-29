#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 1e-9

void solve_quadratic(double a, double b, double c) {
	double delta = b * b - 4 * a * c;

	if (fabs(delta) < EPSILON) {
		double root = -b / (2 * a);
		printf("Radacina: %.13lf\n", root);
	}
	else if (delta > 0) {
		double root1 = (-b + sqrt(delta)) / (2 * a);
		double root2 = (-b - sqrt(delta)) / (2 * a);
		printf("Radacina 1: %.13lf\nRadacina 2: %.13lf\n", root1, root2);
	}
	else {
		double real_part = -b / (2 * a);
		double imag_part = sqrt(fabs(delta)) / (2 * a);
		printf("Radacini: %.13lf + %.13lfi, %.13lf - %.13lf\n", real_part, imag_part, real_part, imag_part);
	}
}

void bairstow(double* a, int n, double p, double q, double epsilon) {
	while (n >= 3) {
		double* b = (double*)malloc((n + 1) * sizeof(double));
		double* c = (double*)malloc((n + 1) * sizeof(double));

		if (b == NULL || c == NULL) {
			printf("Memorie insuficienta!\n");
			exit(1);
		}

		do {
			double b0 = a[0];
			double b1 = a[1] - p * b0;

			b[0] = b0;
			b[1] = b1;

			for (int i = 2; i <= n; i++) {
				b[i] = a[i] - p * b[i - 1] - q * b[i - 2];
			}

			double c0 = b[0];
			double c1 = b[1] - p * c0;

			c[0] = c0;
			c[1] = c1;

			for (int i = 2; i <= n - 1; i++) {
				c[i] = b[i] - p * c[i - 1] - q * c[i - 2];
			}

			double delta = (c[n - 2] * c[n - 2]) - (c[n - 3] * c[n - 1]) + (c[n - 3] * b[n - 1]);
			double P = -(b[n - 1] * c[n - 2]) + (b[n] * c[n - 3]);
			double Q = -(b[n] * c[n - 2]) + (b[n - 1] * c[n - 1]) - (b[n - 1] * b[n - 1]);

			p -= P / delta;
			q -= Q / delta;
		} while (fmax(fabs(b[n - 1]), fabs(b[n] + p * b[n - 1])) >= epsilon);

		printf("Radacinile lui x^2 + %.13lfx + %.13lf = 0:\n", p, q);
		solve_quadratic(1, p, q);

		n -= 2;

		for (int i = 0; i <= n; i++) {
			a[i] = b[i];
		}

		free(b);
		free(c);
	}

	if (n == 2) {
		printf("Radacinile lui %.13lfx^2 + %.13lfx + %.13lf = 0:\n", a[0], a[1], a[2]);
		solve_quadratic(a[0], a[1], a[2]);
	}
	else if (n == 1) {
		printf("Radacina: %.13lf\n", -a[1] / a[0]);
	}
}

int main() {
	int n;

	printf("Introduceti ordinul ecuatiei: ");
	scanf_s("%d", &n);

	double* coefficients = (double*)malloc((n + 1) * sizeof(double));

	if (coefficients == NULL) {
		printf("Memorie insuficienta!\n");
		return 1;
	}

	printf("Introduceti coeficientii ecuatiei: ");
	
	for (int i = 0; i <= n; i++) {
		scanf_s("%lf", &coefficients[i]);
	}

	double p, q, epsilon;
	printf("Introduceti aproximatiile initiale p si q: ");
	scanf_s("%lf %lf", &p, &q);

	printf("Introduceti eroarea epsilon: ");
	scanf_s("%lf", &epsilon);

	bairstow(coefficients, n, p, q, epsilon);

	free(coefficients);

	return 0;
}