#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10

void readMatrix(FILE* file, double A[N][N]) {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fscanf(file, "%lf", &A[i][j]);
		}
	}
	return A;
}

void printMatrix1(double A[N][1]) {
	for (int i = 0; i < N; i++)
		printf("%.16lf ", A[i][0]);
	printf("\n");
}


void printMatrix(double A[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%.16lf ", A[i][j]);
		printf("\n");
	}
}

double scalar_product(double a[N][1], double b[N][1]) {
	double rezult = 0;
	for (int i = 0; i < N; i++) {
		rezult += a[i][0] * b[i][0];
	}
	return rezult;
}

void multiplicationMS(double A[N][N], double x[N][1], double rez[N][1]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 1; j++) {
			rez[i][j] = 0;
			for (int k = 0; k < N; k++)
				rez[i][j] += A[i][k] * x[k][j];
		}
	}
}

double norma(double first[N][1]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		norm += pow(first[i][0], 2);
	norm = sqrt(norm);
	return norm;
}

void multiplication(double A[N][N], double a, double A_new[N][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A_new[i][j] = A[i][j] * a;
}

void multiplicationB(double A[N][1], double a, double A_new[N][1]) {
	for (int i = 0; i < N; i++)
		A_new[i][0] = A[i][0] * a;
}

void subtraction1(double A[N][1], double B[N][1], double C[N][1]) {
	for (int i = 0; i < N; i++)
		C[i][0] = A[i][0] - B[i][0];
}


double scalar_method(double A[N][N], double eps, double x[N][1]) {
	eps = eps / 10;
	double x_prev[N][1], x_curr[N][1], l_prev = 1, l_curr=0, check1, check3;
	int i, counter = 0;
	x_prev[0][0] = 1;
	for (i = 1; i < N; i++) {// создаю х(0)
		x_prev[i][0] = 0;
	}
	do {
		l_prev = l_curr;
		multiplicationMS(A, x_prev, x_curr); //считаю у(к+1)
		l_curr = scalar_product(x_curr, x_prev)/ scalar_product(x_prev, x_prev);//считаю новое сч
		double norm_x = norma(x_curr);
		for (i = 0; i < N; i++) { //считаю х(к+1)
			x_prev[i][0] = (double)x_curr[i][0] / norm_x;
		}
		counter++;
	} while (fabs(l_curr - l_prev) > eps);

	//printf("l_norm = %.16lf it = %i ", l_curr, counter);
	printf("%.16lf %i ", l_curr, counter);
	for (i = 0; i < N; i++) {
		x[i][0] = x_curr[i][0];
	}
	return(l_curr);
}

double scalar_method_no_norm(double A[N][N], double eps, double x[N][1]) {
	eps = eps ;
	double x_prev[N][1], x_curr[N][1], y_curr[N][1], l_prev = 1, l_curr = 0;
	int i, counter = 0;
	x_prev[0][0] = 1;
	for (i = 1; i < N; i++) {// создаю х(0)
		x_prev[i][0] = 0;
	}
	do {
		l_prev = l_curr;
		multiplicationMS(A, x_prev, y_curr); //считаю у(к+1)
		//double norm_y = norma(y_curr);
		for (i = 0; i < N; i++) { //считаю х(к+1)
			x_curr[i][0] = y_curr[i][0];
		}
		l_curr = scalar_product(y_curr, x_prev) / scalar_product(x_prev, x_prev);//считаю новое сч
		for (i = 0; i < N; i++) { //перехожу на след шаг
			x_prev[i][0] = x_curr[i][0];
		}
		counter += 1;
	} while (fabs(l_curr - l_prev) > eps);

	//printf("l_no_norm = %.16lf it = %i ", l_curr, counter);
	printf("%.16lf %i ", l_curr, counter);
	for (i = 0; i < N; i++) { //перехожу на след шаг
		x[i][0] = x_curr[i][0];
	}
	return(l_curr);
}

double norma2(double first[N][1], double second[N][1]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		norm += pow(first[i][0] - second[i][0], 2);
	norm = sqrt(norm);
	return norm;
}


int main() {
	double A[N][N], A_new[N][N], x[N][1], x2[N][1], eigenvalue, xx[N][1], eigenvaluex[N][1], nevyzka[N][1];
	FILE* file;
	file = fopen("M_tab.txt", "r");
	if (file == NULL) {
		printf("Files not found");
		exit(1);
	}

	readMatrix(file, A);
	//printMatrix(A);
	fscanf(file, "%lf", &eigenvalue);
	for (int i = 0; i < N; i++) {
		fscanf(file, "%lf", &xx[i][0]);
	}
	double eps, Ax[N][1], l1 = 0, l2 = 0;
	for (int count = 0; count < N; count++) {
		eps = pow(10, -count - 1);
		printf("%.10lf ", eps);

		l1 = scalar_method(A, eps, x);
		//printf("\nx=\n");printMatrix1(x);printf("\n");

		l2 = scalar_method_no_norm(A, eps, x2);
		//printf("\nx=\n");printMatrix1(x2);printf("\n");

		for (int i = 0; i < N; i++) {
			x[i][0] = -x[i][0];
		}
		double norm_l1 = sqrt(pow(eigenvalue - l1, 2)), norm_l2 = sqrt(pow(eigenvalue - l2, 2));
		multiplicationMS(A, x, Ax);
		multiplicationB(x, eigenvalue, eigenvaluex);
		subtraction1(Ax, eigenvaluex, nevyzka);
		//printf("nevyzka = %.16lf  ", norma(nevyzka));
		//printf("fact error = %.16lf fact error no norm = %.16lf\n", norm_l1, norm_l2);
		printf("%.16lf ", norma(nevyzka));
		printf("%.16lf ", norm_l1);
		printf("%.16lf\n", norm_l2);
	}

	return 0;
}