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
        up_entferne_datensatz(f);
        break;

    case 6:
        up_speichern(f);
        break;
    case 7:
        up_hex(f);
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

    while (f->mom)                                                                                                              // gehe solange die liste durch bis du das ende = 0 erreichst
    {                                                                                                                           //solange mom != 0
        printf("\n%-18s%-18s%-10d%-24s%d", f->mom->vorname, f->mom->nachname, f->mom->kursnummer, f->mom->email, f->mom->ects); //formatierte Ausgabe der Inhalte des aktuellen Listenelemts
        f->mom = f->mom->danach;                                                                                                //setzte den Zeiger auf den nachfolger, auf das nächste Listenelement
        if (zaehler != 25)                                                                                                      //Überprüfe ob bereits 25 Zeilen ausgegeben wurden
            zaehler++;
        else
        {
            printf("\nEs wurden die ersten 25 Zeilen ausgegeben\num weitere 25 Zeilen auszugeben bitte mit Enter weiter");
            printf("\nWeiter mit Enter Taste ...");
            getchar();
            zaehler = 0;
        }
    }
    printf("\n\nWeiter mit Enter Taste ...");
    getchar();
}

void up_datei_einlesen(t_feld *f)
{
    char text[99 + 1];
    FILE *einlesen;
    einlesen = fopen("./src/input.txt", "r"); // "w" , "a" , "b"

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");
    else
    {
        while (!feof(einlesen))
        {
            fgets(text, 99, einlesen); // lese 99 zeichen, vorlesen
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

void up_liste_Add(t_feld *f, char text[99 + 1]) // es kommt ein Zeiger f von typ t_feld
{
    f->mom = (t_studenten *)malloc(sizeof(t_studenten)); // Reserviert Hauptspeicher von der Größe des Struct-elements t_studenten für nächstes Listenelement
    up_file_struct(f, text);                             //( inhalt wird in listelemet übertragen)

    //Hier passiert werden die Zeiger listen verknüpfungen erstellt

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
    f->mom = f->start;
    while (f->mom)
    {
        printf("\n %-10s mom Zeiger: %10X   mom DAVOR : %10X  mom DANCH : %10X", f->mom->email, f->mom, f->mom->davor, f->mom->danach);

        f->mom = f->mom->danach;
    }
    printf("\nWeiter mit Enter Taste ...");
    getchar();
}

void up_file_struct(t_feld *f, char text[99 + 1])
{
    //In dieser Methode wird der eingelesene Text aufgeteil in die Listenelemente:
    //vorname, nachname, kursnummer, email, ects gespeichert

    //Der eingelesene Text ist eine ganze Zeile und wird der Methode als char text[99 + 1] mitgebenen.

    char tempkurs[10];
    char tempects[5];
    strncpy(f->mom->vorname, text, 20); //kopiert den Vornamen, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (vorname)
    f->mom->vorname[20] = '\0';

    strncpy(f->mom->nachname, text + 20, 20); //kopiert den Nachnamen, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (nachname)
    f->mom->nachname[20] = '\0';

    strncpy(tempkurs, text + 40, 10);
    //tempkurs[10] = '\0';         //Speichert die, an der Stelle 40 stehenden 10 Zeichenelemente, die die Kursnummer abbilden, in ein  char tempkurs[10]
    f->mom->kursnummer = atoi(tempkurs); //umwandlung von der Kursnummer, die als char temp[] durch strncpy kommt, als Int wert, und speichts in die aktuelle Liste an die passende Stelle (kursnummer)

    strncpy(f->mom->email, text + 50, 45); //kopiert die E-Amil , von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (email)
    f->mom->email[45] = '\0';

    strncpy(tempects, text + 95, 5);
    // tempects[5] = '\0';    //Speichert die, an der Stelle 95 stehenden 5 Zeichenelemente ,die die ECTSPunkte abbilden in ein char temp[]
    f->mom->ects = atoi(tempects); //umwandlung von der ECTS, die als char temp[] durch strncpy kommt, als Int wert, und speichts in die aktuelle Liste an die passende Stelle (ects)
}
void up_speichern(t_feld *f)
{
    int i;
    char kurschar[10 + 1]; //für die ausgabe der kursnummer ein Char Array, dieses ist bis jetzt als int in Struc gespeichert
    char *kurscharzeiger = kurschar;

    char etcschar[4 + 1]; //für die ausgabe der ECTS Punkte ein Char Array, dieses ist bis jetzt als int in Struc gespeichert
    char *etcscharzeiger = etcschar;

    FILE *einlesen;
    einlesen = fopen("./src/input1.txt", "w"); //öffnen mit parameter w "leert" die Datei. Öffnen und leert die datei

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");

    //Initialisierung der Array, diese werden mit Leerzeichen die als als Trennsymbolen herhalten gefüllt
    for (i = 0; i < sizeof(kurschar); i++) 
        kurschar[i] = 32;                 
    for (i = 0; i < sizeof(etcschar); i++)
        etcschar[i] = 32;

    f->mom = f->start; //setzte startzeiger auf anfang der Liste

    while (f->mom)
    { //solange mom != 0 gehe solange jedes Listenelement durch bis das Ende (0) erricht wird

        fprintf(einlesen, f->mom->vorname);  //schreiben den Vornamen aus der aktuellen Liste in die Datei
        fprintf(einlesen, f->mom->nachname); //schreiben den Nachnamen aus der aktuellen Liste in die Datei

        sprintf(kurschar, "%d", f->mom->kursnummer);
        //Der Befehl sprintf Konvertiert eine Zahl(int) in ein Char Array, sobald die Zahl zuuende umgewandelt wurden ist wird einen terminierende \0 gesetzt
        //Diese \0 steht aber nicht ganz am ende dieses Arrays kurschar[10 + 1]
        //Im kurschar[] soll aber bis zur 7.Stelle eine Zahlenfolge (Zeichen pro Stelle) gefolgt von 3 Leerzeichen stehen
        //Beispiel die Zahl 482 wird nach der Konvertierung folgendermaßen abgebildet:
        //kurschar[0] = '4'
        //kurschar[1] = '8'
        //kurschar[2] = '2'
        //kurschar[3] = '\0'   <-- diese null wird von der funktion gesetzt
        //kurschar[4] = ' '
        //kurschar[...] = ' '
        //kurschar[10] = ' '
        //wir haben also die Terminierende \0 an der falschen Stelle
        //diese muss an die letzte stelle und dieses wird mit der nachfolgenden Methode bewerkstelligt

        up_bereinige(kurscharzeiger, sizeof(kurschar)); //das Array muss wieder breinigt werden

        fprintf(einlesen, kurschar); //schreiben die umgewandelte und bereinigt Kursnummer aus der aktuellen Liste in die Datei

        fprintf(einlesen, f->mom->email); //schreiben die Emailaus der aktuellen Liste in die Datei

        sprintf(etcschar, "%d", f->mom->ects); //siehe umwandlung kurschar, selbes problem , terminierende 0 an der falschen stelle. Breinigung durch Methodenaufruf
        up_bereinige(etcscharzeiger, sizeof(etcschar));
        fprintf(einlesen, etcschar); //schreiben die umgewandelte und bereinigt ECTS Punktzahl aus der aktuellen Liste in die Datei

        //alle werte in die erste Zeile geschrieben es folgt ein Zeilenumbruch
        fprintf(einlesen, "\n");

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
    // ECTS        maximal 3 stellige Zahl der ECTS-Punkt Anzahl wird übernommen
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
            printf("Bitte den Nachnamen (max 15 Alphabetische-Zeichen keine Sonderzeichen!!!):  ");
            fgets(tmpnachname, sizeof(tmpnachname) - 5, stdin); //Nimm 15 Zeichen der Eingabe und speichere es in tmpnachname
            fflush(stdin);
            fehler = up_text_ueberpruefung(zeigernachname, (sizeof(tmpnachname) - 5)); //Überprüfung der Eingabe  auf Fehler
        } while (fehler != 0);

        do //EINGABE DER KURSNUMMER
        {
            printf("Bitte Kursnummer angeben (max 7 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpkursnummer, sizeof(tmpkursnummer) - 3, stdin); //Nimm 10-3 = 7 Zeichen der Eingabe und speichere es in tmpnachname
            fflush(stdin);
            fehler = up_zahl_ueberpruefung(zeigerkursnummer, sizeof(tmpkursnummer) - 3); //Überprüfung der Eingabe  auf Fehler
        } while (fehler != 0);

        do //EINGABE DER ECTS PUNKT
        {
            printf("Bitte die Anzahl der ECTS Punkte angeben (max 3 Zeichen nur Zahlen erlaubt):  ");
            fgets(tmpects, sizeof(tmpects), stdin); //3 Zeichen der Eingabe und speichere es in tmpects
            fflush(stdin);
            fehler = up_zahl_ueberpruefung(zeigerects, sizeof(tmpects)); //Überprüfung der Eingabe  auf Fehler
        } while (fehler != 0);

        //Setze die E-Mail anhand des vor und nachnames zusammen
        up_emailfeld(zeigervorname, zeigernachname, zeigeremail, sizeof(tmpvorname), sizeof(tmpnachname));

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

        printf("\n\nWollen Sie weiter Werte eingeben, dann Taste: \"j\" \num abzubrechen eine beliebige Taste : \n ");
        scanf("%c", &eingabe);
        fflush(stdin);
    } while (eingabe == 'j'); //uum weitere eingaben zu ermöglichen muss einfach 'j' gedrückt werden
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
        if (bekommenerZeiger[i] >= 'A' && bekommenerZeiger[i] <= 'Z' || bekommenerZeiger[i] >= 'a' && bekommenerZeiger[i] <= 'z')
        {
        }
        else //es gibt ein zeichen, dass nicht im Alphabet ist ODER das ende \n wurde erreicht.
        {
            if (bekommenerZeiger[i] == '\n') //hier wurde das ende des eingebenen Strings gefunden
                break;                       //beendet die forschleife
            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubtes Zeichen!\nBitte nochmal probieren\n");
                fehler = 1;
                break;
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
        else // Dieser Fall tritt ein, wenn es ein Zeichen gibt, dass nicht im numerisch ist ODER das ende "\n" wurde erreicht.
        {
            if (bekommenerZeiger[i] == '\n') //hier wurde das ende des eingebenen Strings gefunden
                break;                       //beendet die forschleife
            else
            {
                printf("\nACHTUNG: Ein Eingabe erhielt ein nicht erlaubtes Zeichen!\nBitte nochmal probieren\n");
                fehler = 1;
                break;
            }
        }
    }
    return fehler;
}
void up_emailfeld(char *zeigervorname, char *zeigernachname, char *zeigeremail, int laengevorname, int laengenachname)
{
    //Methode, um aus den gegebenen Infos: Vor und Nachname eine den Uni-entsprechenen Vorschriften gerechten Emailadresse zu erstellen
    //im format vorname.nachname@uni.de
    //vorname und nachname wir zeichenweise in email geschrieben

    //Zusatzinfos
    //Es gibt bishier im Programm 2 möglichkeiten wie die char[] (vorname und nachname) gefüllt werden können:

    //1 Fall
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
    //[2]'\n'
    //[3]'\0'
    //[4]' ' <-- hier kommen noch die 5 Leerzeichen, als Trennungszeichen für die ausgaben später
    //[...]' '
    //[19]'\0'

    //Trittfall 2 auf muss beim kopieren nur zu der Stelle geschehen, bis das '\n' kommt

    char mailzusatz[7 + 1] = {'@', 'u', 'n', 'i', '.', 'd', 'e'};
    int i, j;

    for (i = 0; i < (laengevorname - 5 - 1); i++) // gehe bis index 14. Eins vor der Terminierenden null, bis hierhin könnte Text stehen
    {
        //Kopiere jedes Zeichen vom Vonamen in das E-Mail Feld solange bis man eben entwerder ein vorzeitiges Ende (FALL 2) (\n) gefunden hat,
        //oder man an der Vorletzten stelle ist
        if (zeigervorname[i] != 10) // 10 ist \n .
            zeigeremail[i] = zeigervorname[i];
        else
            break; // Wird das \n gefundenm, kann direkt abgerochen werden
    }
    //vorname steht nun in zeigervorname
    zeigeremail[i] = '.'; // Setze den punkt der e-Mail zwischen vor und nachname

    for (j = 0; j < (laengenachname - 5 - 1); j++) // gehe bis index 14. Eins vor der Terminierenden null, bis hierhin könnte Text stehen
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
    for (j = 0; j < 7; j++)
    {
        zeigeremail[i + 1] = mailzusatz[j];
        i++;
    }
}
void up_entferne_datensatz(t_feld *f)
{
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
        printf("Bitte geben Sie die E-Mail des zu entfernenden Benutzers\n");
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

                if (f->mom->davor == 0) //Erstes element wurde getroffen
                {
                    f->mom->danach->davor = 0;
                    f->start = f->mom->danach; // im vorherigen element wird der danach zeiger auf 0 gesetzt
                    printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                    geloescht = 1;
                    break;
                }
                if (f->mom->danach == 0) // Letzes Element wurde getroffen
                {
                    f->mom->davor->danach = 0;
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
}
