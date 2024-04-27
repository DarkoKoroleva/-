#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 3

void readMatrix(FILE* file, double A[N][N]) {
	int i, j;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fscanf(file, "%lf", &A[i][j]);
			//printf("%f ", A[i][j]);
		}
		//printf("\n");	
	}
	return A;
}

void printMatrix(double A[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%.16lf ", A[i][j]);
		printf("\n");
	}
}

void printMatrix1(double A[N][1]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 1; j++)
			printf("%.16lf ", A[i][j]);
		printf("\n");
	}
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

void multiplicationMS(double A[N][N], double x[N][1], double rez[N][1]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 1; j++) {
			rez[i][j] = 0;
			for (int k = 0; k < N; k++)
				rez[i][j] += A[i][k] * x[k][j];
		}
	}
}

void subtraction(double A[N][N], double B[N][N], double C[N][N]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			C[i][j] = A[i][j] - B[i][j];
}

void subtraction1(double A[N][1], double B[N][1], double C[N][1]) {
	for (int i = 0; i < N; i++)
		C[i][0] = A[i][0] - B[i][0];
}

void addition1(double A[N][1], double B[N][1], double C[N][1]) {
	for (int i = 0; i < N; i++)
		C[i][0] = A[i][0] + B[i][0];
}

double norma(double first[N][1], double second[N][1]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		norm += pow(first[i][0] - second[i][0], 2);
	norm = sqrt(norm);
	return norm;
}

double normaN(double first[N][N]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			norm += pow(first[i][j], 2);
	return sqrt(norm);
}

void approximation_method(double A[N][N], double B[N][1], double x[N][1], double lmin, double lmax, double e) {
	double a, x_next[N][1], x_curr[N][1];
	a = (double)1 / lmax;
	//a = (double) 1 / 3883.17291169844;

	double A_new[N][N], C[N][N], E[N][N], first_vector[N][1], G[N][1];
	for (int i = 0; i < N; i++) {
		x_curr[i][0] = 0;
	}

	//≈ƒ»Ќ»„Ќјя	
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j)
				E[i][i] = 1;
			else
				E[i][j] = 0;
		}
	}
	// создать х(к+1)
	multiplication(A, a, A_new);
	subtraction(E, A_new, C);
	multiplicationMS(C, x_curr, first_vector);
	multiplicationB(B, a, G);
	addition1(first_vector, G, x_next);

	int it = 0, step = 0;
	double normC = 1 - lmin / lmax;
	while (step != 1) {
		while (normC / (1 - normC) * norma(x_next, x_curr) > e) {
			//while (norma(x_next, x_curr) > e) {
			for (int i = 0; i < N; i++) { //x_curr = x_next
				x_curr[i][0] = x_next[i][0];
			}
			multiplicationMS(C, x_curr, first_vector);
			addition1(first_vector, G, x_next);// printf("x1 = %.14f ", x1);
			it += 1;
		}
		step += 1;
		for (int i = 0; i < N; i++) {
			x[i][0] = x_next[i][0];
		}
		printf("it = %d ", it);
	}
}


int main() {
	double A[N][N], B[N][1];
	FILE* file;
	file = fopen("M_tab.txt", "r");
	if (file == NULL) {
		printf("Files not found");
		exit(1);
	}

	double xx[N][1];
	for (int q = 0; q < N; q++)
		xx[q][0] = (double)rand() / RAND_MAX * 5 + 2;
	printf("xx= \n"); printMatrix1(xx);

	double x[N][1], B2[N][1];// где B2 дл€ нев€зки


	for (int counter = 1; counter < 2; counter++) {
		readMatrix(file, A);
		multiplicationMS(A, xx, B);
		printf("A= \n"); printMatrix(A); printf("B= \n"); printMatrix1(B);	
		double e = 0.1, lmin, lmax;
		fscanf(file, "%lf", &lmax);
		fscanf(file, "%lf", &lmin);

		for (int k = 1; k < 2; k++) {
			approximation_method(A, B, x, lmin, lmax, e);
			multiplicationMS(A, x, B2);
			printf("e = %.16lf NormX=  %.16lf NormN=  %.16lf\n", e, norma(xx, x), norma(B2, B));
			//printf("%.16lf %.16lf %.16lf\n", e, norma(xx, x), norma(B2, B));
			e *= 0.1;
		}
		e = 0.000001;
		printf("\n");
		/*for (int k = 1; k < 10; k++) {
			readMatrix(file, A);
			multiplicationMS(A, xx, B);
			fscanf(file, "%lf", &lmax);
			fscanf(file, "%lf", &lmin);
			approximation_method(A, B, x, lmin, lmax, e);
			//printf("x= \n"); printMatrix1(x);
			printf("NormaX = %.16lf\n", norma(xx, x));
		}*/

		//printf("x= \n"); printMatrix1(x);

	}
	return 0;
}