#include <stdio.h>
#include <math.h>

#define ITMAX 7
#define err 0.000000001

double f(double x) {
	return x * exp(x) - 1;
}

double derivative(double x) {
	return exp(x) * (x + 1);
}

int main() {
	int n = 1;
	double x;

	printf("Introduceti o valoare pentru x: ");
	scanf_s("%lf", &x);

	while (fabs(f(x)) > err && n <= ITMAX) {
		printf("\nValoare f(x): %f", f(x));
		printf("\nValoare f'(x): %f", derivative(x));
		printf("\nValoare |f(x)|: %f", fabs(f(x)));
		printf("\nValoare f(x)/f'(x): %f", fabs(f(x)) / derivative(x));
		x = x - (f(x) / derivative(x));
		n++;

		printf("\nx = %.13f", x);
	}

	if (n > ITMAX) {
		printf("\nIn %d iteratii nu a fost realizata aproximarea dorita", ITMAX);
	}
	else {
		printf("\nAproximarea dorita este: %f", x);
	}

	return 0;
}