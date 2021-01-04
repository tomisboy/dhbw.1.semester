#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

void up_TvH(int scheibe, int von, int nach);
int counter=1;
int main(void)
{


    int scheiben;
    int von = 1;
    int nach = 3;

    printf("Anzahl der Scheiben eingeben ");
    scanf("%d", &scheiben);

    up_TvH(scheiben, von, nach);


    return (42);
}

void up_TvH(int scheibe, int von, int nach)
{
    int zwischen;
    if (scheibe > 1)
    {
        zwischen = 6 - von - nach;
        up_TvH(scheibe - 1, von, zwischen);
        printf("Scheibe %d von %d nach Stange %d ", scheibe, von, nach);
        counter++;
        up_TvH(scheibe - 1, zwischen, nach);
    }
    else
    {
        printf("Scheibe %d von %d nach Stange %d",scheibe, von, nach);
        printf(" Anzahl %d \n", counter);
        counter++;
    }
 
}