#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include < malloc.h >
#include <conio.h>
#define MEMORY_ERROR 2 

double function(double x) {
	return (pow(x, 5) - 9.2 * pow(x, 3) + 2.5 * pow(x, 2) - 7 * x + 1.4);
}

double antiderivative(double x) {
	return ((double)pow(x, 6)/6 - (double)23/10 * pow(x, 4) + (double)5/6 * pow(x, 3) - (double)7/2 * pow(x,2) + 1.4 * x);
}

double the_trapezoidal_rule(double a, double b, int n) {
	double result = 0, x1 = a;
	double step = (b - a) / n;
	double x2 = x1 + step;

	while (x2 <= b) {
		result += (function(x1) + function(x2)) / 2 * (x2 - x1);
		x1 = x2;
		x2 += step;
	}

	return result;
}

int main() {
	FILE* fileERROR;
	fileERROR = fopen("ERROR.txt", "w");
	double e = 0.1;
	int counter = 0, i=0;
	double intagrals[25];
	double a = 0, b = 1;
	intagrals[0] = the_trapezoidal_rule(a, b, 0);
	intagrals[1] = the_trapezoidal_rule(a, b, 1);

	double Newton_Leibniz = antiderivative(b) - antiderivative(a);

	while (counter != 13) {
		while (fabs(intagrals[i + 1] - intagrals[i]) / 3 >= e) {
			i++;
			intagrals[i+1] = the_trapezoidal_rule(a, b, pow(2, i+1));
		}
		printf("%15.15lf %15.15lf %15.15lf %d %15.15lf\n", e, intagrals[i+1], intagrals[i+1] - Newton_Leibniz, i+1, (double)(b-a)/pow(2, i+1));
		fprintf(fileERROR, "%15.15lf %15.15lf %d %15.15lf\n", e, intagrals[i + 1] - Newton_Leibniz, i+1, (double)(b - a) / pow(2, i + 1));
		counter++;
		e *= 0.1;
	}
	fclose(fileERROR);

	double result;
	for (int i = 0; i < 15; i++) {
		result = the_trapezoidal_rule(a, b, i);
		printf("%15.15lf %d \n", result - Newton_Leibniz, i);
	}


	return 0;
}