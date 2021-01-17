#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{

    char wert = 120;

    //durch weißen wir die Adresse zu
    char *t;

    int i = 7;
    float f = 12.34;
    double d = 29.45;

    char bu;
    char text[80 + 1];
    strcpy(text, "Hannes ist schlau");
    t = text;
 /*   scanf("%d", &i);
    fflush(stdin);
    scanf("%f", &f);
    fflush(stdin);
    scanf("%lf", &d);
    fflush(stdin);
    scanf("%c", &bu);
    fflush(stdin);
    scanf("%s", text);
*/

    printf("\n ---%s---", text);
    printf("\n ---%s---", t);
    printf("\n ---%s---", text);
    printf("\n ---%s---", text+6);
    

    
    
    return (42);

}