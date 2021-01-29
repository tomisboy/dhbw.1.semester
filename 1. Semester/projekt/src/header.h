//Thomas Alpert
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#pragma warning(disable : 4996)

//LIST ELEMENT
typedef struct m_studenten
{
  char vorname[15 + 5 + 1];  //15 Zeichen + 5 formatierungszeichen
  char nachname[15 + 5 + 1]; //  //nacbhName des  schülers 15 Zeichen + 5 formatierungszeichen
  char kursnummer[7 + 3 + 1];
  char email[40 + 5 + 1]; // 40 zeichen + 5 formatierungszeichen
  //int ects;
  char ects[3 + 1]; //Bereits erreichte ECTS Punkte
  struct m_studenten *davor;
  struct m_studenten *danach;

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
void zeiger_anzeigen(t_feld *f);

void up_neues_Listenelement(t_feld *f, char text[99 + 1]);
void up_text_zu_Liste(t_feld *f,char text[99 + 1]);
void up_bereinige(char *bekommenerZeiger, int langeArray);
int up_text_ueberpruefung(char *bekommenerZeiger, int langeArray);
int up_zahl_ueberpruefung(char *bekommenerZeiger, int langeArray);

int up_emailfeld(t_feld *f, char *zeigervorname, char *zeigernachname, char *zeigeremail, int laengevorname, int laengenachname);
void up_speichern();
void up_entferne_datensatz(t_feld *f);
int up_suche_doppelte_elemente(t_feld *f, char *zeigertext);

void up_sortieren(t_feld *f);

void up_zeiger_tausch(t_feld *f);

int up_verschluesseln(t_feld *f);
void up_entschluesseln(t_feld *f, int key);

void up_char_init(char *array, int lange);
void up_suche(t_feld *f);