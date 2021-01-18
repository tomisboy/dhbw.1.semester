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
    char fett[4 + 1];

    struct m_nuesse *davor;
    struct m_nuesse *danach;
} t_nuesse;

typedef struct /*"dfjejf"*/
{

    t_nuesse *mom;
    t_nuesse *start;
    t_nuesse *zwischen;

} t_feld;

void up_file_struct(t_feld *f, char text[80 + 1]);
void up_Anzeige_daten(t_feld *f);
void up_listeAdd(t_feld *f, char text[80 + 1]);

int main(void)
{
    int i = 0;
    FILE *einlesen;

    t_feld feld;
    t_feld *f = &feld;

    f->mom = 0;
    f->start = 0;
    f->zwischen = 0;

    char text[63 + 1];

    einlesen = fopen("C:\\nuesse.txt", "r"); // "w" , "a" , "b"

    if (!einlesen)
    {
        printf("\n Datei nicht moeglich zu oeffnen");
    }
    else
    {
        fgets(text, 64, einlesen); // lese 64 zeichen, vorlesen

        while (!feof(einlesen))
        {
            up_listeAdd(f, text);
            fgets(text, 64, einlesen); //nachlesen
        }
        up_Anzeige_daten(f);

        fclose(einlesen);
    }

    return (42);
}

void up_listeAdd(t_feld *f, char text[80 + 1]) // es kommt ein Zeiger f von typ t_feld
{

    f->mom = (t_nuesse *)malloc(sizeof(t_nuesse)); // holt hauptspeciher
    up_file_struct(f, text);                       //( inhalt wird in listelemet übertragen)

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

void up_file_struct(t_feld *f, char text[80 + 1]) // kopiert inhalt globaler vairable in Listelement
{
    strncpy(f->mom->nuss, text, 20);
    f->mom->nuss[20] = '\0';
    strncpy(f->mom->nummer, text + 20, 10);
    f->mom->nummer[10] = '\0';
    strncpy(f->mom->land, text + 30, 25);
    f->mom->land[25] = '\0';
    strncpy(f->mom->fett, text + 55, 5);
    f->mom->fett[4] = '\0'; //ENTFERT NEWLINE
}

void up_Anzeige_daten(t_feld *f)
{
    int i;
    //Tabellenkopf nur einmal
    while (i != 1)
    {

        printf("\nNusssorte        Bezeichnung    Herkunftsland             Fett      ");
        i++;
    };

    f->mom = f->start;

    while (f->mom)
    { //solange mom != 0
        printf("\n%-20s %-10s %-25s %-10s", f->mom->nuss, f->mom->nummer, f->mom->land, f->mom->fett);
        f->mom = f->mom->danach;
    }
}