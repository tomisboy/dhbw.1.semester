#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{

    int a, b, c ;

    printf("ZAHL 1 eingeben: \n ");
    scanf("%i", &a);
    fflush(stdin);
    printf("ZAHL 2 eingeben: \n ");
    scanf("%i", &b);


c = a %b;

printf("MOD = %i ", c);   
 return (42);
}