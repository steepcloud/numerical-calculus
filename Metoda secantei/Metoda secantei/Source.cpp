#include <stdio.h>
#include <math.h>

#define ITMAX 9
#define err 0.000000001

double f(double x) {
	return x * exp(x) - 1;
}


int main() {
	double x, x_0 = 0, x_1 = 1;
	int n = 2;

	printf("Introduceti o valoare pentru x: ");
	scanf_s("%lf", &x);

	while (fabs(f(x_1)) > err && n <= ITMAX) {
		x = x_1 - (f(x_1) * (x_1 - x_0)) / (f(x_1) - f(x_0));
		printf("\nx = %.13f", x);
		printf("\n|f(xn)|: %.13f", fabs(f(x)));
		x_0 = x_1;
		x_1 = x;
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