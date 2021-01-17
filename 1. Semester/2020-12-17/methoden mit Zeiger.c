#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

void up_addiere(int *i, char *bu, double *d, float *f, int *erg, char*t); //MIT SEMIKOLON 


int main(void)
{

    int i = 7, erg;
    char bu = 'a';
    float f = 7.85;
    double d = 12.99;



    char text[] ={"Hannes\n"};  //ist bereits Zeiger

    //& ADDRESSE der Variablen
    up_addiere(&i, &bu, &d, &f, &erg, text);

    printf("ERG = %d", erg);

    return (42);
}

//* es kommt ein ZEIGER
// es kommt nur eine Adresse unf greife über zeigen auf die Adresse zu
// hoohl dir den Inhalt und weise den der Var "*" zu "

void up_addiere(int *i, char *bu, double *d, float *f, int *erg, char *t)
{
    *erg = *i + (int)*bu + (int)*d + (int)*f;


    printf("%s", t);
// kein RETURN wei VOID 
}