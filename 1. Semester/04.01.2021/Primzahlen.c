#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    char bereich[100000] = {0};
    int i = 0 , j= 0, counter=0;

    //keine Primzahlen werden werden 1
    for (i = 2; i < 100000; i++)
    {
        if (bereich[i] == 0)
        {
            for (j= 2 * i; j < 100000; j+=i) 
            {
                bereich[j] = 1; // alle vielfachen einer primzahl Zahl streichen
            }   // keine Primzahlen werden mit 1 markiert
         counter++; // 
        }

        //if (bereich[i] == 0)
           
    }
/*
    for (i = 2; i <= 1000; i++)
    {
        if (bereich[i] == 0)
            counter++;
    }
*/
    printf("Anzahl der Primzahlen ist %d", counter);
    return (42);
}