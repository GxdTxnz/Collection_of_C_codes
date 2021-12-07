#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 3
int main (int argc, char *argv[])

{
    int i, j, k;
    // выделим память под матрицы
    int **A = (int**)malloc(N * sizeof(int*));
    int **B = (int**)malloc(N * sizeof(int*));
    for (i = 0; i < N; i++)
{
A[i] = (int*)malloc(N * sizeof(int));
B[i] = (int*)malloc(N * sizeof(int));
}
    // рандомно заполним нужную матрицу
    srand(time(NULL));
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
{
    A[i][j] = rand() % 10;
}
// перемножим
for(i = 0; i < N; i++)
for(j = 0; j < N; j++)
{
    B[i][j] = 0;
    for(k = 0; k < N; k++)
    B[i][j] += A[i][k] * A[k][j];
}
// выводим результат
printf("matrix A\n");
for (i = 0; i < N; i++)
{
    for (j = 0; j < N; j++)
    printf("%d ", A[i][j]);
    printf("\n");
}
printf("\nthe result of multiplying\n");
for (i = 0; i < N; i++)
{
    for (j = 0; j < N; j++)
    printf("%3d ", B[i][j]);
    printf("\n");
}
return 0;
}
