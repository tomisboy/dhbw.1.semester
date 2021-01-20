#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
//#include <sys\timeb.h>
#pragma warning(disable : 4996)

//LIST ELEMENT
typedef struct m_studenten
{
    char vorname[15 + 5 + 1];  //15 Zeichen + 5 formatierungszeichen
    char nachname[15 + 5 + 1]; //  //nacbhName des  schülers 15 Zeichen + 5 formatierungszeichen
    int kursnummer;            //die kursnummer als INT gespeichert um bubble sort
    char email[40 + 5 + 1];    // 40 zeichen + 5 formatierungszeichen
    int ects;                  //Bereits erreichte ECTS Punkte
    struct m_studenten *davor;
    struct m_studenten *danach;
    struct m_studenten *vorvor;   //Vor-Vorgänger Speicher für Methode löschen
    struct m_studenten *nachnach; //Nach/NAch-Vorgänger Speicher für Methode löschen

} t_studenten;

typedef struct
{
    t_studenten *mom;
    t_studenten *start;
    t_studenten *temp;
} t_feld;

int up_menu(t_feld *f);

void up_datei_einlesen(t_feld *f);
void up_eingabe_tastatur(t_feld *f);
void up_bubble(int *f);
void up_anzeige_daten(t_feld *f);
void up_hex(t_feld *f);

void up_liste_Add(t_feld *f, char text[99 + 1]);
void up_struct_liste(t_feld *f);
void up_bereinige(char *bekommenerZeiger, int langeArray);
int up_text_ueberpruefung(char *bekommenerZeiger, int langeArray);
int up_zahl_ueberpruefung(char *bekommenerZeiger, int langeArray);

void up_emailfeld(char *zeigervorname, char *zeigernachname, char *zeigeremail, int laengevorname, int laengenachname);
void up_speichern();
void up_entferne_datensatz(t_feld *f);