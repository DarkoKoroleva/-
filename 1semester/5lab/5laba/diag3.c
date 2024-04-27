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

void printMatrix(double A[N][N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%.16lf ", A[i][j]);
		printf("\n");
	}
}

void printMatrix1(double A[N][1]) {
	for (int i = 0; i < N; i++)
		printf("%.16lf ", A[i][0]);
	printf("\n");
}

void Rotation(double A[N][N]) {
	int i, j, j2, i2=0;
	double c12, s12, k1, k2, k3, k4;

	for (i = 1; i < N - 1; i++) {
		for (j = i + 1; j < N; j++) {
			c12 = (double)A[i][i - 1] / sqrt(pow(A[i][i - 1], 2) + pow(A[j][i - 1], 2));//считаю коэфициенты дл€ линейного разложени€
			s12 = (double)A[j][i - 1] / sqrt(pow(A[i][i - 1], 2) + pow(A[j][i - 1], 2));

			for (j2 = i; j2 < N + 1; j2++) { //мен€ю числа в столбцах
				k3 = c12 * A[j2 - 1][i] + s12 * A[j2 - 1][j];
				k4 = -s12 * A[j2 - 1][i] + c12 * A[j2 - 1][j];
				A[j2 - 1][i] = k3;
				A[j2 - 1][j] = k4;
			}
			//printMatrix(A);
			//printf("\n");

			for (j2 = i; j2 < N + 1; j2++) { // мен€ю строки теми же преобразовани€ми и коэффициентами
				k1 = c12 * A[i][j2 - 1] + s12 * A[j][j2 - 1];
				k2 = -s12 * A[i][j2 - 1] + c12 * A[j][j2 - 1];
				A[i][j2 - 1] = k1;
				A[j][j2 - 1] = k2;
			}
			//printMatrix(A);
			//printf("\n");
		}
	}
}

void characteristic_polynomial(double A[N][N], double polynom[N + 2]) {
	double k_prevprev[N + 1], k_prev[N + 1];
	for (int i = 0; i < N + 1; i++) {
		k_prevprev[i] = 0;
		k_prev[i] = 0;
		polynom[i] = 0;
	}
	k_prevprev[0] = 0;
	k_prevprev[1] = 1;
	k_prev[0] = 0;
	k_prev[1] = A[0][0];
	k_prev[2] = -1;
	for (int count = 2; count < N + 1; count++) {
		double k = A[count - 1][count - 2] * A[count - 2][count - 1]; //то самое во втором слагаемом
		polynom[1] = A[count - 1][count - 1] * k_prev[1] - k * k_prevprev[1];
		polynom[count + 1] = -k_prev[count];
		for (int i = count; i > 0; i--) {
			polynom[i] = A[count - 1][count - 1] * k_prev[i] - k_prev[i - 1] - k * k_prevprev[i]; //!!!!!!!!!
		}
		for (int i = 0; i < N + 1; i++) {
			k_prevprev[i] = k_prev[i];
			k_prev[i] = polynom[i];
		}
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

double norma(double first[N][1]) {
	double norm = 0;
	for (int i = 0; i < N; i++)
		norm += pow(first[i][0], 2);
	norm = sqrt(norm);
	return norm;
}


void ReverseSubstitution(double A[N][N], double B[N][1]) {
	int i, j;
	for (i = N - 1; i >= 0; i--) {
		for (j = i + 1; j < N; j++) {
			B[i][0] -= A[i][j] * B[j][0]; //перенос в правую сторону
			A[i][j] = 0;
		}
		if (i != 9) {
			B[i][0] = (double)B[i][0] / A[i][i];
			//printf("B[%d] = %lf ", i, B[i][0]);
			A[i][i] = 1;
		}
			
	}
}

void Jordan(double A[N][N], double B[N][1]) {
	int i, j, j2;
	double k;
	//change(A, B, 0, 0);
	//printMatrix(A);

	for (j = 0; j < N; j++) {
		for (i = j; i < N; i++)
			if (i != j) {
				k = -(double)A[i][j] / A[j][j];
				//printf("%f ", k);
				A[i][j] += A[j][j] * k;
				B[i][0] += B[j][0] * k;
				//printf("%lf ", B[i][0]);
				for (j2 = j + 1; j2 < N; j2++) {
					A[i][j2] += A[j][j2] * k;
					//printf("%lf ", A[i][j]);
				}
			}
	}
	printf("\n");
	/*for (i = 0; i < N; i++)
		if (A[i][i] != 1) {
			k = 1 / A[i][i];
			A[i][i] = k * A[i][i];
			B[i][0] = k * B[i][0];
		}*/
}


int main() {
	double A[N][N], polynom[N + 2];
	FILE* file;

	double lmax;
	double lE[N][N], B[N][N], x[N][1], null[N][1];

	file = fopen("M_tab.txt", "r");
	if (file == NULL) {
		printf("Files not found");
		exit(1);
	}
	double Ax[N][1], lx[N][1], nevyzka[N][1];
	for (int count = 0; count < N; count++) {
		readMatrix(file, A);
		fscanf(file, "%lf", &lmax);
		for (int i = 0; i < N; i++) {
			x[i][0] = 0;
			null[i][0] = 0;
			for (int j = 0; j < N; j++) {
				if (i == j)
					lE[i][j] = lmax;
				else
					lE[i][j] = 0;
			}
		}
		subtraction(A, lE, B);
		Jordan(B, null);
		null[9][0] = 1;
		B[9][9] = 0;
		//printMatrix(B);
		ReverseSubstitution(B, null);
		//printMatrix(B);

		multiplicationMS(A, null, Ax);
		multiplicationB(null, lmax, lx);
		subtraction1(lx, Ax, nevyzka);
		printf("%.16lf \n", norma(nevyzka));
		//fprintf("nevyazka.txt", "%.16lf\n ", norma(nevyzka, null));

		Rotation(A);
		//printMatrix(A);
		printf("\n");
		characteristic_polynomial(A, polynom);

		for (int i = N + 1; i > 0; i--) {
			printf("%.16lf ", polynom[i]);
			//fprintf("poly.txt", "%.14lf ", polynom[i]);
		}
		printf("\n");

	}

	fclose("M_tab.txt");

	return 0;
}
