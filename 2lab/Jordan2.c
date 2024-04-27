#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#define N 10

void readMatrix(FILE* file, double A[N][N]) {
	if (file == NULL) {
		printf("Files not found");
		exit;
	}
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
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++)
			printf("%.16lf ", A[i][j]);
		printf("\n");
	}
	//printf("\n");
}

void printMatrix1(double A[N][1]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 1; j++)
			printf("%.16lf ", A[i][j]);
		printf("\n");
	}
	
}

void change(double A[N][N], double B[N][1], int i, int j) {
	double max=A[i][j], c;
	int i2 = i, cross = i;
	for (i2; i2 < N; i2++) {
		if (A[i2][j] > max) {
			max = A[i2][j];
			cross = i2;
		}			
	}
	if (cross != i) {
		for (j; j < N; j++) {
			c = A[i][j];
			A[i][j] = A[cross][j];
			A[cross][j] = c;
		}
		//printf("%lf %lf", B[i][0], B[cross][0]);
		c = B[i][0];
		B[i][0] = B[cross][0];
		B[cross][0] = c;
		//printf("%lf %lf", B[i][0], B[cross][0]);
	}
}

void Jordan(double A[N][N], double B[N][1]) {
	int i, j, j2;
	double k;
	change(A, B, 0, 0);
	//printMatrix(A);

	for (j = 0; j<N; j++){
		for (i = 0; i < N; i++)
			if (i != j ) {
				k = - (double)A[i][j] / A[j][j];
				//printf("%f ", k);
				A[i][j] += A[j][j] * k;
				B[i][0] += B[j][0] * k;
				//printf("%lf ", B[i][0]);
				for (j2 = j+1; j2 < N; j2++) {
					A[i][j2] += A[j][j2] * k;
					//printf("%lf ", A[i][j]);
				}
			}
	}
	printf("\n");
	for (i = 0; i < N; i++)
		if (A[i][i] != 1) {
			k = 1 / A[i][i];
			A[i][i] = k * A[i][i];
			B[i][0] = k * B[i][0];
		}

	//return B;
}


void multiplication1(double B[N][1], double A[N][N], double xx[N][1]) {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 1; j++) //тк х - вектор столбец, a =1
		{
			B[i][j] = 0;
			for (int k = 0; k < N; k++)
				B[i][j] += A[i][k] * xx[k][j];
		}
}


int main() {
	double A[N][N], B[N][1], dB[N][1], raz[N][1], B2[N][1];
	int i, j;

	double xx[N][1], normX, normN;
	for (int q = 0; q < N; q++)
		xx[q][0] = (double) rand() / RAND_MAX * 5 + 2;
	printf("xx = \n");
	printMatrix1(xx);

	FILE* file;
	file = fopen("M_tab.txt", "r");
	if (file == NULL) {
		printf("Files not found");
		exit;
	}

	for (int w = 1; w < 2; w++) {
		normX = 0; normN = 0;
		readMatrix(file, A);
		//printf("A = \n");
		//printMatrix(A);

		//printf("\n");
		multiplication1(B, A, xx);
		//printf("B = \n");
		//printMatrix1(B);

		Jordan(A, B);
		//printf("A = \n");
		//printMatrix(A);
		printf("x = \n");
		printMatrix1(B);

		for (int q = 0; q < N; q++) {
			raz[q][0] = (B[q][0] - xx[q][0])* (B[q][0] - xx[q][0]);
			normX += raz[q][0];
		}
		normX = sqrt(normX);
		printf("%.16lf ", normX);
		multiplication1(B2, A, B);
		for (int q = 0; q < N; q++) {
			raz[q][0] = (B2[q][0] - B[q][0]) * (B2[q][0] - B[q][0]);
			normN += raz[q][0];
		}
		normN = sqrt(normN);
		printf("%.16lf \n", normN);
		//printf("\n");
	}


	//for (int q = 0; q < N; q++)
	//	dB[q][0] = 2 * (0.5 - (float)rand() / RAND_MAX)*B[q][0];
	//printf("dB = \n");
	//printMatrix1(dB);

	fclose(file);
	return 0;
}