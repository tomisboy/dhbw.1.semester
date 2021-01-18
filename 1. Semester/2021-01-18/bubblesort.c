#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys\timeb.h>
#pragma warning(disable : 4996)

#define ANZAHL 1000
//up_init(int f *);

//up_ausgabe(int f *);
void up_init(int *f);
void up_bubble(int *f);
void up_ausgabe(int *f);
double timeStamp(void);

int main(void)
{

    double t1, t2;
    t1 = timeStamp();
    int folge[ANZAHL];
    int *f = folge;
    up_init(f);
    up_ausgabe(f); //vor der sortierung
    t1 = timeStamp();
    up_bubble(f);
    up_ausgabe(f);
    t2 = timeStamp();

    printf("\n\nDie Zeit fuer die Berechnung betraegt: %3lf sec.", t2 - t1);
    printf("\n-----------------------------");

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

    printf("\nZahlen im Array:\n");

    for (i = 0; i < ANZAHL; i++)
    {
        printf("%d\n", f[i]);
    }
}

void up_init(int *f)
{
    int i;

    for (i = 0; i < ANZAHL; i++)
    {
        f[i] = rand() * rand() % 10000 + 1;
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