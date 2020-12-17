#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

typedef struct //eigenerdatentyo meins angelegt kein Hauptspeicher
{
    int mat[3][4][5];
    char name[5][20 + 1];
    int nr;
} meins;

void up_x(meins *f);
void up_y(meins *f);
int main(void)
{

    meins meinArray;       // 1 element wird angelegt
    meins *f = &meinArray; // ein Zeiger *f holt sich die adresse von meinArray &

    up_x(f); //zeiger wird übergeben
//up_x(&meinArray); geht auch ees kann nur die ADRESSE übergeben werden
    up_y(f);

    return (42);
}

void up_x(meins *f)
{
    f->mat[1][1][2] = 45;
    strcpy(f->name[0], "Hannes");
    
}

void up_y(meins *f)
{
    printf("\n %d", f->mat[1][1][2]);
    printf("\n %s", f->name[0]);
}