#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include < malloc.h >
#include <conio.h>
#define MEMORY_ERROR 2 


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
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%15.15lf ", array[i][j]);
		}
		printf("\n");
	}
}

void printArrayFile(FILE* file, double** array, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			fprintf(file, "%15.15lf ", array[i][j]);
		}
		fprintf(file, "\n");
	}
}

double** nodes(double a, double b, int n) {
	double** grid = createArray(n + 1, 2);
	for (int k = 0; k <= n; k++) {
		grid[k][0] = a + (double)(b - a) / n * k; //x	
	}
	for (int k = 0; k <= n; k++) {
		grid[k][1] = function(grid[k][0]); //y
		//printf("%15.15lf %15.15lf\n", grid[k][0], grid[k][1]);
	}
	return grid;
}

double* differences(double** grid, int n) {
	double* dif = (double*)malloc(n * sizeof(double));
	//printf("Table hi = \n");
	dif[0] = 0;
	for (int i = 1; i <= n; i++) { // 1
		dif[i] = grid[i][0] - grid[i - 1][0];
		//printf("%15.5lf ", dif[i]);
	}
	//printf("\n");
	return dif;
}

double** system_equations(double* h, int n, double** grid) {
	double** M = createArray(n + 1, n + 2);
	printf("Table M = \n");

	M[0][0] = -1 / h[1];
	M[0][1] = 1 / h[1] + 1/h[2];
	M[0][2] = - 1 / h[2];
	for (int k = 3; k <= n+1; k++) {
		M[0][k] = 0;
	}

	for (int i = 1; i <= n-1; i++) {
		for (int k = 0; k < i-1; k++) {
			M[i][k] = 0;
			//printf("%15.5lf ", M[i - 1][k]);
		}

		M[i][i - 1] = h[i] / (h[i] + h[i+1]);
		M[i][i] = 2;
		M[i][i + 1] = h[i+1] / (h[i] + h[i+1]);
		//printf("%15.5lf %15.5lf %15.5lf ", M[i - 1][i - 1], M[i - 1][i], M[i - 1][i + 1]);

		for (int k = i + 2; k <= n; k++) {
			M[i][k] = 0;
			//printf("%15.5lf ", M[i - 1][k]);
		}
		M[i][n + 1] = 6 / (h[1] + h[2]) * ((grid[i+1][1] - grid[i][1])/h[2] - (grid[i][1] - grid[i-1][1]) / h[2]);
		//printf("%15.5lf \n", M[i - 1][n+1]);
	}

	for (int k = 0; k < n-2; k++) {
		M[n][k] = 0;
	}
	M[n][n-2] = - 1 / h[n-1];
	M[n][n-1] = 1 / h[n-1] + 1 / h[n];
	M[n][n] = -1 / h[n];
	M[n][n+1] = 0;

	printArray(M, n + 1, n + 2); 
	printf("\n\n");

	double coefficient1 = -1 / M[1][2] * M[0][2];
	double coefficient2 = -1 / M[n - 1][n - 2] * M[n][n - 2];

	for (int i = 0; i <= n + 1; i++) {
		M[0][i] += M[1][i] * coefficient1;
		M[n][i] += M[n-1][i] * coefficient2;
	}
	return M;
}

double* thomas_algorithm(int n, double** matrix) {
	double* x = (double*)malloc(n* sizeof(double));
	x[1] = matrix[0][n + 1] / matrix[0][1];
	matrix[2][n + 1] -= x[1] * matrix[2][1];
	matrix[2][1] = 0;

	x[n-1] = matrix[n][n + 1] / matrix[n][n-1];
	matrix[n-2][n+1] -= x[n-1] * matrix[n-2][n-1];
	matrix[n - 2][n - 1] = 0;
	printf("\n");
	printArray(matrix, n + 1, n + 2);
	double* lower_diagonal = (double*)malloc((n - 3) * sizeof(double));
	double* main_diagonal = (double*)malloc((n - 3) * sizeof(double));
	double* upper_diagonal = (double*)malloc((n - 3) * sizeof(double));
	double* solution = (double*)malloc((n - 3) * sizeof(double));
	double* d = (double*)malloc((n - 3) * sizeof(double));
	double* l = (double*)malloc((n - 3) * sizeof(double));

	for (int i = 2; i <= n-2; i++) {
		lower_diagonal[i - 2] = matrix[i][i - 1];
		main_diagonal[i-2]= matrix[i][i];
		upper_diagonal[i - 2] = matrix[i][i + 1];
		solution[i - 2] = matrix[i][n + 1];
	}

	// Forward elimination
	double di_old = 1, li_old = 1;
	for (int i = 0; i <= n - 4; i++) {
		d[i] = - upper_diagonal[i] / ( di_old* lower_diagonal[i] + main_diagonal[i]);
		l[i] = (solution[i] - lower_diagonal[i] * li_old) / (lower_diagonal[i]* di_old + main_diagonal[i]);
		printf("d%d = %5.5lf  l%d= %5.5lf \n", i, d[i], i, l[i]);
		di_old = d[i]; li_old = l[i];
	}

	// Backward substitution
	x[n - 2] = l[n-4];
	//printf("x%d = %5.5lf \nx%d = %5.5lf \n", n - 1, x[n - 1], n-2, x[n-2]);
	for (int i = n - 3; i >= 2; i--) {
		x[i] = d[i-2] * x[i+1] + l[i-2];
		//printf("x%d = %5.5lf \n", i, x[i]);
	}
	//printf("x%d = %5.5lf \n", 1, x[1]);
	x[0] = (matrix[1][n + 1] - matrix[1][1] * x[1] - matrix[1][2] * x[2]) / matrix[1][0];
	x[n] = (matrix[n-1][n + 1] - matrix[n-1][n-2] * x[n-2] - matrix[n-1][n-1] * x[n-1]) / matrix[n-1][n];

	printf("\n\n\n");
	for (int i = 0; i <= n; i++) {
		printf("x%d = %5.5lf \n", i, x[i]);
	}

	return x;
}

double** integration_constants(double** grid, double* M, int n, double* h) {
	double** C = createArray(n+1, 2);
	C[0][0] = 0; C[0][1] = 0;
	for (int i = 1; i <= n; i++) {
		C[i][0] = grid[i - 1][1] - M[i - 1] * pow(h[i], 2)/6;
		C[i][1] = (grid[i][1] - grid[i - 1][1]) / h[i] - h[i] / 6 * (M[i] - M[i - 1]);
	}
	return C;
}

double** find_coefficient(double** grid, double* M, int n, double* h, double** C) {
	double** polynom = createArray(n, 4);
	for (int i = 1; i <= n; i++) {
		polynom[i - 1][0] = (M[i] - M[i - 1]) / (6 * h[i]);
		polynom[i - 1][1] = (3*grid[i][0]*M[i-1] - 3 * grid[i-1][0] * M[i]) / (6 * h[i]);
		polynom[i - 1][2] = (3* pow(grid[i - 1][0],2)* M[i] - 3 * pow(grid[i][0], 2) * M[i - 1]) / (6 * h[i]) + C[i][1];
		polynom[i - 1][3] = (pow(grid[i][0], 3) * M[i-1] - pow(grid[i-1][0], 3)*M[i]) / (6 * h[i]) - C[i][1]*grid[i-1][0] + C[i][0];
	}
//	printArray(polynom, n, 4);
	return polynom;
}

double value_polynom(double** poly, int k, double x) {
	double value = 0;
	for(int i = 0; i < 4; i++) {
		value += poly[k][i] * pow(x, 4 - i - 1);
	}
	return value;
}

int main() {
	FILE* filePOLY;
	filePOLY = fopen("POLY.txt", "w");

	int n = 6; // !!! 6
	double a = 1, b = 5, x;
	double** grid = nodes(a, b, n); //ravnomernaya сетка
	double* h = (double*)malloc(n * sizeof(double));
	h = differences(grid, n);
	double** table_coeff = system_equations(h, n, grid);
	double* solution = (double*)malloc(n * sizeof(double));
	double** const_integration = createArray(n + 1, 2);
	printArray(table_coeff, n+1, n + 2);

	solution = thomas_algorithm(n, table_coeff);

	printf("C = \n");
	const_integration = integration_constants(grid, solution, n, h);
	printArray(const_integration, n + 1, 2);
	printf("\n");
	double** poly = find_coefficient(grid, solution, n, h, const_integration);
	printArrayFile(filePOLY, poly, n, 4);
	fclose(filePOLY);

	FILE* fileNODES;
	fileNODES = fopen("NODES.txt", "w");
	printArrayFile(fileNODES, grid, n+1, 2);
	fclose(fileNODES);


	//free(hi);
	//free(solution);
	freeArray(table_coeff, n + 1);
	freeArray(const_integration, n + 1);
	freeArray(grid, n + 1);
	freeArray(poly, n);

	
	FILE* fileERROR;
	fileERROR = fopen("ERROR.txt", "w");
	double error[90];
	for (n = 4; n < 90; n++) { //считаю зависимость ошибки от числа узлов
		double** grid = nodes(a, b, n);
		printArray(grid, n+1, 2);
		double* h = (double*)malloc(n * sizeof(double));
		h = differences(grid, n);
//		printArray(h, 1, n-1);
		double** table_coeff = system_equations(h, n, grid);
//		printArray(table_coeff, n + 1, n + 2);
		double* solution = (double*)malloc(n * sizeof(double));
		double** const_integration = createArray(n + 1, 2);
		solution = thomas_algorithm(n, table_coeff);
		const_integration = integration_constants(grid, solution, n, h);
//		for (int c = 0; c < n; c++) {
//			printf("%15.15lf \n", solution[c]);
//		}

		double** poly = find_coefficient(grid, solution, n, h, const_integration);
//		printArray(poly, n, 4);
//		printf("\n");


		double max_nevyazka = -1, nevyazka;
		for (int i = 0; i < n - 1; i++) {
			x = (double)(grid[i + 1][0] - grid[i][0]) / 2 + grid[i][0];
			nevyazka = value_polynom(poly, i, x) - function(x);
			if (max_nevyazka < fabs(nevyazka))
				max_nevyazka = fabs(nevyazka);
		}
		error[n] = max_nevyazka;
		fprintf(fileERROR, "%i %15.16lf\n", n, error[n]);

		//free(h);
		//free(solution);
		freeArray(table_coeff, n + 1);
		freeArray(const_integration, n + 1);
		freeArray(grid, n + 1);
		freeArray(poly, n);
	}

	fclose(fileERROR);

	return 0;
}

