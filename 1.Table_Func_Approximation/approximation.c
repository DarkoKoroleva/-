#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include < malloc.h >
#include <conio.h>
#define MEMORY_ERROR 2 
const double PI = 3.141592653589793;

double function(double x) {
	return (pow(x, 3) - exp(x) + 1);
}

double** createArray(int n, int m) {
	double** grid = (double**)malloc(n * sizeof(double*));
	if (grid == NULL) { 
		return MEMORY_ERROR;
	}
	for (int i = 0; i < n; i++) {
		grid[i] = (double*)malloc(m * sizeof(double));
	}
	return grid;
}

void freeArray(double** array, int n) {
	for (int i = 0; i < n; i++) {
		free(array[i]);
	}
	free(array);
}

void printArray(double** array, int n, int m) {
	FILE* file;
	file = fopen("NODE.txt", "w");
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fprintf(file, "%15.15lf ", array[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

double** nodes(double a, double b, int n) {
	double** grid = createArray(n+1, 2);
	for (int k = n; k >= 0; k--) {
		double t = cos((double)PI * (2 * k + 1) / (2 * (n+1)));
		grid[n - k][0] = (a + b) / 2 + (b - a) / 2 * t; //x	
	}
	for (int k = 0; k <= n; k++) {
		grid[k][1] = function(grid[k][0]); //y
		//printf("%15.15lf %15.15lf\n", grid[k][0], grid[k][1]);
	}
	return grid;
}

/*double* divided_differences(double** grid, int n) {
	double* div_dif = (double*)malloc(n * sizeof(double));
	for (int k = 0; k < n; k++) {
		double multiplication = 1, summ = 0;
		for (int j = 0; j <= k+1; j++) {
			multiplication = 1;
			for (int i = 0; i <= k+1; i++) {
				if (i != j) {
					multiplication *= (grid[j][0] - grid[i][0]); //Xkj-Xki
				}
			}
			summ += grid[j][1] / multiplication;
		}
		div_dif[k] = summ;
	}
	for (int i = 0; i < n; i++) {
		printf("%15.16lf ", div_dif[i]);
	}

	return div_dif;
}*/

double* divided_differences(double** grid, int n) {
	double* div_dif = (double*)malloc(n * sizeof(double));
	double* div_dif1 = (double*)malloc(n * sizeof(double));
	double* div_dif2 = (double*)malloc(n * sizeof(double));
	
	for (int i = 0; i <= n; i++) { // 1
		div_dif1[i] = grid[i][1];
	}
	//int counter = 0;
	for (int k = 1; k <= n; k++) {
		for (int i = 0; i <= n-k; i++) {
			div_dif2[i] = (div_dif1[i + 1] - div_dif1[i]) / (grid[i + k][0] - grid[i][0]);
			div_dif1[i] = div_dif2[i];
			//printf("%15.16lf  ", div_dif1[i]);
		}
		//printf("\n");
		div_dif[k - 1] = div_dif2[0];
		div_dif1[n - k + 1] = 0;
		//printf("%15.16lf\n", div_dif[k - 1]);
	}
	for (int i = 0; i < n; i++) {
		printf("%15.16lf ", div_dif[i]);
	}
	return div_dif;
}

int count;

double Newton_method(double* div_dif, double** grid, int n, double x) {
	double value;
	//Pn(x)= y0 + [y0, y1](x−x0) + [y0, y1, y2](x−x0)(x−x1) + ... + [y0, ..., yn] П(i=0->n-1)(x−xi)
	//double P = grid[0][1] + div_dif[0] * (x - grid[0][0])  + ... + div_dif[n - 1] * (x - grid[0][0]) *...*(x - grid[n - 1][0]);
	double P = grid[0][1]; //y0
	for (int k = 0; k < n; k++) {
		double multi = 1;
		for (int i = 0; i <= k; i++) {
			multi *= (x - grid[i][0]);
		}
		P += div_dif[k] * multi;
	}
	value = P;
	return value;
}

int main() {
	FILE* file;
	file = fopen("POLY.txt", "w");

	int n = 6; // !!! 6
	double a = 1, b = 5, x;
	double** grid = nodes(a, b, n); //чебышевская сетка
	printArray(grid, n+1, 2);
	double* div_dif = (double*)malloc(n * sizeof(double)); //разделенные разности для м ньютона
	div_dif = divided_differences(grid, n);
	double valuePoly = Newton_method(div_dif, grid, n, a); 
	fprintf(file, "%15.16lf %15.16lf\n", a, valuePoly); //записываю границу а
	
	for (x = a; x < grid[0][0]; x += 0.01) { //записываю все значения полинома до первого узла
		valuePoly = Newton_method(div_dif, grid, n, x);
		fprintf(file, "%15.16lf %15.16lf\n", x, valuePoly);
	}

	for (int i = 0; i < n-1; i++) {
		x = grid[i][0];
		for (x = grid[i][0]; x < grid[i + 1][0]; x += 0.01) { //записываю все значения полинома по сетке
			valuePoly = Newton_method(div_dif, grid, n, x);
			fprintf(file, "%15.16lf %15.16lf\n", x, valuePoly);
		}	
	}

	for (x = grid[n-1][0]; x < b; x += 0.01) { //записываю все значения полинома после последнего узла
		valuePoly = Newton_method(div_dif, grid, n, x);
		fprintf(file, "%15.16lf %15.16lf\n", x, valuePoly);
	}

	valuePoly = Newton_method(div_dif, grid, n, b);
	fprintf(file, "%15.16lf %15.16lf\n", b, valuePoly); //записываю границу в

	free(div_dif);
	freeArray(grid, n, 2);
	//freeArray(values, n, 2);
	fclose(file);
	
	FILE* fileERROR;
	fileERROR = fopen("ERROR.txt", "w");
	double error[44];
	int node;
	for (node = 3; node < 44; node++) { //считаю зависимость ошибки от числа узлов
		double a = 1, b = 5, x;
		double** grid = nodes(a, b, node);
		double* div_dif = (double*)malloc(node* sizeof(double));
		div_dif = divided_differences(grid, node);
		//printArray(grid, node, 2);

		double max_nevyazka=-1, nevyazka;
		for (int i = 0; i < node - 1; i++) {
			x = (double)(grid[i+1][0] - grid[i][0])/2 + grid[i][0];
			nevyazka = Newton_method(div_dif, grid, node, x) - function(x);
			//printf("%15.16lf %15.16lf %15.16lf \n", Newton_method(div_dif, grid, node, x), function(x), nevyazka);
			if (max_nevyazka < fabs(nevyazka))
				max_nevyazka = fabs(nevyazka);	
		}
		error[node] = max_nevyazka;
		fprintf(fileERROR, "%i %15.16lf\n", node, error[node]);

		free(div_dif);
		freeArray(grid, node, 2);
		div_dif = NULL;
		grid = NULL;
	}

	fclose(fileERROR);
	return 0;
}