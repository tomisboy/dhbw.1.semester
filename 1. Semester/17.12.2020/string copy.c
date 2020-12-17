#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

void stringkopie(char *t2, char *t1);

void stringkopie2 (char *t2, char *t1);


int main(void)
{
    char t1[80 + 1], t2[80 + 1];

    strcpy(t1, "Hann0es");

    stringkopie(t2, t1); //es wird nur der Zeiger übergeben

    stringkopie2(t2, t1); //es wird nur der Zeiger übergeben
    printf("---%s--- ---%s---", t1, t2);

    return (42);
}



void stringkopie(char *t2, char *t1)
{
    int i;
    for (i = 0; i < strlen(t1); i++) //
    {
        t2[i] = t1[i];
    }
    t2[i] = 0; //terminierende 0 um String zu schließen
    t2[i] = '\0';
}

void stringkopie2(char *t2, char *t1)

{
while (*t2++ = *t1++); // geht so weit bis die \0 kommt dann steht da while(0) und es ist falsch
// *t == t [i]    * == []
}