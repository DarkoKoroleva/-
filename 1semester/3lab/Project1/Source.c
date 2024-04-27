#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#define N 10

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

void Rotation(double A[N][N], double B[N][1]) {
	int i, j, j2;
	double c12, s12, k1, k2, c1;
	double c2;

	for (j = 0; j < N; j++) {
		for (i = j + 1; i < N; i++) {
			c12 = (double)A[j][j] / sqrt(pow(A[j][j], 2) + pow(A[i][j], 2));
			s12 = (double)A[i][j] / sqrt(pow(A[j][j], 2) + pow(A[i][j], 2));
			c1 = B[j][0];
			c2 = B[i][0];
			B[j][0] = c12 * c1 + s12 * c2;
			B[i][0] = -s12 * c1 + c12 * c2;
			for (j2 = j; j2 < N; j2++) {
				k1 = c12 * A[j][j2] + s12 * A[i][j2];
				k2 = -s12 * A[j][j2] + c12 * A[i][j2];
				A[j][j2] = k1;
				//printf("%f ", A[j][j2]);
				A[i][j2] = k2;
				//printf("%f ", A[i][j2]);
				//printf("%\n ");
			}
		}
	}
}

void ReverseSubstitution(double A[N][N], double B[N][1]) {
	int i, j;
	for (i = N - 1; i >= 0; i--) {
		for (j = i + 1; j < N; j++) {
			B[i][0] -= A[i][j] * B[j][0]; //перенос в правую сторону
			A[i][j] = 0;
		}
		B[i][0] = (double)B[i][0] / A[i][i];
		//printf("B[%d] = %lf ", i, B[i][0]);
		A[i][i] = 1;
	}
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

double norma(double first[N][1], double second[N][1]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		norm += pow(first[i][0] - second[i][0], 2);
	norm = sqrt(norm);
	return norm;
}

double normaN(double first[N][N], double second[N][N]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			norm += pow(first[i][j] - second[i][j], 2);
	norm = sqrt(norm);
	return norm;
}

int main() {
	double A[N][N], B[N][1], null[N][1];
	FILE* file;
	file = fopen("M_tab.txt", "r");
	if (file == NULL) {
		printf("Files not found");
		exit;
	}

	double xx[N][1];
	for (int q = 0; q < N; q++)
		xx[q][0] = (double)rand() / RAND_MAX * 5 + 2;
	//printf("xx= \n"); printMatrix1(xx);

	for (int q = 0; q < N; q++) //null for norma
		null[q][0] = 0;

	double null2[N][N];
	for (int q = 0; q < N; q++) //null2 for normaN
		for (int j = 0; j < N; j++)
			null2[q][j] = 0;

	double BB[N][1], dA[N][N], B2[N][1], A1[N][N];// где B2 для невязки


	for (int w = 1; w < 2; w++) {
		readMatrix(file, A1);
		double normA = normaN(A1, null2); // NORMA A																	!

		for (int k = 0; k < 10; k++) {
			
			for (int q = 0; q < N; q++)
				for (int j = 0; j < N; j++)
					A[q][j] = A1[q][j];

			for (int q = 0; q < N; q++) // DELTA A
				for (int j = 0; j < N; j++)
					dA[q][j] = A[q][j] + 2 * (0.5 - (double)rand() / RAND_MAX) * A[q][j] * pow(10, - w - 2);

			double normda = normaN(dA, A); // NORMA dA																	!

			multiplication1(B, A, xx);

			for (int q = 0; q < N; q++) // COPY B
				BB[q][0] = B[q][0];

			Rotation(A, B);
			printf("A'= \n"); printMatrix(A); //printf("B= \n"); printMatrix1(B);
			ReverseSubstitution(A, B);
			//printf("B'= \n"); printMatrix1(B);

			double normX = norma(B, xx); // FACT ERROR																				!

			multiplication1(B2, A, B);
			double normN = norma(B2, B); //NEVYAZKA																					!

			Rotation(dA, BB);
			//printf("A'= \n"); printMatrix(A); printf("B= \n"); printMatrix1(B);
			ReverseSubstitution(dA, BB);

			double normdx = norma(BB, B); //NORMA DX																				!
			double normx = norma(B, null); //NORMA X																				!

			//printf("%.16lf %.16lf %.16lf %.16lf\n",normdx, normx, normda, normA);
		}
		//printf("normX = %.16lf normN = %.16lf normdx = %.16lf normx = %.16lf normda = %.16lf normA = %.16lf\n", normX, normN, normdx, normx, normda, normA);
	}

	return 0;
}