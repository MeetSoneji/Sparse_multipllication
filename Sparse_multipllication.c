#include <stdio.h>
#define MAX_SIZE 100
struct Sparse
{
    int row;
    int col;
    int value;
}sparseA[], sparseB[],result[];
void create(int rows, int cols, int matrix[rows][cols], struct Sparse sparse[])
{
    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }
    sparse[k].row = -1;
}
void multiply(struct Sparse sparseA[], struct Sparse sparseB[], struct Sparse result[])
{
    int i, j, k;
    int sum;
    int r = 0;
    i = j = k = 0;
    while (sparseA[i].row != -1)
    {
        j = 0;
        while (sparseB[j].row != -1)
        {
            if (sparseA[i].col == sparseB[j].row)
            {
                sum = 0;
                k = 0;
                while (sparseA[i].row == sparseA[i + k].row &&
                       sparseB[j].row == sparseB[j + k].row)
                {
                    if (sparseA[i + k].col == sparseB[j + k].col)
                    {
                        sum += sparseA[i + k].value * sparseB[j + k].value;
                        k++;
                    }
                    else if (sparseA[i + k].col < sparseB[j + k].col)
                    {
                        k++;
                    }
                    else
                    {
                        k++;
                    }
                }
                result[r].row = sparseA[i].row;
                result[r].col = sparseB[j].col;
                result[r].value = sum;
                r++;
                j += k;
                i += k;
            }
            else if (sparseA[i].col < sparseB[j].row)
            {
                i++;
            }
            else
            {
                j++;
            }
        }
        i++;
    }
    result[r].row = -1;
}
void display(struct Sparse sparse[])
{
    int i = 0;
    while (sparse[i].row != -1)
    {
        printf("(%d, %d): %d\n", sparse[i].row, sparse[i].col, sparse[i].value);
        i++;
    }
}
int main()
{
    int matrixA[MAX_SIZE][MAX_SIZE] = {
        {1, 0, 2},
        {0, 3, 0},
        {4, 0, 5}};
    int matrixB[MAX_SIZE][MAX_SIZE] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    struct Sparse sparseA[MAX_SIZE * MAX_SIZE];
    struct Sparse sparseB[MAX_SIZE * MAX_SIZE];
    struct Sparse result[MAX_SIZE * MAX_SIZE];
    create(3, 3, matrixA, sparseA);
    create(3, 3, matrixB, sparseB);
    multiply(sparseA, sparseB, result);
    printf("Sparse Matrix A:\n");
    display(sparseA);
    printf("\nSparse Matrix B:\n");
    display(sparseB);
    printf("\nResultant Sparse Matrix:\n");
    display(result);
    return 0;
}
