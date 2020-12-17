#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)
#include <time.h>

int main(void)
{
    char datum[80 + 1];
    up_datum(datum);

    printf("\n %s", datum);

    return (42);
}

void up_datum(char *datum)
{

    char htext[80 + 1];
    struct tm *zeit; //Zeiger von Strukturmusster aus der time.headerfile

    time_t sek;

    time(&sek); // füllte die sek mit anzahl seit 1.1.1970 //adresse wird übergeben von sek

    zeit = localtime(&sek); // legt von strukturmuster tm eine Struktur an und gibt Zeiger zurück

    switch (zeit->tm_wday)
    {
    case 0:
        strcpy(datum, "Sonntag, den ");
        break;
    case 1:
        strcpy(datum, "Montag , den ");
        break;
    case 2:
        strcpy(datum, "Dienstag, den ");
        break;
    case 3:
        strcpy(datum, "Mittwoch, den ");
        break;
    case 4:
        strcpy(datum, "Donnerstag, den ");
        break;
    case 5:
        strcpy(datum, "Freitag, den ");
        break;
    case 6:
        strcpy(datum, "Samstag, den ");
        break;

    default:
        printf("fehlerduwohfduio");
        break;
    }

    itoa(zeit->tm_mday, htext, 10);
    strcat(datum, htext);
    strcat(datum, ".");

    switch (zeit->tm_mon)
    {
    case 0:
        strcat(datum, " Jan");
        break;
    case 1:
        strcat(datum, " Feb ");
        break;
    case 2:
        strcat(datum, " Maerz ");
        break;
    case 3:
        strcat(datum, " April");
        break;
    case 4:
        strcat(datum, " Mai ");
        break;
    case 5:
        strcat(datum, " Juni");
        break;
    case 6:
        strcat(datum, " Juli");
        break;
    case 7:
        strcat(datum, " August");
        break;
    case 8:
        strcat(datum, " September");
        break;
    case 9:
        strcat(datum, " Oktober");
        break;
    case 10:
        strcat(datum, " November");
        break;
    case 11:
        strcat(datum, " Dezemeber");
        break;
        strcat(datum, htext);
    }
    itoa(zeit->tm_mon, htext, 10);
    strcat(datum, " ");



    itoa(zeit->tm_year + 1900, htext, 10);
    strcat(datum, htext);
}