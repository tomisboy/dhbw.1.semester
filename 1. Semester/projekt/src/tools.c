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
    printf("\n \n Gebe nun bitte eine Zahl ein:\t");
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
        up_eingabe_tastatur(f);
        break;
    case 3:
        //sortieren
        //unterscheiden ob nach name oder Kursnummer sortiert haben will(f);
        break;
    case 4:
        up_anzeige_daten(f);
        break;
    case 5:
        //up_entferne_daten(f);
        break;

    case 6:
        up_speichern(f);
        break;
    case 7:
        //up_hex();
        break;

    default:
        break;
    }
    return (auswahl);
}

void up_anzeige_daten(t_feld *f)
{
    int zaehler = 0;
    f->mom = f->start;
    printf("\nVorname         Nachname        Kurs       E-Mail                         ECTS      \n");

    while (f->mom)
    { //solange mom != 0
        printf("\n%-15s %-15s %-10d %-25s %8d", f->mom->vorname, f->mom->nachname, f->mom->kursnummer, f->mom->email, f->mom->ects);
        f->mom = f->mom->danach;
        if (zaehler != 25)
            zaehler++;
        else
        {
            printf("\nEs wurden die ersten 25 Zeilen ausgegeben\num weitere 25 Zeilen auszugeben bitte mit Enter weiter");
            printf("\nWeiter mit Enter Taste ...");
            getchar();
            zaehler = 0;
        }
    }
    printf("\nWeiter mit Enter Taste ...");
    getchar();
}

void up_datei_einlesen(t_feld *f)
{
    char text[64 + 1];
    FILE *einlesen;
    einlesen = fopen("./src/input.txt", "r"); // "w" , "a" , "b"

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");
    else
    {
        while (!feof(einlesen))
        {
            fgets(text, 64, einlesen); // lese 64 zeichen, vorlesen
            if (text[0] >= 'A' && text[0] <= 'Z' || text[0] >= 'a' && text[0] <= 'z')
                up_liste_Add(f, text);
            //geh nur in die Schleife wenn der Anfang einer Zeile ein Buchstabe aus dem Alphabet ist
        }
        fclose(einlesen);
        printf("\n\nDaten wurden erfolgreich eingelesen\n\n");
        printf("\nWeiter mit Enter Taste ...");
        getchar();
    }
}

void up_liste_Add(t_feld *f, char text[64 + 1]) // es kommt ein Zeiger f von typ t_feld
{
    f->mom = (t_reservierung *)malloc(sizeof(t_reservierung)); // holt hauptspeciher
    up_file_struct(f, text);                                   //( inhalt wird in listelemet übertragen)

    f->mom->davor = f->zwischen; //ZEIGER AUF ZEIGER
    f->mom->danach = 0;
    if (f->zwischen == 0) // (!zwischen)
        f->start = f->mom;
    else
        f->zwischen->danach = f->mom;
    f->zwischen = f->mom;
}
void up_file_struct(t_feld *f, char text[64 + 1]) // kopiert inhalt globaler vairable in Listelement
{

    char temp[7];
    strncpy(f->mom->vorname, text, 10);
    f->mom->vorname[10] = '\0';

    strncpy(f->mom->nachname, text + 10, 10);
    f->mom->nachname[10] = '\0';

    strncpy(temp, text + 20, 10);
    f->mom->kursnummer = atoi(temp); //umwandlung von der Kursnummer, die als char[] durch strncpy kommt, als Int wert umwandeln

    strncpy(f->mom->email, text + 30, 30);
    f->mom->email[30] = '\0';
    strncpy(temp, text + 60, 7); //speicher die ECTS Punkte als Chararray speichere (nimm extra 7 um alle werte aus temp[] zu überschreiben )
    f->mom->ects = atoi(temp);   //Umwandeln des ECTS chararrays als INT
}
void up_eingabe_tastatur(t_feld *f)

{
    int i, j, temp, fehler, eingabe;
    char tmptext[63 + 1];      //text in dem die ganze eingabe als eine zeile (wie in der Textdatei) gespeichert wird
    char *zeigertxt = tmptext; // Zeiger auf tmptext für methoden

    char tmpvorname[10 + 1];          //hier wird der eingebenene Vorname gespeichert
    char *zeigervorname = tmpvorname; //Zeiger auf tmpvorname für methoden

    char tmpnachname[10 + 1];           //hier wird der eingebenene nachname gespeichert
    char *zeigernachname = tmpnachname; //Zeiger auf tmpnachname für methoden

    char tmpkursnummer[8 + 1];              //hier wird die eingebenene Kursnummer gespeichert
    char *zeigerkursnummer = tmpkursnummer; //Zeiger auf tmpkursnummer für methoden

    char tmpects[5 + 1];        //hier wird die eingebenene ECTS punkzahl gespeichert
    char *zeigerects = tmpects; //Zeiger auf tmpects für methoden

    char tmpemail[30 + 1];        //hier wird die email gespeichert
    char *zeigeremail = tmpemail; //Zeiger auf tmpemail für methoden

    //Fülle alle Arrays mit Leerzeichen, ist fürs Speichen und einlesen später besser
    for (i = 0; i < sizeof(tmptext); i++)
        tmptext[i] = 32;
    for (i = 0; i < sizeof(tmpvorname); i++)
        tmpvorname[i] = 32;
    for (i = 0; i < sizeof(tmpnachname); i++)
        tmpnachname[i] = 32;
    for (i = 0; i < sizeof(tmpemail); i++)
        tmpemail[i] = 32;
    for (i = 0; i < sizeof(tmpkursnummer); i++)
        tmpkursnummer[i] = 32;
    for (i = 0; i < sizeof(tmpects); i++)
        tmpects[i] = 32;

    printf("\nWillkommen zur Eingabe von neuen Studenten\nweiter mit Enter ...\n");
    getchar();

    do
    {
        do //EINGABE DES VORNAMENS
        {
            printf("Zuerst bitte den Vornamen (max 10 Zeichen keine Sonderzeichen erlaubt!!!):  ");
            fgets(tmpvorname, sizeof(tmpvorname), stdin);
            fflush(stdin);
            fehler = textueberpruefung(zeigervorname); //Überprüfung der Eingabe
        } while (fehler != 0);

        do //EINGABE DES NACHNAMENS
        {
            printf("Bitte den Nachnamen (max 10 Zeichen keine Sonderzeichen!!!):  ");
            fgets(tmpnachname, sizeof(tmpnachname), stdin);
            fflush(stdin);
            fehler = textueberpruefung(zeigernachname); //Überprüfung der Eingabe
        } while (fehler != 0);

        do //EINGABE DER KURSNUMMER
        {
            printf("Bitte Kursnummer angeben (max 7 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpkursnummer, sizeof(tmpkursnummer), stdin);
            fflush(stdin);
            fehler = zahlueberpruefung(zeigerkursnummer); //Überprüfung der Eingabe
        } while (fehler != 0);

        do //EINGABE DER ECTS PUNKT
        {
            printf("Bitte die Anzahl der ECTS Punkte angeben (max 3 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpects, sizeof(tmpects), stdin);
            fflush(stdin);
            fehler = zahlueberpruefung(zeigerects); //Überprüfung der Eingabe
        } while (fehler != 0);

        printf("\n\nWollen Sie weiter Werte eingeben, so drücken Sie jetzt \"j\" \num abzubrechen wählen sie eine beliebige Taste : \n ");
        scanf("%c", &eingabe);
        fflush(stdin);

        emailfeld(zeigervorname, zeigernachname, zeigeremail, sizeof(tmpvorname), sizeof(tmpnachname));

        // um die eingaben schon in eine Zeile zusammenzufassen gleich,
        // müssen die einzelnen arrays bereinigt werden
        // \n und die terminierende 0 wird entfernt
        bereinige(zeigervorname, sizeof(tmpvorname));
        bereinige(zeigernachname, sizeof(tmpnachname));
        bereinige(zeigerkursnummer, sizeof(tmpkursnummer));
        bereinige(zeigerects, sizeof(tmpects));

        //nun sind alle eingaben bereining und können hintereinander zusammengefügt werden,
        //sodass eine "Zeile" Text entsteht und diese wird in tmptext gespeichert

        strncpy(tmptext, tmpvorname, 10);
        strncpy(tmptext + 10, tmpnachname, 10);
        strncpy(tmptext + 20, tmpkursnummer, 7);
        strncpy(tmptext + 30, tmpemail, 30);
        strncpy(tmptext + 60, tmpects, 4);
        tmptext[64] = '\n';

        //Die Eingabe wird nun in einer verkettetn Liste gespeichert:

        up_liste_Add(f, tmptext); // der Zeiger vom Hautprogramm und temp text wird der Methode übergeben, die die Daten in die Liste speichern soll.

    } while (eingabe == 'j'); //uum weitere eingaben zu ermöglichen muss einfach 'j' gedrückt werden
}
void bereinige(char *bekommenerZeiger, int langeArray)
{
    // Methode zur Bereinigung von char[] entferne von \n und der terminierenden o
    // Text verarbeitung dadurch einfacher
    int i;
    for (i = 0; i < langeArray; i++)
        if (bekommenerZeiger[i] == 10)     // Wenn innerhalb der 10 stellen ein \n auftaucht wir dieses und die nächste 0 durch ein SPACE ersetzt
            bekommenerZeiger[i] = 32;      // entferne \n
        else if (bekommenerZeiger[i] == 0) // enterne die terminierende 0
            bekommenerZeiger[i] = 32;
}
int textueberpruefung(char *bekommenerZeiger)
{
    //Überprüft ob die die getätigte Eingabe ausschließlich alphatetischen buchstaben beinhaltet
    // gibt einen Fehler zurück.
    int i, fehler;
    for (i = 0; i < sizeof(bekommenerZeiger) - 1; i++)
    {
        fehler = 0;
        if (bekommenerZeiger[i] >= 'A' && bekommenerZeiger[i] <= 'Z' || bekommenerZeiger[i] >= 'a' && bekommenerZeiger[i] <= 'z')
        {
        }
        else //es gibt ein zeichen, dass nicht im Alphabet ist ODER das ende \n wurde erreicht.
        {
            if (bekommenerZeiger[i] == '\n') //hier wurde das ende des eingebenen Strings gefunden
                break;                       //beendet die forschleife
            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubtes Zeichen! Bitte nochmal probieren\n");
                fehler = 1;
                break;
            }
        }
    }
    return fehler;
}
int zahlueberpruefung(char *bekommenerZeiger)
{
    //Überprüft ob die die getätigte Eingabe ausschließlich Zahlen beinhaltet
    // gibt einen Fehler zurück.
    int i, fehler;
    for (i = 0; i < sizeof(bekommenerZeiger) - 1; i++)
    {
        fehler = 0;                                                   //setze Fehler (zurück)
        if (bekommenerZeiger[i] >= '0' && bekommenerZeiger[i] <= '9') //Überprüft die char ob sie Zahlen sind
        {
        }
        else //es gibt ein zeichen, dass nicht im Alphabet ist ODER das ende "\n" wurde erreicht.
        {
            if (bekommenerZeiger[i] == '\n') //hier wurde das ende des eingebenen Strings gefunden
                break;                       //beendet die forschleife
            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubtes Zeichen! Bitte nochmal probieren\n");
                fehler = 1;
                break;
            }
        }
    }
    return fehler;
}
void emailfeld(char *zeigervorname, char *zeigernachname, char *zeigeremail, int laengevorname, int laengenachname)
{
    //Methode um aus den gegebenen Infos: Vor und nachname eine den Unientsprechenen Vorschriften gerechten emailadresse zu erstellen
    // im format vorname.nachname@uni.de
    char mailzusatz[7 + 1] = {'@', 'u', 'n', 'i', '.', 'd', 'e'};
    int i, j;
    //tmpvorname könnte folgerdermaßen aussehen, wenn die eingabe unter 10 Zeichen ist
    //[0]'t'
    //[1]'h'
    //[2]'\n'
    //[3]'\0'

    // Wenn der char (String) kleiner als 10 existier ein \n vor der terminierenden 0
    // Dieses \n muss noch beim kopieren nicht beachtet werden

    for (i = 0; i < laengevorname - 1; i++) //kopiere den die einzellenen Char aus vorname in mail , bis du fertig bist oder früher schon das \n gefunden hast
    {
        if (zeigervorname[i] != 10) // 10 ist \n .
            zeigeremail[i] = zeigervorname[i];
        else
            break; // bei vorzeitigen finden des \n wird das kopieren beendet
    }

    zeigeremail[i] = '.'; // Setze den punkt der e-Mail zwischen vor und nachname

    for (j = 0; j < (laengenachname)-1; j++) // mache jetzt der stelle wo du aufgehört hast weiter (i)
    {
        if (zeigernachname[j] != 10) // 10 ist \n
        {
            zeigeremail[i + 1] = zeigernachname[j]; //kopiere den Nachnamen an der stelle der email nach dem "."
            i++;                                    // gehe an die nächste Stelle des Email Arrays
        }
        else
            break; // bei vorzeitigen finden des \n wird das kopieren beendet
    }
    //zusatz @uni.de in den zusammengesetze email hinzufügen an der passenden  stelle
    for (j = 0; j < 7; j++)
    {
        zeigeremail[i + 1] = mailzusatz[j];
        i++;
    }
}

void up_speichern(t_feld *f)
{
    int i;
    char kurschar[10 + 1];
    char *kurscharzeiger = kurschar;
    char etcschar[4 + 1];
    char *etcscharzeiger = etcschar;

    FILE *einlesen;
    einlesen = fopen("./src/input1.txt", "w"); //öffnen mit parameter w "leert" die Datei

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");

    f->mom = f->start;
    // printf("\nVorname         Nachname        Kurs       E-Mail                         ECTS      \n");

    while (f->mom)
    { //solange mom != 0

        fprintf(einlesen, f->mom->vorname);
        fprintf(einlesen, f->mom->nachname);
        for (i = 0; i < sizeof(kurschar); i++)
            kurschar[i] = 32;                        //letzen wert löschen init // array wieder mit SPACE füllen
        sprintf(kurschar, "%d", f->mom->kursnummer); //konvertiert das int in ein char[]
        bereinige(kurscharzeiger, sizeof(kurschar));
        kurschar[10] = 0; // die null muss am ende stehen
        fprintf(einlesen, kurschar);

        fprintf(einlesen, f->mom->email);

        for (i = 0; i < sizeof(etcschar); i++)
            etcschar[i] = 32; //letzen wert löschen init // array wieder mit SPACE füllen

        sprintf(etcschar, "%d", f->mom->ects); //konvertiert das int in ein char[]etcschar
        bereinige(etcscharzeiger, sizeof(etcschar));
        etcschar[4] = 0;
        fprintf(einlesen, etcschar);

        fprintf(einlesen, "\n");
        printf("\n%-15s %-15s %-10d %-25s %8d", f->mom->vorname, f->mom->nachname, f->mom->kursnummer, f->mom->email, f->mom->ects);
        f->mom = f->mom->danach;
    }
    fclose(einlesen);
}
