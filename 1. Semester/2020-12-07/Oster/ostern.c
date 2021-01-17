#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void)
{
    int Jahreszahl, restA, restB, restC, restD, restE, tage, starttag, ostertag;
    restA = 0;
    restB = 0;
    restC = 0;
    restD = 0;
    restE = 0;
    tage = 0;
    Jahreszahl = 1900;
    char temp;

    while (Jahreszahl <= 2099)
    {
        for (int i = 0; i <= 9; i++)
        {

            if (Jahreszahl == 1954 || Jahreszahl == 1981)
            {
                printf("\n Im Jahr %i, gibt es kein Ostern\n", Jahreszahl);
            }
            else
            {
                restA = Jahreszahl % 19;
                restB = Jahreszahl % 4;
                restC = Jahreszahl % 7;
                restD = (19 * restA + 24) % 30;
                restE = (2 * restB + 4 * restC + 6 * restD + 5) % 7;
                tage = restD + restE;

                if (tage <= 9)
                {
                    starttag = 22;
                    ostertag = starttag + tage;
                    printf("\n Ostern fällt im Jahr %i auf den %i März", Jahreszahl, ostertag, 0x84);
                }
                else
                    starttag = 0;
                ostertag = starttag + (tage - 9);
                printf("\n Ostern fällt im Jahr %i auf den %i April", Jahreszahl, ostertag);
            }

            Jahreszahl++;
        }

        printf("\n-------------- Bitte eine Taste druecken --------------");
        scanf("%c", &temp);
        fflush(stdin);
    }
    return (0);
}
