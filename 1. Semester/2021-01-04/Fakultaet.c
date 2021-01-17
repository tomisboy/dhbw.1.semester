#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int up_fak(long long n);

int main(void)
{
    long long  n, erg;

    printf("Zahl eingeben");
    scanf("%d", &n);
    fflush(stdin);

    erg = up_fak(n);

    printf("%d", erg);

    return (42);
}
int up_fak(long long n)
{
    long long  wert;
    if (n > 1)
    {
        wert = n * up_fak(n - 1); // 4,3,2,1 --> 1*2*3*4
    }
    else
    {
        wert = 1;
    }

    return (wert);
}
