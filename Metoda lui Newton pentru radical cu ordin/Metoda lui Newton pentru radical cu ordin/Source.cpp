#include <stdio.h>
#include <math.h>

#define ITMAX 10
#define err 0.000000001

int main() {
	double a, x = 1;
	int p, n = 1;

	printf("Introduceti o valoare pentru ordinul radicalului: ");
	scanf_s("%d", &p);

	printf("\nIntroduceti o valoare pentru numarul real pozitiv a: ");
	scanf_s("%lf", &a);

	while (fabs(pow(x, p) - a) > err && n <= ITMAX) {
		x = (1.0 / p) * ((p - 1) * x + a / (pow(x, p - 1)));

		printf("\nx = %.13f", x);
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
