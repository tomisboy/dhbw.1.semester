#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
//#include <sys\timeb.h>
#pragma warning(disable : 4996)

//LIST ELEMENT
typedef struct m_reservierung
{
    char vorname[10 + 1];   
    char nachname[10 + 1];   //Name des Kunden
    int Kursnummer;  //Reservierte Zimmernummer
    char email[25 + 1];     //Studentenemail
    int ects;          //Bereits erreichte ECTS Punkte
    struct m_reservierung *davor;
    struct m_reservierung *danach;
} t_reservierung;

typedef struct
{
    t_reservierung *mom;
    t_reservierung *start;
    t_reservierung *zwischen;
} t_feld;

int up_menu(t_feld *f);

void up_datei_einlesen(t_feld *f);
void up_eingabe_tastatur(t_feld *f);
void up_bubble(int *f);
void up_anzeige_daten(t_feld *f);
void up_hex(t_feld *f);

void up_liste_Add(t_feld *f, char text[63 + 1]);
void up_struct_liste(t_feld *f);
//void up_speichern()
// SPEICHERN DER DATEI fehlt;
