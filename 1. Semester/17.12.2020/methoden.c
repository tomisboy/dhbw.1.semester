#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)


// NICHT VERGESSEN HIER OBEN MIT ";"
int up_addiere(int i, char bu, double d, float f);

int main(void)
{
    // call by value

    int i = 7, erg;
    char bu = 'a';
    float f = 7.85;
    double d = 12.99;

    erg = up_addiere(i, bu, d, f);

    printf("ERG = %d", erg);

    return (42);
}

int up_addiere(int i, char bu, double d, float f)
{

    int erg;
    erg = i + +(int)bu, (int)d + (int)f; // (int)f + (int)d;

    return (erg);
}