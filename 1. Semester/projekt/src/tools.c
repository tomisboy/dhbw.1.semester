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
    char text[63 + 1];
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

void up_liste_Add(t_feld *f, char text[63 + 1]) // es kommt ein Zeiger f von typ t_feld
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
void up_file_struct(t_feld *f, char text[63 + 1]) // kopiert inhalt globaler vairable in Listelement
{

    char temp[7];
    strncpy(f->mom->vorname, text, 10);
    f->mom->vorname[10] = '\0';

    strncpy(f->mom->nachname, text + 10, 10);
    f->mom->vorname[20] = '\0';

    strncpy(temp, text + 20, 10);
    f->mom->kursnummer = atoi(temp); //umwandlung von der Kursnummer, die als char[] durch strncpy kommt, als Int wert umwandeln

    strncpy(f->mom->email, text + 30, 25);
    f->mom->email[25] = '\0';
    strncpy(temp, text + 59, 7); //speicher die ECTS Punkte als Chararray speichere (nimm extra 7 um alle werte aus temp[] zu überschreiben )
    f->mom->ects = atoi(temp);   //Umwandeln des ECTS chararrays als INT
}

void up_eingabe_tastatur(t_feld *f)

{
    int i;
    int j;
    int temp;
    int fehler;
    char eingabe;
    char tmptext[63 + 1];
    char *zeigertxt = tmptext;

    char tmpvorname[10 + 1];
    char *zeigervorname = tmpvorname;

    char tmpnachname[10 + 1];
    char *zeigernachname = tmpnachname;

    char tmpkursnummer[7 + 1];
    char *zeigerkursnummer = tmpkursnummer;

    char tmpects[4 + 1];
    char *zeigerects = tmpects;

    char tmpemail[25 + 1];

    char mailzusatz[7 + 1] = {'@', 'u', 'n', 'i', '.', 'd', 'e'};

    //Fülle alle Arrays mit Leerzeichen, ist fürs Speichen später besser
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
            printf("Zuerst bitte den Vornamen (max 10 Zeichen keine Sonderzeichen!!!):  ");
            fgets(tmpvorname, sizeof(tmpvorname), stdin);
            fflush(stdin);
            fehler = textueberpruefung(zeigervorname);
        } while (fehler != 0);

        do //EINGABE DES NACHNAMENS
        {
            printf("Bitte den Nachnamen (max 10 Zeichen keine Sonderzeichen!!!):  ");
            fgets(tmpnachname, sizeof(tmpnachname), stdin);
            fflush(stdin);
            fehler = textueberpruefung(zeigernachname);
        } while (fehler != 0);

        do //EINGABE DER KURSNUMMER
        {
            printf("Bitte Kursnummer angeben (max 7 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpkursnummer, sizeof(tmpkursnummer), stdin);
            fflush(stdin);
            fehler = zahlueberpruefung(zeigerkursnummer);
        } while (fehler != 0);

        do //EINGABE DER ECTS PUNKT
        {
            printf("Bitte die Anzahl der ECTS Punkte angeben (max 3 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpects, sizeof(tmpects), stdin);
            fflush(stdin);
            fehler = zahlueberpruefung(zeigerects);
        } while (fehler != 0);

        printf("\n\nWollen Sie weiter Werte eingeben, so drücken Sie jetzt \"j\" \num abzubrechen wählen sie eine beliebige Taste : \n ");
        scanf("%c", &eingabe);
        fflush(stdin);

    } while (eingabe == 'j');

    //EMAIL
    //tmpvorname sieht nun folgendermaßen aus:
    //[0]'t'
    //[1]'h'
    //[2]''
    //[3]'\0'

    // Wenn der String kleiner als 10 ist muss noch dem \n gesucht werden
    //strncpy(tmpemail, tmpvorname, sizeof(tmpvorname)-2 );
    for (i = 0; i < sizeof(tmpvorname) - 1; i++)
    {
        if (tmpvorname[i] != 10) // 10 ist \n
        {
            tmpemail[i] = tmpvorname[i]; //kopiere den String , bis du fertig bist oder früher schon das \n gefunden hast
        }
        else
            break; // bei vorzeitigen finden des \n wird das kopieren beendet
    }

    tmpemail[i] = '.'; // Setze den punkt der e-Mail zwischen vor und nachname

    for (j = 0; j < sizeof(tmpnachname) - 1; j++)
    {
        if (tmpnachname[j] != 10) // 10 ist \n
        {
            tmpemail[i + 1] = tmpnachname[j]; //kopiere den Nachnahmen an der stelle der email nach dem .
            i++;                              // gehe an die nächste Stelle des Email Arrays
        }
        else
            break; // bei vorzeitigen finden des \n wird das kopieren beendet
    }
    //zusatz @uni.de in den zusammengesetze email hinzufügen an der passenden  stelle
    for (j = 0; j < 7; j++)
    {
        tmpemail[i + 1] = mailzusatz[j];
        i++;
    }
    bereinige(zeigervorname, sizeof(tmpvorname)); // #############
    bereinige(zeigernachname, sizeof(tmpnachname));
    bereinige(zeigerkursnummer, sizeof(tmpkursnummer));
    bereinige(zeigerects, sizeof(tmpects));

    //nun sind alle eingaben bereining und können hintereinander zusammengefügt werden, sodass eine "Zeile" Text entsteht.


    strncpy(tmpvorname, tmptext, 10);
    tmptext[10] = 23;
    strncpy(tmpnachname, tmptext + 10, 10);
    tmptext[20] = 23;
    strncpy(tmpkursnummer, tmptext + 20, 10);
    tmptext[30] = 23;

    strncpy((tmpvorname - 1), tmptext + 20, 10);
    tmptext[30] = 23;
    //  strncpy(temp, text + 20, 10);
    //   f->mom->kursnummer = atoi(temp); //umwandlung von der Kursnummer, die als char[] durch strncpy kommt, als Int wert umwandeln

    //   strncpy(f->mom->email, text + 30, 25);
    //   f->mom->email[25] = '\0';
    //   strncpy(temp, text + 59, 7); //speicher die ECTS Punkte als Chararray speichere (nimm extra 7 um alle werte aus temp[] zu überschreiben )
    //   f->mom->ects = atoi(temp);   //Umwandeln des ECTS chararrays als INT
}

void bereinige(char *bekommenerZeiger, int langeArray)
{
    // Methode um von bekommenen Char[] das  \n zu entfernen  damit nacher einen ganzen string zubauen
    int i;
    //  int j = sizeof(bekommenerZeiger);
    for (i = 0; i < langeArray; i++)
        if (bekommenerZeiger[i] == 10) // Wenn innerhalb der 10 stellen ein \n auftaucht wir dieses und die nächste 0 durch ein SPACE ersetzt
        {
            bekommenerZeiger[i] = 32;
            bekommenerZeiger[i + 1] = 32;
            break;
        }

    bekommenerZeiger[langeArray-1] = 32; //letzte element des Arrays auch durch ein Leerzeichen ersetzen.
}
int textueberpruefung(char *bekommenerZeiger)
{
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
            {
                // tmpvorname[i] = 32; // '\n' durch ein Leerzeichen ersetzt
                break; //beendet die forschleife
            }
            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubt Zeichen! Bitte nochmal probieren\n");
                fehler = 1;
                break;
            }
        }
    }
    return fehler;
}
int zahlueberpruefung(char *bekommenerZeiger)


{
    int i, fehler;
    for (i = 0; i < sizeof(bekommenerZeiger) - 1; i++)
    {
        fehler = 0;
        if (bekommenerZeiger[i] >= '0' && bekommenerZeiger[i] <= '9') //Überprungung ob es eine Zahl ist
        {
        }
        else //es gibt ein zeichen, dass nicht im Alphabet ist ODER das ende \n wurde erreicht.
        {
            if (bekommenerZeiger[i] == '\n') //hier wurde das ende des eingebenen Strings gefunden
            {
                //tmpkursnummer[i] = 32; // '\n' durch ein Leerzeichen ersetzt
                break; //beendet die forschleife
            }
            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubt Zeichen! Bitte nochmal probieren\n");
                fehler = 1;
                break;
            }
        }
    }
    return fehler;
}