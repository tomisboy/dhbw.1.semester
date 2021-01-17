#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    float eingabe = 88.125;
    int exponent = 0;
    char darstellung[32 + 1] = {0};
    int charast = 127;
    char charast_array[8 + 1];

    char mantisse[23 + 1] = {0};
    int gruenzaehler = 1;
    float minus = 0.0;
    //
    while (eingabe > 2)
    {
        eingabe = eingabe / 2;
        exponent++;
    }
    printf("Zahl ist nun %f", eingabe);
    printf("Exponent ist nun %d\n\n\n", exponent);
    // grüner Kasten

    eingabe = eingabe - 1;

    for (gruenzaehler = 1; gruenzaehler <= 26; gruenzaehler++)
    {
        minus = pow(2, (gruenzaehler * (-1)));
        if (eingabe >= minus)
        {
            eingabe = eingabe - minus;
            mantisse[gruenzaehler - 1] = 1;
        }

        else
        {
            //nächster schritt
        }
    }

    //offset addieren
    charast = charast + exponent;
    //wandle nun das int in eine Binaär array um
    itoa(charast, charast_array, 2);
    // char arrays zusammenfügen starte  bei Charakteristik:
    int i = 1;
    for (i = 1; i < strlen(charast_array) +1 ; i++) //
    {
        darstellung[i] = charast_array[i - 1];
        darstellung[i] = darstellung[i] - 48;
    }

    int j ;    // char arrays zusammenfügen starte  bei mantisse:
    for (j = 9; j < 24; j++) //
    {
        darstellung[j] = mantisse[j - 9];
        //darstellung[j] = darstellung[j];
    }
    int z;
    for (z = 0; z < 32; z++)
    {
        printf("%d", darstellung[z]);
        if ((z == 8-1) || (z == 16-1) || (z == 24-1))
            printf("||");
    }

    return (42);
}