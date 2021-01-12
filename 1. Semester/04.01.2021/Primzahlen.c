#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)
#include <sys\timeb.h>

double timeStamp(void);

int main(void)
{
    int i = 0, j = 0, counter = 0, bereich = 0;
    double time1, time2;

    //eingabe des Bereiches durch den Benutzer hat nicht geklappt;
    //printf("Bitte geb dein Zahlenbreich ein: ");  //
    //scanf(" %d", &bereich);
    //  ++++++++++++++++++++++++++++++++++++
    //  +char Zahlenbereich[bereich] = {0};+
    //  ++++++++++++++++++++++++++++++++++++
    //Das geht so hier in Visual Studio Codes nicht
    // in C Lion geht das komischerweise.

    time1 = timeStamp();
    char Zahlenbereich[1000 + 1] = {0};
    //keine Primzahlen werden werden 1
    for (i = 2; i < 1000; i++)
    {
        if (Zahlenbereich[i] == 0)
        {
            for (j = 2 * i; j < 1000; j += i)
            {
                Zahlenbereich[j] = 1; // alle vielfachen einer primzahl Zahl streichen
            }                         // keine Primzahlen werden mit 1 markiert
            counter++;                //
        }
    }
    time2 = timeStamp();
    printf("Anzahl der Primzahlen ist %d", counter);
    printf("\n Der Computer hat  %.3lf sec. gebraucht", time2 - time1);
    return (42);
}

double timeStamp(void)
{
    struct timeb tb;
    double t;

    ftime(&tb);
    t = tb.time + (double)tb.millitm / 1000.0;
    return t;
}