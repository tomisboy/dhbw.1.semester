#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

//LIST ELEMENT
typedef struct m_dhler
{
    char name[20 + 1];
    int prn;
    struct m_dhler *davor;
    struct m_dhler *danach;
} t_dhler;

typedef struct
{
    char name[20 + 1];
    int prn;
    t_dhler *mom,
        *start,
        *zwischen;
} t_feld;

void up_listeAdd(t_feld *f);
void up_struct_liste(t_feld *f);
void up_hex(t_feld *f);
void up_Datei_einlesen(t_feld *f);
void up_Eingabe_Tastatur(t_feld *f);
void up_Anzeige_Daten(t_feld *f);
void up_menu(void);


int main(void)
{
    int auswahl = -999;

    t_feld feld;
    t_feld *f = &feld;

    f->mom = 0;
    f->start = 0;
    f->zwischen = 0;

    while (auswahl != 0)
    {
         fflush(stdin);
        up_menu();
        scanf("%i", &auswahl);
        fflush(stdin);

        switch (auswahl)
        {
        case 0:
            auswahl = 0;
            break;
        case 1:
            up_Datei_einlesen(f);
            break;
        case 2:
            up_Eingabe_Tastatur(f);
            break;
        case 4:
            up_Anzeige_Daten(f);
            break;


        default:
            break;
        }
    }
    

    return (42);
}

void up_menu(void)
{
    
    printf("\n");
    printf("\n treffe eine Auswahl ... gib Nr ein:");
    printf("\n 1 einlesen von Datei");
    printf("\n 2 eingeben von Tastatur");
    printf("\n 4 anzeigen von Datensätzen\n ");
}

//###


void up_Eingabe_Tastatur(t_feld *f)
{
        int i;

    for (i = 0; i < 3; i++)
    {
        fflush(stdin);
        printf("\n Gib %d.Namen ein :) ", i + 1);
        scanf("%s", f->name);
        fflush(stdin);
        up_listeAdd(f); //Zeiger wird übergeben
    }

   // up_hex(f); //Zeiger wird übergeben

}
//######


void up_Datei_einlesen(t_feld *f)
{
}

//####
void up_Anzeige_Daten(t_feld *f)
{

 f->mom = f->start;
    while (f->mom)
    {
        printf("\n %-10s momentan Zeiger: %10X   momentan DAVOR : %10X  momentan DANCH : %10X", f->mom->name, f->mom, f->mom->davor, f->mom->danach);

        f->mom = f->mom->danach;
    }
}
//#####
//######
void up_listeAdd(t_feld *f) // es kommt ein Zeiger f von typ t_feld
{
    f->mom = (t_dhler *)malloc(sizeof(t_dhler)); // holt hauptspeciher
    up_struct_liste(f);                          //( inhalt wird in listelemet übertragen)

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


//###
void up_struct_liste(t_feld *f) // kopiert inhalt globaler vairable in Listelement
{
    strcpy(f->mom->name, f->name);
    //.. alle weiteren werden übertragen
}
//####
void up_hex(t_feld *f)
{
    f->mom = f->start;
    while (f->mom)
    {
        printf("\n %-10s momentan Zeiger: %10X   momentan DAVOR : %10X  momentan DANCH : %10X", f->mom->name, f->mom, f->mom->davor, f->mom->danach);

        f->mom = f->mom->danach;
    }
}