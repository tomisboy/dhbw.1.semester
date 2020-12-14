#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    int i, fertigenummer, pruefziffer, Kontonummer ,temp;
    long eingabe;
    pruefziffer = 0;
    eingabe = 12345678911;
    Kontonummer = eingabe;
    //nDigits = floor(log10(abs(eingabe))) + 1;

    int stellen[30] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    fertigenummer = 0;
    int modulo11[6] = {2, 3, 4, 5, 6, 7};
    for (i = 0; i <= 30; i++)
    {
        stellen[i] = eingabe % 10;
        eingabe = eingabe / 10;
        printf("%i", stellen[i]);
    }
    for (i = 0; i <= 30; i++)
    {
        fertigenummer = fertigenummer + (int)stellen[i] * (int)modulo11[i % 6];
    }
    temp = fertigenummer;
    printf("\n fertigenummer %i", fertigenummer);
    temp = temp % 11;
    pruefziffer = 11 - temp;

    if (pruefziffer == 10 || pruefziffer == 11)
    {
        pruefziffer = 0;
    }

    printf("\n \n pruefziffer %i", pruefziffer);

    fertigenummer = Kontonummer * (int)10 + pruefziffer;

    printf("\n \n Kontonummer %i", fertigenummer);

    return (42);
}