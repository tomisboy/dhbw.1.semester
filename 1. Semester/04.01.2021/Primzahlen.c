#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    char bereich[1000000+1] = {0};
    int i, j, counter;
    counter = 0;
    j = 0;

    //keine Primzahlen werden werden 1
    for (i = 2; i <= 1000001; i++)
    {
        if (bereich[i] == 0)
        {
            for (j= 2 * i; j <= 1000001; j+=i)
            {
                bereich[j] = 1;
            }
        }
    }

    for (i = 2; i <= 1000001; i++)
    {
        if (bereich[i] == 0)
            counter++;
    }

    printf("Anzahl der Primzahlen ist %d : ", counter);

    return (42);
}