#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{

    int i, j, k;

    int mat1[12];
    int mat2[5][12];
    int mat3[3][5][12];

    for (i = 0; i < 12; i++)
    {
        mat1[i] = i;
        printf(" %d", mat1[i]);
    }
    printf(" \n");

    // zweidimensional 
    for (j = 0; j < 5; j++)
    {
        for (i = 0; i < 12; i++)
        {
            mat2[j][i] = i * j;
            printf( " %2d", mat2[j][i]);
        }
        printf("\n");
    }


//dreidimiensional
for (k = 0; k < 3; k++)
{
    for (j = 0; j < 5; j++)
    {
        for (i = 0; i < 12; i++)
        {
            mat3[k][j][i] = j * i * k;
            printf( " %2d", mat3[k][j][i]);
        }
        printf("\n");
    }
}

    return (42);
}