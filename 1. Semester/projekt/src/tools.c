#include "header.h"
int up_menu(t_feld *f)
{

    int auswahl;
    printf("\nDu kannst folgene Auswahl treffen:\n (Die Eingabe \"0\" beendet das Programm)\n");
    printf("\n 1: Einlesen der input.txt (Dies speichert automatisch die Felder in verketten Listen");
    printf("\n 2: Manuelles eingeben von Daten");
    printf("\n 3: Sortierung");
    printf("\n 4: Anzeigen der Daten ");
    printf("\n 5: Entfernen eines Datensatzes ");
    printf("\n 6: Speichern der Datei");
    printf("\n 7: Anzeige der Zeiger");
    printf("\n \n Gebe nur bitte eine Zahl ein:\t");
    scanf("%i", &auswahl);
    fflush(stdin);

    switch (auswahl)
    {
    case 0:
        printf("Bis Bald ! \n Programm wird nun geschlossen\n");
        break;
    case 1:
        up_datei_einlesen(f);
        break;
    case 2:
        //up_eingabe_tastatur(f);
        break;
    case 3:
        //sortieren
        //unterscheiden ob nach name oder Kursnummer sortiert haben will(f);
        break;
    case 4:
        //up_anzeige_daten(f);
        break;
    case 5:
        //up_entferne_daten(f);
        break;

    case 6:
        //up_speichern;
        break;
    case 7:
        //up_hex();
        break;

    default:
        break;
    }
    return (auswahl);
}

void up_datei_einlesen(t_feld *f)
{
    char text[63 + 1];
    FILE *einlesen;
    einlesen = fopen("./src/input.txt", "r"); // "w" , "a" , "b"

    if (!einlesen)
    {
        printf("\n Datei nicht moeglich zu oeffnen");
    }
    else
    {
        fgets(text, 64, einlesen); // lese 64 zeichen, vorlesen

        while (!feof(einlesen))
        {
            up_liste_Add(f, text);
            fgets(text, 64, einlesen); //nachlesen
        }
        // up_Anzeige_daten(f);

        fclose(einlesen);
    }
}

void up_liste_Add(t_feld *f, char text[63 + 1]) // es kommt ein Zeiger f von typ t_feld
{

    f->mom = (t_reservierung *)malloc(sizeof(t_reservierung)); // holt hauptspeciher
    up_file_struct(f, text);                                   //( inhalt wird in listelemet übertragen)

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
void up_file_struct(t_feld *f, char text[63 + 1]) // kopiert inhalt globaler vairable in Listelement
{
    char temp[7];
    strncpy(f->mom->name, text, 20);
    f->mom->name[20] = '\0';
    strncpy(temp, text + 20, 10);
    f->mom->Kursnummer = atoi(temp);
//

//geti(text + 20, 10)
//
    //strncpy(f->mom->Kursnummer, text + 20, 10);
  //  f->mom->Kursnummer[10] = '\0';
    strncpy(f->mom->email, text + 30, 25);
    f->mom->email[25] = '\0';
    strncpy(temp, text + 55, 5);
    f->mom->ects = atoi(temp);
}
