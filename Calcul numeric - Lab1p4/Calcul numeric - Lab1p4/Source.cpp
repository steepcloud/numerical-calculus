#include <stdio.h>
#include <math.h>

#define ITMAX 30
#define err 1e-9

double f(double x) {
	return exp(-x);
}

int main() {
	int n = 0;
	double x;

	printf("Introduceti o valoare pentru x: ");
	scanf_s("%lf", &x);

	while (fabs(x - f(x)) > err && n <= ITMAX) {
		printf("\nn: %d", n);
		printf("\nx: %.13f", x);
		printf("\n|x - f(x)|: %.13f\n", fabs(x - f(x)));
		x = f(x);
		n++;
	}

	if (n > ITMAX) {
		printf("\nIn %d iteratii nu a fost realizata aproximarea dorita", ITMAX);
	}
	else {
		printf("\nAproximarea dorita este: %.13f", x);
	}
	return 0;
}