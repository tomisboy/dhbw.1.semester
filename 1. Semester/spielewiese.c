#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {


float kommazahl=0.0;
float punktzahl=0.0;
float erg;

printf("Kommazahl eingeben: \n");
scanf_s("%f",&kommazahl);
fflush(stdin);
printf("\n punkt getrennte zahl eingeben: \n");
scanf_s("%f",&punktzahl);
fflush(stdin);

erg = kommazahl + punktzahl;

printf("\n%f", erg);

return(42);
}