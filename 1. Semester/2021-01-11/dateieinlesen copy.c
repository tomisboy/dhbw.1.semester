#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    char nuss[15 + 1];
    char id[10 + 1];
    char land[25 + 1];
    char fett[10 + 1];

    FILE *einlesen;
    char text[800 + 1];

    einlesen = fopen("C:\\nuesse.txt", "r"); // "w" , "a" , "b"

    if (!einlesen)
    {
        printf("\n Datei nicht moeglich zu oeffnen");
    }
    else
    {
        fgets(text, 800, einlesen); // lese 80 zeichen, vorlesen
        printf("\nNusssorte  \n         ID       \n  LAND       \n   Fett    \n      \n");
        while (!feof(einlesen))
        {
            strncpy(nuss, text, 15);  nuss[15] = '\0';
            strncpy(id, text + 20, 10); id[10] = '\0';
            strncpy(land, text + 20 + 10, 25); land[25] = '\0';
            strncpy(fett, text + 20 + 10 + 25, 10);  fett[10] = '\0';
            printf("%s                  %s                    % s          %s\n", nuss, id, land, fett);
            fgets(text, 57, einlesen);
        }

        fclose(einlesen);
system("Pause");
        return (42);
    }
}
