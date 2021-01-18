#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys\timeb.h>
#pragma warning(disable : 4996)

#define ANZAHL 10
//up_init(int f *);

//up_ausgabe(int f *);
void up_init(int *f);
void up_bubble(int *f);
void up_ausgabe(int *f);
double timeStamp(void);
void up_quick(int *f, int links, int rechts);

int main(void)
{
    int links, rechts;
    double t1, t2, t3, t4;
    t1 = timeStamp();
    int folge[ANZAHL];
    int *f = folge;
    up_init(f);
    printf("Zufällige Zahlen Kombi \n");
    up_ausgabe(f); //vor der sortierung
    
    printf("\nAusgabe der durch Bublesort sortierten Zahlen:\n");
    
    t1 = timeStamp();
    up_bubble(f);
    t2 = timeStamp();
    up_ausgabe(f);

    printf("\nAusgabe der durch Quicksort sortierten Zahlen:\n");
    t3 = timeStamp();
    up_quick(f, links, ANZAHL - 1);
    t4 = timeStamp();
    up_ausgabe(f);

    printf("\n\nDie Zeit fuer die Berechnung des BubbleSort betraegt: %3lf sec.", t2 - t1);
    printf("\n-----------------------------");
    printf("\n\nDie Zeit fuer die Berechnung des Quicksrt betraegt: %3lf sec.", t4 - t3);
    return (42);
}

void up_bubble(int *f)
{
    int temp, i, j;
    for (i = 0; i < ANZAHL - 1; i++)
    {
        for (j = 0; j < ANZAHL - 1; j++)
        {
            if (f[j] > f[j + 1])
            {
                temp = f[j];
                f[j] = f[j + 1];
                f[j + 1] = temp;
            }
        }
    }
}

void up_ausgabe(int *f)
{

    int i;

    for (i = 0; i < ANZAHL; i++)
    {
        printf("%d \t ", f[i]);
    }
}

void up_init(int *f)
{
    int i;

    for (i = 0; i < ANZAHL; i++)
    {
        f[i] = rand() * rand() % 100 + 1;
    }
}

double timeStamp(void)
{
    struct timeb tim;
    double t;

    ftime(&tim);
    t = tim.time + (double)tim.millitm / 1000.0;
    return t;
}

void up_quick(int *f, int links, int rechts)
{
    int ili, ire, med, temp;

    ili = links;
    ire = rechts;
    med = (links + rechts) / 2;

    while (ili < ire)
    {
        while (f[ili] < f[med])
            ili++;
        while (f[ire] > f[med])
            ire--;

        temp = f[ire];
        f[ire] = f[ili];
        f[ili] = temp;

        if (ili == med)
            med = ire;
        else
        {
            if (ire == med)
                med = ili;
        }
        if (ili < med)
            ili++;

        if (ire > med)
            ire--;
    }
    if (links < med - 1)
    {
        up_quick(f, links, med - 1);
    }

    if (rechts > med + 1)
    {
        up_quick(f, med + 1, rechts);
    }
}