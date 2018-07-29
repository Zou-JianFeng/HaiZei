#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define EPS 1e-6

double f(double x, double a, double b, double c) {
	return a * x * x + b * x + c;
}

double find_max(double a, double b, double c) {
	double head = -10000, tail = 10000, m1, m2;
	if (a > 0) {
		a = -a, b = -b, c = -c;
	}
	while (fabs(tail - head) > EPS) {
		m1 = (tail - head) / 3 + head;
		m2 = (tail - head) / 3 * 2 + head;
		if (f(m1, a, b, c) < f(m2, a, b, c)) {
			head = m1;
		} else {
			tail = m2;
		}
	}
	return head;
}

int main() {
	double a, b, c;
	while (scanf("%lf%lf%lf", &a, &b, &c) != EOF) {
		printf("%lf\n",find_max(a, b, c));
	}

	return 0;
}