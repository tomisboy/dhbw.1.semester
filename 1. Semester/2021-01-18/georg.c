#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys\timeb.h>

#define ANZAHL 10

void init(int *f);
void consoleOutput(int *f);
void quickSort(int *f, int firstElement, int lastElement);
double takeTimeStamp(void);

int main()
{
    double t1, t2, t3;
    int array[ANZAHL];
    int *f = array;
    srand(time(NULL));

    t1 = takeTimeStamp();
    init(f);

    t2 = takeTimeStamp();
    consoleOutput(f);

    t3 = takeTimeStamp();
    quickSort(f, 0, ANZAHL-1);

    consoleOutput(f);

    printf("\n Initialisierung vergangene Zeit: %.3lf sec", t2-t1);
    printf("\n Sortierung vergangene Zeit:      %.3lf sec", t3-t2);


    return 42;
}

void init(int *f)
{
    int i;

    for(i=0; i<ANZAHL; i++) f[i] = rand()%100;
}

void consoleOutput(int *f)
{
    int i;

    for(i=0; i<ANZAHL; i++) printf("%3.d ", f[i]);
    printf("\n\n");
}

void quickSort(int *f, int firstElement, int lastElement)
{
    int iLeft = firstElement, iRight = lastElement, temp;
    int median = (lastElement + firstElement) / 2;

    while(iLeft < iRight)
    {
        while(f[iLeft] < f[median]) iLeft++;
        while(f[iRight] > f[median]) iRight--;

        temp = f[iRight];
        f[iRight] = f[iLeft];
        f[iLeft] = temp;

        if(iLeft == median) median = iRight;
        else if(iRight == median) median = iLeft;

        if(iLeft < median) iLeft++;
        if(iRight > median) iRight--;
    }

    if(iLeft < median-1) quickSort(f, firstElement, median-1);
    if(iRight > median+1) quickSort(f, median+1, lastElement);
}

double takeTimeStamp(void)
{
    struct timeb tb;
    double t;

    ftime(&tb);
    t = tb.time + (double)tb.millitm / 1000.0;
    return t;
}