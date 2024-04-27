#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include < malloc.h >
#include <conio.h>
#define MEMORY_ERROR 2 


double function(double x, double y) {
	return (x == 1 ? -1 : ((double)2 * y / (x * log(x)) + (double)1 / x));
}

double solve(double x) {
	return (pow(log(x), 2) - log(x));
}

double* get_grid(double a, double b, int n) {
	double* grid = (double*)malloc((n + 1) * sizeof(double));
	for (int k = 0; k <= n; k++) {
		grid[k] = a + (double)(b - a) / n * k; //x	
	}
	return grid;
}

double method_Runge(double x, double y, double x2, int n) {
	double h = (double)(x2 - x) / n, k1, k2, k3, k4;
	double y_new = y;
	for (int i = 0; i < n; i++) { //вычисляю у_i при 2^i разбиении
		k1 = function(x + i * h, y_new);
		k2 = function(x + i * h + h / 2, y_new + (double)h * k1 / 2);
		k3 = function(x + i * h + h / 2, y_new + (double)h * k2 / 2);
		k4 = function(x + (i + 1) * h, y_new + h * k3);
		y_new = y_new + (double)h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
	}
	return y_new;
}


double order_method(double x, double y_current, double y_prev, double y_prev2, double y_prev3, double x_next) {
	double h = x_next - x;
	double y_next;
	y_next = y_current + (double)h / 24 * (55* function(x, y_current) - 59 * function(x - h, y_prev) + 37* function(x - 2*h, y_prev2) - 9* function(x - 3*h, y_prev3)); //явно
	y_next = y_current + (double)h / 24 * (9 * function(x+h, y_next) + 19 * function(x, y_current) - 5 * function(x - h, y_prev) + function(x - 2 * h, y_prev2));//неявно
	return y_next;
}


int main() {

	double a = 2, b = 3;


	FILE* file;
	file = fopen("solution5.txt", "r");
	double x_prev3, y_prev3, x_prev2, y_prev2, x_prev, y_prev, x_current, y_current;
	fscanf(file, "%lf %lf\n%lf %lf\n%lf %lf\n%lf %lf", &x_prev3, &y_prev3, &x_prev2, &y_prev2, &x_prev, &y_prev, &x_current, &y_current);
	int n = 20;
	double* grid = (double*)malloc(sizeof(double) * (n + 1));
	grid = get_grid(a, b, n);
	double y_next;

	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_prev3, y_prev3, solve(x_prev3), fabs(y_prev3 - solve(x_prev3)));
	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_prev2, y_prev2, solve(x_prev2), fabs(y_prev2 - solve(x_prev2)));
	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_prev, y_prev, solve(x_prev), fabs(y_prev - solve(x_prev)));
	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_current, y_current, solve(x_current), fabs(y_current - solve(x_current)));
	for (int i = 3; i < n; i++) {
		//order_method(double x, double y_current, double y_prev, double y_prev2, double y_prev3, double x_next) 
		y_next = order_method(grid[i], y_current, y_prev, y_prev2, y_prev3, grid[i + 1]);
		printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[i + 1], y_next, solve(grid[i + 1]), fabs(y_next - solve(grid[i+1])));

		y_prev3 = y_prev2;
		y_prev2 = y_prev;
		y_prev = y_current;
		y_current = y_next;
	}
	free(grid);
	fclose(file);

	printf("\n\n");

	file = fopen("solution10.txt", "r");
	fscanf(file, "%lf %lf\n%lf %lf\n%lf %lf\n%lf %lf", &x_prev3, &y_prev3, &x_prev2, &y_prev2, &x_prev, &y_prev, &x_current, &y_current);
	n = 10;
	grid = (double*)malloc(sizeof(double) * (n + 1));
	grid = get_grid(a, b, n);

	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_prev3, y_prev3, solve(x_prev3), fabs(y_prev3 - solve(x_prev3)));
	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_prev2, y_prev2, solve(x_prev2), fabs(y_prev2 - solve(x_prev2)));
	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_prev, y_prev, solve(x_prev), fabs(y_prev - solve(x_prev)));
	printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", x_current, y_current, solve(x_current), fabs(y_current - solve(x_current)));
	for (int i = 3; i < n; i++) {
		//order_method(double x, double y_current, double y_prev, double y_prev2, double y_prev3, double x_next) 
		y_next = order_method(grid[i], y_current, y_prev, y_prev2, y_prev3, grid[i + 1]);
		printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[i + 1], y_next, solve(grid[i + 1]), fabs(y_next - solve(grid[i + 1])));

		y_prev3 = y_prev2;
		y_prev2 = y_prev;
		y_prev = y_current;
		y_current = y_next;
	}
	free(grid);
	fclose(file);

	printf("\n\n");

	for (int n = 3; n < 14; n++) {
		int k = pow(2, n);
		grid = (double*)malloc(sizeof(double) * (k + 1));
		grid = get_grid(a, b, k);

		x_prev3 = grid[0];
		y_prev3 = solve(grid[0]);
		x_prev2 = grid[1];
		y_prev2 = method_Runge(x_prev3, y_prev3, x_prev2, 1);
		x_prev = grid[2];
		y_prev = method_Runge(x_prev2, y_prev2, x_prev, 1);
		x_current = grid[3];
		y_current = method_Runge(x_prev, y_prev, x_current, 1);
		
		
		double eps = 0;
		for (int i = 3; i < n; i++) {
			//order_method(double x, double y_current, double y_prev, double y_prev2, double y_prev3, double x_next) 
			y_next = order_method(grid[i], y_current, y_prev, y_prev2, y_prev3, grid[i + 1]);
			//printf("%15.15lf %15.15lf %15.15lf %15.15lf\n", grid[i + 1], y_next, solve(grid[i + 1]), fabs(y_next - solve(grid[i + 1])));
			eps = max(eps, fabs(y_next - solve(grid[i + 1])));
			y_prev3 = y_prev2;
			y_prev2 = y_prev;
			y_prev = y_current;
			y_current = y_next;
		}

		printf("%15.15lf %15.15lf\n", (double)(b - a) / k, eps);

		free(grid);
	}

	return 0;
}