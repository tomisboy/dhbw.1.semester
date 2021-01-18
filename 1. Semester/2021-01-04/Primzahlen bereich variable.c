
//Sieb des Erathostenes
//Programmentwurf von André Schwabauer vom 12.01.2021

#include <stdio.h>		
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys\timeb.h>
#pragma warning(disable:4996)

double timeStamp(void);

int main(void)
{
	double t1, t2;
	unsigned int scope = 0;
	unsigned int i, primzahlcounter = 0;
	char* p;

	printf("Geben sie einen Bereich an: ");
	scanf("%d", &scope);
	fflush(stdin);

	t1 = timeStamp();


//	p = (char*)malloc(scope * sizeof(char));


    p = (char*)malloc(scope * sizeof(char));


	if (NULL == p)
	{
		printf("Fehler bei der Speicherreservierung!\n");
		return EXIT_FAILURE;
	}



	p[0] = 0;
	p[1] = 0;


	for (i = 2; i < scope + 1; i++)
	{
		p[i] = 1;
	}

	for (i = 2; i < scope + 1; i++)
	{
		if (p[i] == 1)
		{

			primzahlcounter++;
			unsigned int j;

			for (j = i; j <= scope; j = j + i)
			{
				p[j] = 0;
			}
		}
		else
		{
			p[i] = 0;
		}
	}


	printf("Es gibt %d Primzahlen bis %d", primzahlcounter, scope);

	t2 = timeStamp();

	printf("\n\nDie Zeit fuer die Berechnung betraegt: %3lf sec.", t2 - t1);
	printf("\n-----------------------------");

	return 42;
}

double timeStamp(void)
{
	struct timeb tim;
	double t;

	ftime(&tim);
	t = tim.time + (double)tim.millitm / 1000.0;
	return t;
}