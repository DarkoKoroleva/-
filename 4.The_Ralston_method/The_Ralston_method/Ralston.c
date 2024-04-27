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
	return ((double)pow(x, 6) / 6 - (double)23 / 10 * pow(x, 4) + (double)5 / 6 * pow(x, 3) - (double)7 / 2 * pow(x, 2) + 1.4 * x);
}

double* Ralston_method(double a, double b) {
	double B_plus = 0, B_minus=0, B1 = 0, x_plus = 0, x_minus = 0;
	double* coeff = (double*)malloc(sizeof(double)*5);
	B1 = (b - a);
	double A = 0, B = 0, C = 0, D;

	A = B1;
	B = -(a + b) * B1;
	C = (double)(b * b - a * a) / 2 * (a + b) - (double)(pow(b, 3) - pow(a, 3)) / 3;
	D = pow(B, 2) - 4 * A * C;
	x_plus = max((double)(-B + sqrt(D)) / (2 * A), (double)(-B - sqrt(D)) / (2 * A));
	x_minus = min((double)(-B + sqrt(D)) / (2 * A), (double)(-B - sqrt(D)) / (2 * A));

	B_plus = (double)((double)(pow(b, 2) - pow(a, 2)) / 2 - B1 * x_plus) / (a - b);
	B_minus = (double)((double)(pow(b, 2) - pow(a, 2)) / 2 - B1 * x_minus) / (a - b);
	coeff[0] = B_minus; coeff[1] = B_plus; coeff[2] = B1; coeff[3] = x_minus; coeff[4] = x_plus;
	return coeff;
}

void Find_accuracy(double a, double b, double* coeff) {
	double Newton_Leibniz = antiderivative(b) - antiderivative(a);
	int counter = 0, i=0;
	double e = 0.1;
	double* integrals = (double*)malloc(sizeof(double) * 25);
	integrals[0] = coeff[1] * (function(a) - function(b)) + coeff[2] * function(coeff[4]);
	double h = (double)(b - a) / 2;
	integrals[1] = (double)h / 2 * (coeff[1] * (function(a) - function(b)) + coeff[2] * function(a +coeff[4] * (double)h / 2 + (double)h / 2) + coeff[2]* function( a+h + coeff[4] * (double)h / 2 + (double)h / 2));
	while (counter != 12) {
		while (fabs(integrals[i + 1] - integrals[i]) / 3 >= e) {
			i++;
			h = (double)(b - a) / pow(2, i + 1);
			integrals[i+1] = coeff[1] * (function(a) - function(b));
			for (int k = 0; k < pow(2, i + 1); k++) {
				integrals[i + 1] += coeff[2] * function(a +h*k + coeff[4] * (double) h/2 + (double)h/2);
			}
			integrals[i + 1] = (double)h / 2 * integrals[i + 1];
		}
		printf("%15.15lf %15.15lf %15.15lf %d\n", e, integrals[i + 1], integrals[i + 1] - Newton_Leibniz, i + 1);
		//fprintf(fileERROR, "%15.15lf %15.15lf %d %15.15lf\n", e, integrals[i + 1] - Newton_Leibniz, i + 1, (double)(b - a) / pow(2, i + 1));
		counter++;
		e *= 0.1;
	}
}

int main() {
	double* coeff = (double*)malloc(sizeof(double) * 5);
	double a = -1, b = 1;
	coeff = Ralston_method(a, b);
	double I1 = coeff[1]*(function(a) - function(b)) + coeff[2] * function(coeff[4]);
	double I2 = coeff[0] * (function(a) - function(b)) + coeff[2] * function(coeff[3]);
	double I = (double)(I1 + I2) / 2;
	printf("%15.15lf", 1/ sqrt(3));

	double Newton_Leibniz = antiderivative(b) - antiderivative(a);
	Find_accuracy(a, b, coeff);

	printf("%15.15lf %15.15lf", I, Newton_Leibniz - I);
	free(coeff);
	return 0;
}