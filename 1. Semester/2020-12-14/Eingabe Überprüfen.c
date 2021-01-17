#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{

    int sum = 0, nz, i, l;
    char kto[80 + 1];
    printf("Gib Kontonummer ein");
    scanf("%s", kto);
    fflush(stdin);

    l = strlen(kto);

    for (i = 0; i < l; i++)
    {
        if (kto[i] < 48 || kto[i] > 57)
            nz = 1;
        //hier wird geschaut ob es zwischen 48 und 57 im acsi Code ist
        // durch den char arrays ist es keine ZAHL an sich sindern der wert in der asci Tabelle !!!
        // es gibt kein Convert to !!!
    }

    if (nz == 1)
    {
        //error weil blabla
    }

    // gebe so lange ein bis es Ziffern sind:

  
}