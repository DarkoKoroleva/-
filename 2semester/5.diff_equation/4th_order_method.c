#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include < malloc.h >
#include <conio.h>
#define MEMORY_ERROR 2 


double function(double x, double y) {
	return (x == 1 ? -1 : ((double) 2*y / (x * log(x)) + (double)1/x));
}

double solve(double x) {
	return (pow(log(x), 2) - log(x));
}

double* get_grid(double a, double b, int n) {
	double* grid = (double*)malloc((n+1) * sizeof(double));
	for (int k = 0; k <= n; k++) {
		grid[k] = a + (double)(b - a) / n * k; //x	
	}
	return grid;
}

double order_method(double x, double y, double x2, int n) {
	double h = (double)(x2 - x) / n, k1, k2, k3, k4;
	double y_new = y;
	for (int i = 0; i < n; i++) { //вычисл€ю у_i при 2^i разбиении
		k1 = function(x + i * h, y_new);
		k2 = function(x + i * h + h / 2, y_new + (double)h * k1 / 2);
		k3 = function(x + i * h + h / 2, y_new + (double)h * k2 / 2);
		k4 = function(x + (i+1) * h, y_new + h * k3);
		y_new = y_new + (double)h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
	}
	return y_new;
}


int counter;

double find_accuracy(double a, double y0, double b, double e) {
	double y_new1 = order_method(a, y0, b, pow(2, 0));
	double y_new = order_method(a, y0, b, pow(2, 1));
	double error = 0;
	counter = 1;
	double q = fabs(y_new1 - y_new) / 15;
	while ((fabs(y_new1 - y_new) / 15 >= e)) {
		counter++;
		y_new1 = y_new;
		y_new = order_method(a, y0, b, pow(2, counter));
	}

	if (fabs(y_new1 - y_new) > error)
		error = fabs(y_new1 - y_new);
	return error;
	//printf("%15.15lf %15.15lf %d \n",  e, fabs(y_new - solve(b)), counter);
}


int main() {
	double a = 2; double b = 3;
	int n = 2;
	double* grid = (double*)malloc(sizeof(double) * (n+1));
	
	printf("\n\n");
	for (int n = 20; n < 21; n++) {
		double* grid = (double*)malloc(sizeof(double) * (n + 1));
		grid = get_grid(a, b, n);
		double y = solve(grid[0]);
		printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[0], y, y, fabs(y - solve(grid[0])));
		for (int i = 0; i < n; i++) {
			y = order_method(grid[i], y, grid[i+1], 1);
			printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[i + 1], y, solve(grid[i + 1]), fabs(y - solve(grid[i])));
		}
		
		free(grid);
	}

	printf("\n\n");

	for (int n = 10; n < 11; n++) {
		double* grid = (double*)malloc(sizeof(double) * (n + 1));
		grid = get_grid(a, b, n);
		double y = solve(grid[0]);
		printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[0], y, y, fabs(y - solve(grid[0])));
		for (int i = 0; i < n; i++) {
			y = order_method(grid[i], y, grid[i + 1], 1);
			printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[i + 1], y, solve(grid[i + 1]), fabs(y - solve(grid[i])));
		}

		free(grid);
	}

	printf("\n\n");

	for (int n = 1; n < 14; n++) {
		int k = pow(2, n);
		double* grid = (double*)malloc(sizeof(double) * (k+1));
		
		grid = get_grid(a, b, k);
		double y = solve(grid[0]);

		y = order_method(grid[0], solve(grid[0]), grid[k], k);

		printf("%15.15lf %15.15lf\n", (double)(b-a)/k, fabs(y - solve(grid[k])) );

		free(grid);
	}

	int nodes = 10;
	printf("\n\n");
	double e, error = 0, new_error=0;

	for (int i = 1; i < 16; i++) {
		grid = get_grid(a, b, nodes);
		double y = solve(grid[0]);
		e = pow(10, -i);
		error = 0;
		for (int n = 0; n < nodes; n++) {
			new_error = find_accuracy(grid[n], solve(grid[n]), grid[n + 1], e);
			error = max(new_error, error);
		}
		printf("%15.15lf %15.15lf\n", e, error);
		free(grid);
	}
	

	n=10;
	int count = 0;
	grid = get_grid(a, b, n);
	double y = solve(grid[0]);

	for (int i = 1; i < 16; i++) {
		grid = get_grid(a, b, nodes);
		double y = solve(grid[0]);
		e = pow(10, -i);
		error = 0;
		for (int n = 0; n < nodes; n++) {
			new_error = find_accuracy(grid[n], solve(grid[n]), grid[n + 1], e);
			count = max(count, counter);
		}
		printf("%15.15lf %d\n", e, count);
		free(grid);
	}

	
	return 0;
}

