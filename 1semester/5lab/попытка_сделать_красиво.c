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
			//printf("%f ", A[i][j]);
		}
		//printf("\n");	
	}
	return A;
}

//по факту тут надо знать и (!!)менять(!!) только число столбцов
void printMatrix(const int(*columns)[N], const size_t columnsCount)
{
	// количество столбцов или элементов в каждом подмассиве
	size_t rowsCount =sizeof(*columns);
	size_t sizeValue = sizeof(int);
	for (size_t i=0; i < rowsCount/sizeValue; i++){
		for (size_t j=0; j < columnsCount/sizeValue; j++){
			printf("%d ", columns[i][j]);
		}
		printf("\n");
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

	readMatrix(file, A);
	size_t columnsCount = sizeof(A[0]);
	printMatrix(A, columnsCount);

	return 0;
}