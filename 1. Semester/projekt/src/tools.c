#include "header.h"
int up_menu(t_feld *f)
{
    int key;
    int auswahl;
    printf("\n\tWillkommen im Hauptprogramm\n");
    printf("\nDu kannst folgene Auswahl treffen:\n(Die Eingabe \"0\" beendet das Programm)\n");
    printf("\n 1: Einlesen der input.txt (Dies speichert automatisch die Felder in verketten Listen");
    printf("\n 2: Manuelles eingeben von Daten");
    printf("\n 3: Sortierung");
    printf("\n 4: Anzeigen der Daten ");
    printf("\n 5: Entfernen eines Datensatzes ");
    printf("\n 6: Speichern der Datei");
    printf("\n 7: Anzeige der Zeiger");
    printf("\n 8: Verschluesseln");
    printf("\n 9: Entschluesseln");

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
        up_sortieren(f);
        break;
    case 4:
        up_anzeige_daten(f);
        break;
    case 5:
        up_entferne_datensatz(f);
        break;

    case 6:
        up_speichern(f);
        break;
    case 7:
        up_hex(f);
        break;
    case 8:
        key = verschluesseln(f);
        break;
    case 9:
        entschluesseln(f, key);
        break;
    default:
        break;
    }
    return (auswahl);
}

void up_anzeige_daten(t_feld *f)
{
    int zaehler = 0;
    f->mom = f->start; //Starte beim ersten Listenelement
    printf("\nVorname             Nachname            Kurs      E-Mail                                       ECTS\n");

    while (f->mom) // gehe solange die liste durch bis du das ende = 0 erreichst
    {
        //Gibt aktuellen Listenelemente formatiert aus
        printf("\n%-18s%-18s%-10s%-24s%s", f->mom->vorname, f->mom->nachname, f->mom->kursnummer, f->mom->email, f->mom->ects);
        f->mom = f->mom->danach; //setzte den Zeiger auf den nachfolger, auf das nächste Listenelement
        if (zaehler != 25)       //Überprüfe ob bereits 25 Zeilen ausgegeben wurden
            zaehler++;           //Zähle die ausgebenen Listen aus
        else
        { //Es wurden 25 Zeichen eingelesen
            printf("\nEs wurden die ersten 25 Zeilen ausgegeben\num weitere 25 Zeilen auszugeben bitte mit Enter weiter");
            printf("\nWeiter mit Enter Taste ...");
            getchar();
            zaehler = 0; //Setzte Zähler zurück
        }
    }
    printf("\n\nWeiter mit Enter Taste ...");
    getchar();
}
void up_datei_einlesen(t_feld *f)
{

    //DATEI EINLESEN UND DOPPELTE ENTFERNEN :)
    char text[99 + 1];
    char *zeigertext = text; //in diesem Array wird eine ganze Zeile aus der Datei gespeichert
    FILE *einlesen;
    einlesen = fopen("input.txt", "r"); //Öffnet die Datei zum Lesen "read"
    int fehler = 0;
    int ersteZeile = 0;

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");
    else
    {
        while (!feof(einlesen))
        {
            fgets(text, 99, einlesen);            // Lese 99 Zeichen der input Datei ein (eine ganze Zeile)
            if (text[0] >= 'A' && text[0] <= 'Z') //Lese ausschließlich Zeilen ein, die mit Großbuchtaben (alpahbetischen Zeichen) beginnen
            {
                if (f->start == 0) //Wenn die List leer ist wird der das allererste erste Element geschrieben, ohne zu Überprüfen ob es doppelt vorkommt
                    up_liste_Add(f, text);

                //Überprüfe ob der einzulesende Wert in der Liste bereits vorkommt(Kriterium ist Email die an stelle (zeigertext + 50 steht)
                fehler = up_suche_doppelte_elemente(f, (zeigertext + 50));
                if (fehler == 0)           //nur wenn der Wert nicht in den LIsten vorkommt schreibe füge die Zeile den Listen hinzu
                    up_liste_Add(f, text); //Lese nur ein, wenn das erste Zeichen der Zeile ein Buchstaben oder eine Zahlen ist
            }
        }
        fclose(einlesen); //schließe Datei

        printf("\n\nDaten wurden erfolgreich eingelesen\n\n");
        printf("\nWeiter mit Enter Taste ...");

        getchar();
    }
}
void up_liste_Add(t_feld *f, char text[99 + 1])
{
    f->mom = (t_studenten *)malloc(sizeof(t_studenten)); // Reserviert Hauptspeicher von der Größe des Struct-elements t_studenten für nächstes Listenelement
    up_file_struct(f, text);                             //( inhalt wird in listelemet übertragen)

    //Hier werden die Zeiger listen verknüpfungen erstellt

    f->mom->davor = f->temp;      //Von aktelle neu erzeugtem mom element das Feld davor ist temp, was der vorgänger ist ----
    f->mom->danach = 0;           //Von aktelle neu erzeugtem mom element das Feld danach wird 0 gesetzt.                   |
    if (f->temp == 0)             //erster Fall temp ist noch von der Initi auf 0                                           |
        f->start = f->mom;        //erstes Element der Liste wird festgelegt                                                |
    else                          //                                                                                        |
        f->temp->danach = f->mom; //vom Vorgänger, das Zeigerelement "danach" wird der akutell neu erzeugt mom Zeiger       |
    f->temp = f->mom;             //temp Zeiger wird der aktuelle neu erzeugte mom zeiger       <----------------------------
}
void up_hex(t_feld *f)
{
    f->mom = f->start; //gehe zum ersten Listenelement
    while (f->mom)     //wiederhole solange das Ende nicht ereicht wurde
    {                  //gebe die Zeiger des aktuellen Listenelements aus
        printf("\n %-10s mom Zeiger: %10X   mom DAVOR : %10X  mom DANACH : %10X", f->mom->email, f->mom, f->mom->davor, f->mom->danach);
        f->mom = f->mom->danach; //gehe zum
    }
    printf("\nWeiter mit Enter Taste ...");
    getchar();
}
void up_file_struct(t_feld *f, char text[99 + 1])
{
    //In dieser Methode wird der eingelesene Text aufgeteil in die Listenelemente:
    //vorname, nachname, kursnummer, email, ects gespeichert

    //Der eingelesene Text ist eine ganze Zeile und wird der Methode als char text[99 + 1] mitgebenen.

    strncpy(f->mom->vorname, text, 20); //kopiert den Vornamen, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (vorname)
    f->mom->vorname[20] = '\0';

    strncpy(f->mom->nachname, text + 20, 20); //kopiert den Nachnamen, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (nachname)
    f->mom->nachname[20] = '\0';

    //  strncpy(tempkurs, text + 40, 10);
    //tempkurs[10] = '\0';         //Speichert die, an der Stelle 40 stehenden 10 Zeichenelemente, die die Kursnummer abbilden, in ein  char tempkurs[10]
    //    f->mom->kursnummer = atoi(tempkurs); //umwandlung von der Kursnummer, die als char temp[] durch strncpy kommt, als Int wert, und speichts in die aktuelle Liste an die passende Stelle (kursnummer)
    strncpy(f->mom->kursnummer, text + 40, 10);
    f->mom->kursnummer[10] = '\0';

    strncpy(f->mom->email, text + 50, 45); //kopiert die E-Amil , von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (email)
    f->mom->email[45] = '\0';

    strncpy(f->mom->ects, text + 95, 5);
    f->mom->ects[5] = '\0'; //Speichert die, an der Stelle 95 stehenden 5 Zeichenelemente ,die die ECTSPunkte abbilden in ein char temp[]
}
void up_speichern(t_feld *f)
{
    int i;
    char kurschar[10 + 1]; //für die ausgabe der kursnummer ein Char Array, dieses ist bis jetzt als int in Struc gespeichert
    char *kurscharzeiger = kurschar;

    char etcschar[4 + 1]; //für die ausgabe der ECTS Punkte ein Char Array, dieses ist bis jetzt als int in Struc gespeichert
    char *etcscharzeiger = etcschar;

    FILE *einlesen;
    einlesen = fopen("output.txt", "w"); //öffnen mit parameter w "leert" die Datei. Öffnen und leert die datei

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");

    //Initialisierung der Array, diese werden mit Leerzeichen die als als Trennsymbolen herhalten gefüllt
    up_char_init(kurscharzeiger, sizeof(kurschar));
    up_char_init(etcscharzeiger, sizeof(etcschar));

    /*
    for (i = 0; i < sizeof(kurschar); i++)
        kurschar[i] = 32;
    for (i = 0; i < sizeof(etcschar); i++)
        etcschar[i] = 32;
*/
    f->mom = f->start; //setzte startzeiger auf anfang der Liste

    while (f->mom)
    {                                          //solange mom != 0 gehe solange jedes Listenelement durch bis das Ende (0) erricht wird
        fprintf(einlesen, f->mom->vorname);    //schreiben den Vornamen aus der aktuellen Liste in die Datei
        fprintf(einlesen, f->mom->nachname);   //schreiben den Nachnamen aus der aktuellen Liste in die Datei
        fprintf(einlesen, f->mom->kursnummer); //schreiben die umgewandelte und bereinigt Kursnummer aus der aktuellen Liste in die Datei
        fprintf(einlesen, f->mom->email);      //schreiben die Emailaus der aktuellen Liste in die Datei
        fprintf(einlesen, f->mom->ects);       //schreiben die umgewandelte und bereinigt ECTS Punktzahl aus der aktuellen Liste in die Datei
        fprintf(einlesen, "\n");               //alle werte in die erste Zeile geschrieben es folgt ein Zeilenumbruch

        f->mom = f->mom->danach; //nächsten Listenelement
    }
    fclose(einlesen); //Datei wird geschlossen
}
void up_eingabe_tastatur(t_feld *f)

{
    //Methode um Benutzer das anlegen eines Neuen Benutzers zu ermöglichen:
    //Der eingegebene Benutzer wird anschließend in der Verketteten Liste angefügt

    //Randbedingungen:
    //Eingaben erfolge nach Abfrage :
    // Vorname      maximal 15 Zeichen (alphanumerisch) werden übernommen
    // Nachname     maximal 15 Zeichen (alphanumerisch) werden übernommen
    // Kursnummer   maximal 7 Zeichen (nur Zahlen) werden übernommen
    // ECTS         maximal 3 stellige Zahl der ECTS-Punkt Anzahl wird übernommen
    //die passende E-Mail-Adresse wird automatisch erstellt.

    int i, j, temp, fehler;
    char eingabe;
    char tmptext[99 + 1];      //text in dem die ganze eingabe zusammengebaut als eine zeile (wie in der Textdatei) gespeichert wird
    char *zeigertxt = tmptext; // Zeiger auf tmptext für methoden

    char tmpvorname[20 + 1];          //15 Zeichen des Vornamens + 5 "trennzeichen"
    char *zeigervorname = tmpvorname; //Zeiger auf tmpvorname für methoden

    char tmpnachname[20 + 1];           //15 Zeichen des Nachnames + 5 "trennzeichen"
    char *zeigernachname = tmpnachname; //Zeiger auf tmpnachname für methoden

    char tmpkursnummer[10 + 1];             //7 Zeichen de Kursnummer  + 3 "trennzeichen"
    char *zeigerkursnummer = tmpkursnummer; //Zeiger auf tmpkursnummer für methoden

    char tmpects[3 + 1];        //3 Zeichen des ETCS Punkte + 2 "trennzeichen"
    char *zeigerects = tmpects; //Zeiger auf tmpects für methoden

    char tmpemail[50 + 1];        //45 zeichen der Email vorname.nachname@uni.de
    char *zeigeremail = tmpemail; //Zeiger auf tmpemail für methoden

    //Fülle alle Arrays mit Leerzeichen, diese Zeichen sind für das getrennte ausgeben (trennungszeichen) da.

    up_char_init(tmptext, sizeof(tmptext));
    up_char_init(tmpnachname, sizeof(tmpnachname));
    up_char_init(tmpemail, sizeof(tmpemail));
    up_char_init(tmpkursnummer, sizeof(tmpkursnummer));
    up_char_init(tmpects, sizeof(tmpects));

    /* //for (i = 0; i < sizeof(tmptext); i++)
    //  tmptext[i] = 32;
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
        
*/
    printf("\nWillkommen zur Eingabe von neuen Studenten\nweiter mit Enter ...\n");
    getchar(); //warte auf ENTER

    do
    {

        do //EINGABE DES VORNAMENS
        {
            printf("Zuerst bitte den Vornamen (max 15 Alphabetische-Zeichen keine Sonderzeichen erlaubt!!!):  ");
            fgets(tmpvorname, sizeof(tmpvorname) - 5, stdin); //Nimm 15 Zeichen der Eingabe und speichere es in tmpvorname
            fflush(stdin);
            fehler = up_text_ueberpruefung(zeigervorname, (sizeof(tmpvorname) - 5)); //Überprüfung der Eingabe auf Fehler
        } while (fehler != 0);

        do //EINGABE DES NACHNAMENS
        {
            printf("Bitte den Nachnamen (max 15 Alphabetische-Zeichen keine Sonderzeichen erlaubt!!!):  ");
            fgets(tmpnachname, sizeof(tmpnachname) - 5, stdin); //Nimm 15 Zeichen der Eingabe und speichere es in tmpnachname
            fflush(stdin);
            fehler = up_text_ueberpruefung(zeigernachname, (sizeof(tmpnachname) - 5)); //Überprüfung der Eingabe  auf Fehler
        } while (fehler != 0);

        do //EINGABE DER KURSNUMMER
        {
            printf("Bitte Kursnummer angeben (7 Stellige Zahl):  ");
            fgets(tmpkursnummer, sizeof(tmpkursnummer) - 3, stdin); //Nimm 10-3 = 7 Zeichen der Eingabe und speichere es in tmpnachname
            fflush(stdin);
            fehler = up_zahl_ueberpruefung(zeigerkursnummer, sizeof(tmpkursnummer) - 3); //Überprüfung der Eingabe  auf Fehler
        } while (fehler != 0);

        do //EINGABE DER ECTS PUNKT
        {
            printf("Bitte die Anzahl der ECTS Punkte angeben (3 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpects, sizeof(tmpects), stdin); //3 Zeichen der Eingabe und speichere es in tmpects
            fflush(stdin);
            fehler = up_zahl_ueberpruefung(zeigerects, sizeof(tmpects)); //Überprüfung der Eingabe  auf Fehler
        } while (fehler != 0);

        fehler = 0; //fehlercode wurde zurückgesetzt falls einmal eine Fehleingaben passierte wird der nun resettet:

        //Setze die E-Mail anhand des vor und nachnames zusammen dies ist das entscheidene merkmal eines users(primary Key)
        //Überprüfe auch gleich ob diese E-Mail bereits vorkam
        fehler = up_emailfeld(f, zeigervorname, zeigernachname, zeigeremail, sizeof(tmpvorname), sizeof(tmpnachname));

        if (fehler == 0) //mache nur weiter wenn e-mail überprüfung eine 0 liefert wenn es keine doppelt vorkommende email gibt
        {

            // um die eingaben schon in eine Zeile zusammenzufassen gleich,
            // müssen die einzelnen arrays bereinigt werden
            // \n und die terminierende 0 wird entfernt, wenn sie vor dem eigentlichen ende des Stings kommt:
            up_bereinige(zeigervorname, sizeof(tmpvorname));
            up_bereinige(zeigernachname, sizeof(tmpnachname));
            up_bereinige(zeigerkursnummer, sizeof(tmpkursnummer));
            up_bereinige(zeigerects, sizeof(tmpects));

            //nun sind alle Eingaben bereining und können hintereinander zusammengefügt werden,
            //sodass eine "Zeile" Text entsteht und diese wird in tmptext gespeichert

            strncpy(tmptext, tmpvorname, 20);         //Kopiere nun den Inhalt von tmpvorname bis stelle 15 stehen buchstaben dann folgen 5 Leerzeichen (als Trennzeichen)
            strncpy(tmptext + 20, tmpnachname, 20);   //Hänge nun den Inhalt von tmpnachname  (bis stelle 15 stehen buchstaben dann folgen 5 Leerzeichen (als Trennzeichen)) an die passende stelle im String
            strncpy(tmptext + 40, tmpkursnummer, 10); //Hänge nun den Inhalt von tmpkursnummer (bis stelle 7 stehen zahlen dann folen 3 Leerzeichen (als Trennzeichen))  an die passende stelle im String
            strncpy(tmptext + 50, tmpemail, 45);      //Hänge nun den Inhalt von tmpemail (bis stelle 45 steht die E-Mail dann folgen 5 Leerzeichen (als Trennzeichen)) an die passende stelle im String
            strncpy(tmptext + 95, tmpects, 5);        //Hänge nun den Inhalt von tmpects (bis stelle 15 stehen buchstaben dann folgen 5 Leerzeichen (als Trennzeichen)) an die passende stelle im String
            tmptext[99] = '\0';                       //Markiere das ente der char Arrays

            //Die Eingabe ist nun genau so in dem Format wie sie in der input.txt (pro Zeile) steht.
            //daruch kann diese eingabe als Parameter für die up_liste_Add übergeben werden um sie in die verkette Liste zu speichern
            //Die Einga
            up_liste_Add(f, tmptext); // der Zeiger vom Hautprogramm und tmptext wird der Methode übergeben, die die Daten in die Liste speichern soll.
            printf("\nFolgender Student wurde erfolgreich eingelegt \n%s\n%s\n%s\n", f->mom->vorname, f->mom->nachname, f->mom->email);
        }

        printf("\n\nWollen Sie weitere Werte eingeben, oder die Eingabe wiederholen , dann Taste: \"j\"\num abzubrechen eine beliebige Taste :\n");
        scanf("%c", &eingabe);
        fflush(stdin);

    } while ((eingabe == 'j')); //uum weitere eingaben zu ermöglichen muss einfach 'j' gedrückt werden
}
void up_bereinige(char *bekommenerZeiger, int langeArray)
{
    // Methode zur Bereinigung von char[] entferne von \n und einer vorzeitigen terminierenden \0
    // überprüft ob innerhalb einer char[] bis zur vorletzten stelle ein \n oder eine \0 steht
    // Wenn ja dann wir dieses Zeichen und folgende (bis zur vorletzen stelle) durch ein " " (Leerzeichen) ersetzt
    // Text verarbeitung dadurch einfacher vereinfacht
    int i;
    for (i = 0; i < langeArray - 1; i++)                               //überprüfe bis zur vorletzen element ob eine termierende 0 oder \n vorkommt
        if ((bekommenerZeiger[i] == 10) || (bekommenerZeiger[i] == 0)) // Wenn ein \n oder \0 auftaucht, wir diesesdurch ein Leerezeichen ersetzt
        {
            bekommenerZeiger[i] = 32; // ersetze ungültiges Zeichen
            break;                    //beendet forschleife an der stelle der vorzeitigen terminierenden null
        }
    for (i + 1; i < langeArray - 1; i++) //starte beim abgebrochen index der vorherigen schleife
        bekommenerZeiger[i] = 32;        // fülle bis an die Vorletzte Stelle alles mit Leerzeichen auf

    bekommenerZeiger[i] = '\0'; //An die allerletzte stelle des char[] wird die terminierende \0 gesetzt
}
int up_text_ueberpruefung(char *bekommenerZeiger, int langeArray)
{
    //Überprüft ob die die getätigte Eingabe ausschließlich alphatetischen buchstaben beinhaltet
    // gibt einen Fehler zurück.
    int i, fehler;
    for (i = 0; i < langeArray - 1; i++)
    {
        fehler = 0;
        //Erstes Zeichen wird in Großbuchstaben umgewandelt
        if (bekommenerZeiger[0] >= 'a' && bekommenerZeiger[0] <= 'z')
            bekommenerZeiger[0] = bekommenerZeiger[0] - 32; //gehe 32 schritte im Acsi Code zurück

        if (bekommenerZeiger[i] >= 'A' && bekommenerZeiger[i] <= 'Z' || bekommenerZeiger[i] >= 'a' && bekommenerZeiger[i] <= 'z')
        {
        }
        else //es gibt ein zeichen, dass nicht im Alphabet ist ODER das ende \n wurde erreicht.
        {
            if (bekommenerZeiger[0] == '\n') //Aller erstes element ist falsch (Bei der Eingabe wurde nur ENTER gedrückt)
            {
                fehler = 1;
                printf("\nACHTUNG: Bitte gebe etwas ein\n");
                break; //beendet die forschleife
            }
            else if (bekommenerZeiger[i] == '\n') //hier wurde das ende des eingebenen Strings gefunden
                break;                            //beendet die forschleife

            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubtes Zeichen! \t %c \t \nBitte nochmal probieren\n", bekommenerZeiger[i]);
                fehler = 1;
                break; //beendet die forschleife
            }
        }
    }
    return fehler;
}
int up_zahl_ueberpruefung(char *bekommenerZeiger, int langeArray)
{
    //Überprüft ob die die getätigte Eingabe ausschließlich Zahlen beinhaltet
    // gibt einen Fehler zurück wen dem nicht so ist .
    int i, fehler;
    for (i = 0; i < langeArray - 1; i++)
    {
        fehler = 0;                                                   //setze Fehler (zurück)
        if (bekommenerZeiger[i] >= '0' && bekommenerZeiger[i] <= '9') //Überprüft die einzelnen Zeichenob sie Zahlen sind
        {
        }
        else
        {
            if (bekommenerZeiger[i] == '\n') //Sobald ein \n gefunden wurde bedeutet dies, das Char Array ist nicht vollständig gefüllt!
            {
                fehler = 1; // Fehler weil char array nicht die notwendige Anzahl der Stellen erfüllt
                printf("\nEingaben enthielt zu wenig Stellen\n ");
                printf("Sie müssen %d Stellen angeben (Wenn Eingabe kleiner als %d Stellen ist, geben sie 0 an den Anfang\n", langeArray - 1, langeArray - 1);
                printf("\nBitte nochmal probieren\n");
                break;
            }
            else
            {
                fehler = 1;
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubtes Zeichen! \t %c \t \nBitte nochmal probieren\n", bekommenerZeiger[i]);
                break;
            }
            //dieser Fall titt ein wenn nicht alle Stellen gefüllt worden sind
        }
    }
    return fehler;
}
int up_emailfeld(t_feld *f, char *zeigervorname, char *zeigernachname, char *zeigeremail, int laengevorname, int laengenachname)
{
    //Methode, um aus den gegebenen Infos: Vor und Nachname eine den Uni-entsprechenen Vorschriften gerechten Emailadresse zu erstellen
    //im format vorname.nachname@uni.de
    //vorname und nachname werden zeichenweise in email geschrieben
    //Überprüft auch ob diese E-Mail bereits vorhanden ist und gibt einen Fehler zurück

    //Zusatzinfos
    //Es gibt bishier im Programm 2 möglichkeiten wie die char[] (vorname und nachname) gefüllt werden können:

    //1 Fall:
    //das Char Array wurde vollständig gefüllt bis an stelle 15 -->
    //[0]'t'
    //[1]'h'
    //[...]'x'
    //[13]'e'
    //[14]'\0'
    //[15]' '<-- hier kommen noch die 5 Leerzeichen, als Trennungszeichen für die ausgaben später
    //[...]' '
    //[19]'\0'

    //2. Fall:
    //wenn aber die Eingabe der Zeichen kleiner als 15 war, kommt an die letzte stelle ein '\n' das Enter
    //tmpvorname könnte folgerdermaßen aussehen, wenn die eingabe unter 10 Zeichen ist
    //[0]'t'
    //[1]'h'
    //[2]'\n'  <-- Vorzeitiges Ende wird mit \n gekennzeichnet
    //[3]'\0'
    //[4]' ' <-- hier kommen noch die 5 Leerzeichen, als Trennungszeichen für die ausgaben später
    //[...]' '
    //[19]'\0'

    //Trittfall 2 auf muss beim kopieren nur zu der Stelle geschehen, bis das '\n' kommt

    char mailzusatz[7 + 1] = {'@', 'u', 'n', 'i', '.', 'd', 'e'};
    int i, j, fehler = 0;

    for (i = 0; i < (laengevorname - 5 - 1); i++) // gehe bis index 14 des vornamens. Eins vor der Terminierenden null, bis hierhin könnte Text stehen
    {
        //Kopiere jedes Zeichen vom Vonamen in das E-Mail Feld solange bis man eben entwerder ein vorzeitiges Ende (FALL 2) (\n) gefunden hat,
        //oder man an der Vorletzten stelle ist
        if (zeigervorname[i] != 10) // 10 ist \n .
            zeigeremail[i] = zeigervorname[i];
        else
            break; // Wird das \n gefundenm, kann direkt abgerochen werden
    }
    //vorname steht nun in zeigeremail
    zeigeremail[i] = '.'; // Setze den punkt der e-Mail zwischen vor und nachname

    for (j = 0; j < (laengenachname - 5 - 1); j++) // gehe bis index 14 der nachnames. Eins vor der Terminierenden null, bis hierhin könnte Text stehen
    {
        if (zeigernachname[j] != 10) // 10 ist \n
        {
            zeigeremail[i + 1] = zeigernachname[j]; //kopiere den Nachnamen an der stelle der email nach dem "."
            i++;                                    // gehe an die nächste Stelle des Email Arrays
        }
        else
            break; // Wird das \n gefundenm, kann direkt abgerochen werden
    }
    //zusatz @uni.de wird hinter dem Nachnamen nun noch drangehängt
    for (j = 0; j < 7; j++) //hänge zeichenweise mit einer for schleife an, da die trennzeichen
    {
        zeigeremail[i + 1] = mailzusatz[j];
        i++;
    }

    zeigeremail[45] = '\0'; //terminierende 0 setzen
    f->mom = f->start;      //gehe auf den Startzeiger

    // Es wird überprüft, ob die E-Mail bereits in der der Liste vorkommt
    fehler = up_suche_doppelte_elemente(f, zeigeremail);

    if (fehler == 1)
    {
        printf("\n\n\tAchtung E-Mail ist bereits vorhanden\n\n\tDieser Benutzer kann nicht angelegt werden !");
    }

    return fehler;
}
void up_entferne_datensatz(t_feld *f)
{
    int auswahl;
    /////////

    printf("\n Was willstdu entfernen");
    printf("\n '1' Fure die leerung aller Listenelemente");
    printf("\n '2' für die Entfernung einzelner Bentutzer");
    printf("\n '3' Fure die leerung aller Listenelemente\n");

    scanf("%i", &auswahl);
    fflush(stdin);

    switch (auswahl)
    {
    case 1:
    {
        f->mom = 0;
        f->start = 0;
        f->temp = 0;
        break;
    }

    case 2:
    {
        ///////
        //gebe E-Mail ein
        //sucher nach e-mail
        /// vom voränger Zeiger muss der nachfolger auf den übernächsten gesetzt werden
        // vom nachfolger Zeiger muss der voränger auf den vor vor letzten Zeiger
        char eingabe[45 + 1];
        char tmpeingabe[45 + 1];
        int i;
        int geloescht; //Überprüft ob ein Wert gelöscht worden ist
        char taste;    //eingabetaste für wiederholtes löschen von Datensätzen

        do
        {
            geloescht = 0;
            for (i = 0; i < sizeof(eingabe); i++) //Fülle den char Array mit Leerzeichen
                eingabe[i] = 32;                  // muss in der do while passieren, da bei mehrer eingaben
                                                  //das Array neu "leer" gemacht werden sollte
            printf("Bitte geben Sie die E-Mail des zu entfernenden Benutzers ein\n");
            fgets(eingabe, sizeof(eingabe) - 5, stdin);
            up_bereinige(eingabe, sizeof(eingabe));

            f->mom = f->start; //gehe auf den Startzeiger

            while (f->mom) // DU STARTET AM LETZEN ELEMENT GERADE gehe solange die liste durch bis du das ende = 0 erreichst
            {
                if ((strcmp(eingabe, f->mom->email))) //String compare liefert 0 wenn die Strings gleich sind
                {
                }
                else
                { //Strucelement das gelöscht werden soll wurde gefunden
                    //er gibt 3 möglichkeiten: Das ersten, letzte, oder mittendrinn soll gelöscht werden

                    f->mom->email[0] = '0'; //leert das E-Mail feld, damit die E-Mail nicht mehr in einer Liste steht
                    if (f->mom->davor == 0) //Erstes element wurde getroffen
                    {
                        f->mom->danach->davor = 0;
                        f->start = f->mom->danach; // im vorherigen element wird der danach zeiger auf 0 gesetzt
                        f->temp = f->mom;
                        printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                        geloescht = 1;
                        break;
                    }
                    if (f->mom->danach == 0) // Letzes Element wurde getroffen
                    {
                        f->mom->davor->danach = 0;
                        f->temp = f->mom->davor; //<-- Wichtig das vorletzte Element wird nun das zwischen element,
                        //damit beim löschen des Letzten elements immer noch welche hinzugefügt werden können, durch up_liste_Add
                        printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                        geloescht = 1; // im vorherigen element wird der danach zeiger auf 0 gesetzt
                        break;
                    }

                    else // Element mittendrinne wurde getroffen
                    {
                        f->mom->davor->danach = f->mom->danach; //Setze den Nachfolger des Vorgängers auf den übernächsten Zeiger
                        f->mom->danach->davor = f->mom->davor;  //Setze den Vorgänger der Nachfolgers auf den vorherigen Zeiger ein Element dahinter

                        printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                        geloescht = 1;
                        break;
                    }
                }
                f->mom = f->mom->danach; //Nächstes Element
            }

            if (!geloescht) //Alle Listen sind durchgelaufen, es wird überprüft ob was gelöscht wurden
                printf("\nACHTUNG Die E-Mail \t %s \t wurde nicht gefunden, es wurde nichts entfernt\n", eingabe);

            printf("\n\nWollen Sie weiter Werte entfernen, oder eine die Eingabe wiederholen, dann Taste: \"j\" \num abzubrechen eine beliebige Taste : \n ");
            scanf("%c", &taste);
            fflush(stdin);
        } while (taste == 'j');
        break;
    }

    default:
        break;
    }
}
int up_suche_doppelte_elemente(t_feld *f, char *zeigertext)
{
    //Methode überprüft, ob die Inhalte der neu eingelesenen Zeile bereits in einer der Listenelementen vorkommt.
    //Als entscheidendes kriterium,(und übergabe Paramter) wird die E-Mail benutze, da diese einmalig ist und nicht doppelt vorkommen darf/kann.

    int fehler = 1;
    char temp[45 + 1];                 //Hier wird die E-Mail drinne gespeichert der eingelesenen Zeile
    f->mom = f->start;                 //setzte startzeiger auf anfang der Liste
    strncpy(temp, zeigertext, 45 + 1); //Schreibe die E-Mail (eindeutiges Element eines Benutzers) in ein temp
    temp[45] = '\0';                   //terminierede Null wird gesetzt

    while (f->mom) //gehe alle elemente der Liste durch
    {
        if (strcmp(temp, f->mom->email)) //String compare liefert 0 wenn die Strings gleich sind
            fehler = 0;
        else
        {
            fehler = 1; // wenn die E-Mail aus der aktuell ausgelesen Zeile in bereits einer Liste vorkommt, dann gibt es einen Fehler
            break;      //breche die Schleife ab
        }
        f->mom = f->mom->danach; // geht zum nächsten Listenelement
    }
    return fehler;
}
void up_sortieren(t_feld *f)
{
    int i, j, zaehler = 0;

    int auswahl;
    f->mom = f->start;
    while (f->mom) //Zählt die Anzahl der Listenelemente
    {
        f->mom = f->mom->danach;
        zaehler++;
    }
    f->mom = f->start; //gehe auf den Startzeiger

    printf("\n Du kannst nach folgenden Kriterien sortieren");
    printf("\n '1' für die Sortierung des Vornamens");
    printf("\n '2' für die Sortierung des Nachnames");
    printf("\n '3' für die Sortierung der Kursnummer\n");

    scanf("%i", &auswahl);
    fflush(stdin);

    switch (auswahl)
    {
    case 1:
    {
        printf("\n In welcher Reihenfolge, soll sortiert werden\n\t'1' für aufsteigend\n\t'2' für absteigend\n");
        do
        {
            scanf("%i", &auswahl);
            fflush(stdin);
        } while (auswahl != 1 && auswahl != 2);

        if (auswahl == 1) ///KURSNUMMER ABSTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // absteigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->vorname, f->mom->danach->vorname) > 0)
                        zeiger_tausch(f); //Wenn die erste Stelle größer ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        else ///KURSNUMMER AUFTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // austeigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->vorname, f->mom->danach->vorname) < 0)
                        zeiger_tausch(f); //Wenn die erste Stelle kleiner ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        break;
    }
    case 2:
    {
        printf("\n In welcher Reihenfolge, soll sortiert werden\n\t'1' für aufsteigend\n\t'2' für absteigend\n");
        do
        {
            scanf("%i", &auswahl);
            fflush(stdin);
        } while (auswahl != 1 && auswahl != 2);

        if (auswahl == 1) ///KURSNUMMER ABSTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // absteigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->nachname, f->mom->danach->nachname) > 0)
                        zeiger_tausch(f); //Wenn die erste Stelle größer ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        else ///KURSNUMMER AUFTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // austeigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->nachname, f->mom->danach->nachname) < 0)
                        zeiger_tausch(f); //Wenn die erste Stelle kleiner ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }

        break;
    }

    case 3:
    {
        printf("\n In welcher Reihenfolge, soll sortiert werden\n\t'1' für aufsteigend\n\t'2' für absteigend\n");
        do
        {
            scanf("%i", &auswahl);
            fflush(stdin);
        } while (auswahl != 1 && auswahl != 2);

        if (auswahl == 1) ///KURSNUMMER ABSTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // absteigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->kursnummer, f->mom->danach->kursnummer) > 0)
                        zeiger_tausch(f); //Wenn die erste Stelle größer ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        else ///KURSNUMMER AUFTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // austeigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->kursnummer, f->mom->danach->kursnummer) < 0)
                        zeiger_tausch(f);    //Wenn die erste Stelle kleiner ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach; //Nächstes Element
                }
            }
            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }

        break;
    }

    default:
        break;
    }
}
void zeiger_tausch(t_feld *f)
{
    int zeigerspeichen;
    zeigerspeichen = f->mom; // merke dir die aktuelle position vor der vertauschung
    int temp;

    //Hier passiert die Magie des Vertauschen 2er aufeinanderfolgenden Elemente einer Liste:
    // Es müssen 6 Zeiger umgebogen werden
    //Dabei gibt es 2 Fälle zum Beachten dass entweder das erste oder das Letzte element getauscht wird

    //IST Situation:

    //####################################################################################################################
    //              [6]                                     [1]                 [3]                                     //
    //      <---------------------  [ELEMENT  X     ]        <-----------    [ELEMENT  Y           ] <----------------  //
    //                              [ x = f->mom    ]	                     [ y = f->mom->danach  ]                    //
    //       ---------------------> [ELEMENT  X     ]        ----------->    [ELEMENT  Y           ] ---------------->  //
    //              [5]                                         [2]                        [4]                          //
    //####################################################################################################################

    //SOLL  Situation:
    //####################################################################################################################
    //              [6]                                        [1]             [3]                                      //
    //      <---------------------  [ELEMENT Y          ]   <-----------    [ELEMENT x     ] <----------------          //
    //                              [ y = f->mom->danach]	                [ x = f->mom   ]                            //
    //      --------------------->  [ELEMENT  Y         ]   ----------->    [ELEMENT x     ] ---------------->          //
    //              [5]                                        [2]             [4]                                      //
    //####################################################################################################################
    /*
    */
    // x stellt des erste element dar, das mit y getauscht wird
    //x = f->mom  (das aktuelle Listenelement )  y= f->mom->danach (das nächste Listenelement)

    temp = f->mom->danach->danach; //Nachfolger von y muss zwischengespeichert werden
    //Der vorgänger vom Nachfolger von y wird nur dann 0 wenn da auch einer steht, sonst ist es eben x
    if (f->mom->danach->danach != 0) // !(mach nicht nach dir kommt nichts mehr du bist letzten )
        f->mom->danach->danach->davor = f->mom;

    //der nachfolger vom vorgänger von x wird nur dann 0 wenn da auc was steht
    if (f->mom->davor != 0)
        f->mom->davor->danach = f->mom->danach;

    //Der Vorgänger von y wird der Vorgänger von x könnte auch eine 0 stehen ist aber egal
    f->mom->danach->davor = f->mom->davor;

    //Vorgänger von x  wird y
    f->mom->davor = f->mom->danach;

    //Nachfolger von y wird x sein
    f->mom->danach->danach = f->mom;

    //Nachfolger von x , wird nachfolger von y // kann auch ruhig eine null sein
    f->mom->danach = temp;

    //Setzte den Startwert auf das, möglicherweise neu an die erste Stelle verschobenen Listenelement
    if (f->mom->davor->davor == 0) //
        f->start = f->mom->davor;  // setzte erste anfang auf richtig stelle

    //Da nach dieser Method in der Forschleife der Index wieder hochgezählt wird,
    //muss dieses um eine stelle reduziert werden.
    //der Momentanzeiger liegt ja bisher auf dem nächste index  (eben durch die Vertauschung)
    //damit nun nicht doppelt hochgezählt wird wird der hier reduziert und erst auserhalb der Methode hochgezählt)
    f->mom = zeigerspeichen;
    f->mom = f->mom->davor;
}
int verschluesseln(t_feld *f)
{
    //E-Mail wird verschlüsselt

    const MOD = 60;

    int i, eingabe_key, key;
    printf("Code zum Verschluesseln eingeben\n");
    scanf("%i", &eingabe_key);
    fflush(stdin);

    // Für die berechnung des wertes das auf den klartext addiert wird
    f->mom = f->start;
    key = eingabe_key % MOD + 65; // 65 weil, verschlüsseltes Zeichen, soll kein @ enthalten, daher fangen wir beim asci code 1 weiter an
    //Algorithumu
    //Cäsar Verfahren addiere auf den char ASCI wert eine geheime Zahl drauf. Daruf wird ein anderes Zeichen ausgegeben

    while (f->mom) // gehe die Liste durch
    {
        for (i = 0; i < 45; i++)
        {
            if (f->mom->email[i] == 64) //Verschlüssele solange du bis auf das @ Zeichen triffst
                break;
            else
                f->mom->email[i] = f->mom->email[i] + key; //Hier wird der wert auf den asci Code addiert (die eigentlich Verschlüsselung )
        }
        f->mom = f->mom->danach;
    }
    printf("\n alle E-Mails wurden verschluesselt,\n");
    printf("\n\nWeiter mit Enter Taste ...");
    getchar();
    return eingabe_key;
}
void entschluesseln(t_feld *f, int key)
{
    const MOD = 60; // Für die berechnung des wertes das auf den klartext addiert wird

    int i, eingabe_key;
    printf("Code zum Entschluesseln eingeben\n");
    scanf("%i", &eingabe_key);
    fflush(stdin);

    f->mom = f->start; //setzte start
    if (key == eingabe_key)
    {
        key = key % MOD + 65;
        while (f->mom) //Geht die Liste durch
        {
            for (i = 0; i < 45; i++) //ENTSCHLÜSSLEN
            {
                if (f->mom->email[i] == 64) // wenn du das "Klartext" "@" findest kannst du aufhören zu entschlüsseln
                    break;
                else
                    f->mom->email[i] = f->mom->email[i] - key; //entschlüsselung . Ziehe den zum verschlüsselung addierten wert nun wieder ab
            }
            f->mom = f->mom->danach;
        }

        printf("\n alle E-Mails wurden entschluesselt,\n");
        printf("\n\nWeiter mit Enter Taste ...");
        getchar();
    }
    else
        printf("Der Code War falsch");
}

up_char_init(char *array, int lange)
{
    //Fülle Char arrays mit Leerzeichen
    int i;
    for (i = 0; i < lange; i++)
        array[i] = 32;
}
