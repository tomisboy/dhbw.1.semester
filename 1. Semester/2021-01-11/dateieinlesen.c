#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)




typedef struct m_nuesse
{
    char nuss[20 + 1];
    char nummer[10 + 1];
    char land[25 + 1];
    char fett[10 + 1];

    struct nuesse *davor;
    struct nuesse *danach;
} t_nuesse;

typedef struct
{
    char nuss[20 + 1];
    char nummer[10 + 1];
    char land[25 + 1];
    char fett[10 + 1];
    t_nuesse *mom,
        *start,
        *zwischen;
} t_feld;



void up_file_struct(t_feld *f, char text[80+1]);
void up_Anzeige_daten(t_feld *f);
void up_listeAdd(t_feld *f, char text[80+1]);

int main(void)
{

    FILE *einlesen;

    t_feld feld;
    t_feld *f = &feld;

    f->mom = 0;
    f->start = 0;
    f->zwischen = 0;

    char text[80 + 1];




    einlesen = fopen("C:\\nuesse.txt", "r"); // "w" , "a" , "b"

    if (!einlesen)
    {
        printf("\n Datei nicht moeglich zu oeffnen");
    }
    else
    {
        fgets(text, 80, einlesen); // lese 80 zeichen, vorlesen

        while (!feof(einlesen))
        {
           up_listeAdd(f, text);
            up_Anzeige_daten(f),
        
            fgets(text, 80, einlesen); //nachlesen
        }

        fclose(einlesen);
    }

    return (42);
}

void up_listeAdd(t_feld *f, char text[80+1]) // es kommt ein Zeiger f von typ t_feld
{
    f->mom = (t_nuesse *)malloc(sizeof(t_nuesse)); // holt hauptspeciher
    up_file_struct(f, text);                          //( inhalt wird in listelemet übertragen)

    f->mom->davor = f->zwischen; //ZEIGER AUF ZEIGER
    f->mom->danach = 0;
    if (f->zwischen == 0) // (!zwischen)
    {
        f->start = f->mom;
    }
    else
    {
        f->zwischen->danach = f->mom;
    }
    f->zwischen = f->mom;
}

void up_file_struct(t_feld *f, char text[80+1]) // kopiert inhalt globaler vairable in Listelement
{
    strncpy(f->mom->nuss, text, 20);             f->nuss[20] = '\0';
    strncpy(f->mom->nummer, text+20, 10);    f->nummer[10] = '\0';
    strncpy(f->mom->land, text+40, 25);    f->land[25] = '\0';
    strncpy(f->mom->fett, text+65, 10);        f->fett[10] = '\0';

}


void up_Anzeige_daten(t_feld *f){

    f->mom = f->start;

    printf("\nNusssorte           Kalorien      Herkunftsland    Fett      ");

    while(f->mom){                                                                                                      //solange mom != 0
        printf("\n%-20s %-10X %-25X %-10X", f->mom->nuss, f->mom->nummer, f->mom->land, f->mom->fett);
        f->mom = f->mom->danach;
    }
}