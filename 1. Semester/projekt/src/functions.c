//Thomas Alpert
#include "header.h"

int up_menu(t_feld *f)
{
    int passwort, auswahl;
    system("cls");
    printf("\n\tWillkommen im Hauptprogramm\n");
    printf("\nDu kannst folgene Auswahl treffen:\n(Die Eingabe \"0\" beendet das Programm)\n");
    printf("\n 1: Einlesen der input.txt ");
    printf("\n 2: Anlegen eines neuen Studentens");
    printf("\n 3: Sortierung");
    printf("\n 4: Anzeigen: Listet alle Studenten ");
    printf("\n 5: Entfernen eines Studenten oder der ganzen Liste");
    printf("\n 6: Speichern der Datei in die output.txt");
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
        up_zeiger_anzeigen(f);
        break;
    case 8:
        passwort = up_verschluesseln(f);
        break;
    case 9:
        up_entschluesseln(f, passwort);
        break;
    default:
        break;
    }
    return (auswahl);
}

void up_datei_einlesen(t_feld *f)
{

    //DATEI EINLESEN UND DOPPELTE ENTFERNEN
    char text[99 + 1];
    char *zeigertext = text; //in diesem Array wird eine ganze Zeile aus der Datei gespeichert
    FILE *einlesen;
    einlesen = fopen("input.txt", "r"); //Öffnet die Datei zum Lesen "read"
    int fehler = 0;

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
                    up_neues_Listenelement(f, text);

                //Überprüfe ob der einzulesende Wert in der Liste bereits vorkommt(Kriterium ist Email die an stelle (zeigertext + 50 steht)
                fehler = up_suche_doppelte_elemente(f, (zeigertext + 50));
                if (fehler == 0)                     //nur wenn der Wert nicht in den LIsten vorkommt schreibe füge die Zeile den Listen hinzu
                    up_neues_Listenelement(f, text); //Lese nur ein, wenn das erste Zeichen der Zeile ein Buchstaben oder eine Zahlen ist
            }
        }
        fclose(einlesen); //schließe Datei

        printf("\n\nDaten wurden erfolgreich eingelesen\n\n");
        printf("\nWeiter mit Enter Taste ...");
        getchar();
    }
}

void up_eingabe_tastatur(t_feld *f)
{
    //Methode um Benutzer das Anlegen eines Nnuen Benutzers zu ermöglichen:
    //Der eingegebene Benutzer wird anschließend in der Verketteten Liste angefügt

    //Randbedingungen:
    //Eingaben erfolge nach Abfrage :
    // Vorname      maximal 15 Zeichen (alphanumerisch) werden übernommen (erster Buchstaben wird in Großbuchstabe umgewandelt)
    // Nachname     maximal 15 Zeichen (alphanumerisch) werden übernommen  (erster Buchstaben wird in Großbuchstabe umgewandelt)
    // Kursnummer   maximal 7 Zeichen (nur Zahlen) werden übernommen (führende 0)
    // ECTS         maximal 3 stellige Zahl der ECTS-Punkt Anzahl wird übernommen (führende 0)
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

    printf("\nWillkommen zur Eingabe von neuen Studenten\nweiter mit Enter ...\n");
    getchar(); //warte auf ENTER

    do
    {
        //Initiesierung der char Arrays für die Eingaben, muss vor jeder eingabe geschrieben/überschrieben werden
        up_char_init(tmptext, sizeof(tmptext));
        up_char_init(tmpvorname, sizeof(tmptext));
        up_char_init(tmpnachname, sizeof(tmpnachname));
        up_char_init(tmpemail, sizeof(tmpemail));
        up_char_init(tmpkursnummer, sizeof(tmpkursnummer));
        up_char_init(tmpects, sizeof(tmpects));

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

        //Setze die E-Mail anhand des vor und nachnames zusammen dies ist das entscheidene merkmal eines users(primary Key)
        //Überprüfe auch gleich ob diese E-Mail bereits vorhanden ist (liefert Fehler zurück)
        fehler = up_emailfeld(f, zeigervorname, zeigernachname, zeigeremail, sizeof(tmpvorname), sizeof(tmpnachname));

        if (fehler == 0) //mache nur weiter wenn e-mail überprüfung eine 0 liefert wenn es keine doppelt vorkommende email gibt
        {

            // um die eingaben schon in eine Zeile zusammenzufassen gleich,
            // müssen die einzelnen arrays bereinigt werden
            // \n und die terminierende 0 wird entfernt, wenn sie vor dem eigentlichen Ende des Stings kommt:
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
            //daruch kann diese eingabe als Parameter für die up_neues_Listenelement übergeben werden, um sie in die verkette Liste zu speichern
            up_neues_Listenelement(f, tmptext); // der Zeiger vom Hautprogramm und tmptext wird der Methode übergeben, die die Daten in die Liste speichern soll.
            printf("\nFolgender Student wurde erfolgreich eingelegt \n%s\n%s\n%s\n", f->mom->vorname, f->mom->nachname, f->mom->email);
        }

        printf("\n\nWollen Sie weitere Werte eingeben, oder die Eingabe wiederholen, dann Taste: \"j\"\num abzubrechen eine beliebige Taste :\n");
        scanf("%c", &eingabe);
        fflush(stdin);

    } while ((eingabe == 'j')); //uum weitere eingaben zu ermöglichen muss einfach 'j' gedrückt werden
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
    printf("\n '1' fuer die Sortierung des Vornamens");
    printf("\n '2' fuer die Sortierung des Nachnames");
    printf("\n '3' fuer die Sortierung der Kursnummer\n");

    scanf("%i", &auswahl);
    fflush(stdin);

    switch (auswahl)
    {
    case 1:
    {
        printf("\n In welcher Reihenfolge, soll sortiert werden\n\t'1' fuer aufsteigend\n\t'2' fuer absteigend\n");
        do
        {
            scanf("%i", &auswahl);
            fflush(stdin);
        } while (auswahl != 1 && auswahl != 2);

        if (auswahl == 1) ///Vorname ABSTEIGEND###############################################
        {
            f->mom = f->start; //gehe auf den Startzeiger
            // Da die Kursnummer mit führenden 0 (Nullen) gefüllt ist , kann hier die StringCompare Funktion verwendet werde ,
            for (i = 0; i < zaehler - 1; i++) // absteigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->vorname, f->mom->danach->vorname) > 0)
                        up_zeiger_tausch(f); //Wenn die erste Stelle größer ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            f->temp = f->mom; // Wichitg, das letzte Element der Liste wird nun das Temp element,
            //sodass wenn ein neuer Benutzer angelegt wird dieser ans Ende der sortierten Liste kommt

            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        else ///Vorname AUFTEIGEND###############################################
        {
            f->mom = f->start;                //gehe auf den Startzeiger
            for (i = 0; i < zaehler - 1; i++) // austeigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->vorname, f->mom->danach->vorname) < 0)
                        up_zeiger_tausch(f); //Wenn die erste Stelle kleiner ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            f->temp = f->mom; // Wichitg, das letzte Element der Liste wird nun das Temp element,
            //sodass wenn ein neuer Benutzer angelegt wird dieser ans Ende der sortierten Liste kommt

            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        break;
    }
    case 2:
    {
        printf("\n In welcher Reihenfolge, soll sortiert werden\n\t'1' fuer aufsteigend\n\t'2' fuer absteigend\n");
        do
        {
            scanf("%i", &auswahl);
            fflush(stdin);
        } while (auswahl != 1 && auswahl != 2);

        if (auswahl == 1) ///Nachname ABSTEIGEND###############################################
        {
            f->mom = f->start;                //gehe auf den Startzeiger
            for (i = 0; i < zaehler - 1; i++) // absteigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->nachname, f->mom->danach->nachname) > 0)
                        up_zeiger_tausch(f); //Wenn die erste Stelle größer ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }

            f->temp = f->mom; // Wichitg, das letzte Element der Liste wird nun das Temp element,
            //sodass wenn ein neuer Benutzer angelegt wird dieser ans Ende der sortierten Liste kommt

            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }
        else ///Nachname AUFTEIGEND###############################################
        {
            f->mom = f->start;                //gehe auf den Startzeiger
            for (i = 0; i < zaehler - 1; i++) // austeigend
            {
                f->mom = f->start;
                for (j = 0; j < zaehler - 1; j++)
                {
                    if (strcmp(f->mom->nachname, f->mom->danach->nachname) < 0)
                        up_zeiger_tausch(f); //Wenn die erste Stelle kleiner ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            f->temp = f->mom; // Wichitg, das letzte Element der Liste wird nun das Temp element,
            //sodass wenn ein neuer Benutzer angelegt wird dieser ans Ende der sortierten Liste kommt

            printf("\n Es wurde erfolgreich sortiert, schaue im Hauptprogramm unter Punkt 4 die Ausgabe an.");
            printf("\n\nWeiter mit Enter Taste ...");
            getchar();
        }

        break;
    }

    case 3:
    {
        printf("\n In welcher Reihenfolge, soll sortiert werden\n\t'1' fuer aufsteigend\n\t'2' fuer absteigend\n");
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
                        up_zeiger_tausch(f); //Wenn die erste Stelle größer ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach;
                }
            }
            f->temp = f->mom; // Wichitg, das letzte Element der Liste wird nun das Temp element,
            //sodass wenn ein neuer Benutzer angelegt wird dieser ans Ende der sortierten Liste kommt

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
                        up_zeiger_tausch(f); //Wenn die erste Stelle kleiner ist als die zweite, sollen sie vertauscht werden
                    f->mom = f->mom->danach; //Nächstes Element
                }
            }
            f->temp = f->mom; // Wichitg, das letzte Element der Liste wird nun das Temp element,
            //sodass wenn ein neuer Benutzer angelegt wird dieser ans Ende der sortierten Liste kommt

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

void up_anzeige_daten(t_feld *f)
{
    int zaehler = 0;
    f->mom = f->start; //Starte beim ersten Listenelement
    printf("\n  Vorname             Nachname             Kurs       E-Mail                                       ECTS    Index");
    printf("\n________________________________________________________________________________________________________________");
    while (f->mom) // gehe solange die liste durch bis du das ende = 0 erreichst
    {
        //Gibt aktuellen Listenelemente formatiert aus
        printf("\n|%-18s|%-18s|%-10s|%-24s|%s|", f->mom->vorname, f->mom->nachname, f->mom->kursnummer, f->mom->email, f->mom->ects);
        f->mom = f->mom->danach; //setzte den Zeiger auf den nachfolger, auf das nächste Listenelement
        if (zaehler != 25)       //Überprüfe ob bereits 25 Zeilen ausgegeben wurden
            zaehler++;           //Zähle die ausgebenen Listen aus
        else
        { //Es wurden 25 Zeichen eingelesen
            printf("\n\nEs wurden die 25 Zeilen ausgegeben\num weitere 25 Zeilen auszugeben bitte mit Enter weiter");
            printf("\nWeiter mit Enter Taste ...");
            getchar();
            zaehler = 0; //Setzte Zähler zurück
        }
    }
    printf("\n\nWeiter mit Enter Taste ...");
    getchar();
}

void up_entferne_datensatz(t_feld *f)
{
    int auswahl;
    printf("\n Was willstdu entfernen");
    printf("\n '1' Fure die leerung aller Listenelemente");
    printf("\n '2' fuer die Entfernung einzelner Bentutzer\n");

    scanf("%i", &auswahl);
    fflush(stdin);

    switch (auswahl)
    {
    case 1: //ALLE LISTENELENTE WERDEN GELÖSCHT
    {
        f->mom = f->start;
        while (f->mom)
        {
            free(f->mom->davor);     //Leert den Speicher des Listenelementes starte bei dem hinter dir,
            f->mom = f->mom->danach; // Wenn du das aktuelle löschen würdest dann kannst du nicht mehr die Liste durchgehen
        }
        free(f->mom);
        f->mom = 0;
        f->start = 0;
        f->temp = 0;
        printf("\n Liste und Arbeitsspeicher wurde geleert\n Weiter mit Enter");
        getchar();
        break;
    }

    case 2:
    {
        ///////
        //gebe E-Mail ein
        //suche nach e-mail
        ///vom vorgänger Zeiger muss der nachfolger auf den übernächsten gesetzt werden
        //vom nachfolger Zeiger muss der voränger auf den von vorletzten Zeiger
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
            up_bereinige(eingabe, sizeof(eingabe)); //wandel die eingebene E-Mail in ein format um wie sie in der Liste stehen könnte

            f->mom = f->start; //gehe auf den Startzeiger

            while (f->mom) // DU STARTET AM LETZEN ELEMENT GERADE gehe solange die liste durch bis du das ende = 0 erreichst
            {
                if ((strcmp(eingabe, f->mom->email))) //String compare liefert 0 wenn die Strings gleich sind
                {
                }
                else
                { //Strucelement das gelöscht werden soll wurde gefunden
                    //es gibt 3 möglichkeiten: Das ersten, letzte, oder mittendrinn soll gelöscht werden

                    f->mom->email[0] = '0'; //leert das E-Mail feld, damit die E-Mail nicht mehr in einer Liste steht
                    if (f->mom->davor == 0) //Erstes element wurde getroffen
                    {

                        f->mom->danach->davor = 0; // im vorherigen element wird der danach zeiger auf 0 gesetzt
                        f->start = f->mom->danach; //neues Startelement wird gesetzt
                        printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                        geloescht = 1;
                        free(f->mom);
                        break;
                    }
                    if (f->mom->danach == 0) // Letzes Element wurde getroffen
                    {

                        f->mom->davor->danach = 0;
                        f->temp = f->mom->davor; //<-- Wichtig das vorletzte Element wird nun das zwischen element.
                        //damit beim löschen des Letzten elements immer noch welche hinzugefügt werden können, durch up_neues_Listenelement
                        printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                        geloescht = 1; // im vorherigen element wird der danach zeiger auf 0 gesetzt
                        free(f->mom);
                        break;
                    }

                    else // Element mittendrinne wurde getroffen
                    {

                        f->mom->davor->danach = f->mom->danach; //Setze den Nachfolger des Vorgängers auf den übernächsten Zeiger
                        f->mom->danach->davor = f->mom->davor;  //Setze den Vorgänger der Nachfolgers auf den vorherigen Zeiger ein Element dahinter
                        printf("\n\tFolgender Nutzer wurde entfernt %s", eingabe);
                        geloescht = 1;
                        free(f->mom);
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

void up_speichern(t_feld *f)
{
    //Mehode um Inhalte der Struckturierten Liste in ein output.txt File zu schreiben. output.txt muss vorhanden sein
    FILE *einlesen;
    einlesen = fopen("output.txt", "w+"); //öffnen und erstelltmit parameter w "leert" die Datei. Öffnen und leert die datei

    if (!einlesen)
        printf("\n Datei nicht moeglich zu oeffnen");
    else
    {
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
}

void up_zeiger_anzeigen(t_feld *f)
{
    f->mom = f->start; //gehe zum ersten Listenelement
    while (f->mom)     //wiederhole solange das Ende nicht ereicht wurde
    {                  //gebe die Zeiger des aktuellen Listenelements aus
        printf("\n %-10s mom Zeiger: %10X   mom DAVOR : %10X  mom DANACH : %10X", f->mom->email, f->mom, f->mom->davor, f->mom->danach);
        f->mom = f->mom->danach; //gehe zum nächsten Element
    }
    printf("\nWeiter mit Enter Taste ...");
    getchar();
}

int up_verschluesseln(t_feld *f)
{

    //E-Mail prefix wird verschlüsselt, durch eingabe eines Passwortes
    char eingabe_key[10] = {0};
    const MOD = 60;
    int passwort; //Das eingegebene Passwort in eine Ganzzahl gespeichert
    int i, key = 0;
    f->mom = f->start;
    printf("Code zum Verschluesseln eingeben\n");
    scanf("%s", &eingabe_key); //Passwort kann alle zeichen enthalten
    fflush(stdin);

    for (i = 0; i < 10; i++) //wandelt das eingebene Passwort in eine Ganzzahl, in dem die ASCIIwerte der einzelnen Ziffern zusammengezählt werden
        passwort = passwort + eingabe_key[i];

    //Algorithumus
    //Cäsar Verfahren addiere auf den char ASCII-Wert eine geheime Zahl drauf, dann wird es ein anderes Zeichen.
    //Wir brauchen nur einen Wert (key), den wir auf den Ascii Code der jeweiligen Zeichen addieren
    key = passwort % MOD + 65; // 65 weil, verschlüsseltes Zeichen, soll kein @ enthalten, daher fangen wir beim ascii code ab stelle 65 an

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

    return passwort; //das Passwort im Klartext wird returnt
}

void up_entschluesseln(t_feld *f, int passwort)
{
    //Methode um zu Entschlüsseln enthält als Übergabeparameter das Passwort, dass bei der Methode up_verschluesseln verwendet wurde
    const MOD = 60; // Für die berechnung des wertes das auf den klartext addiert wird

    int key;
    int i, input_passwort = 0;
    char eingabe_key[10] = {0};

    printf("Code zum Entschluesseln eingeben\n");
    scanf("%s", &eingabe_key);
    fflush(stdin);

    for (i = 0; i < 10; i++) //wandelt das eingebene Passwort in eine Ganzzahl, in dem die ASCIIwerte der einzellnen Ziffern zusammengezählt werden
        input_passwort = input_passwort + eingabe_key[i];

    f->mom = f->start;              //setzte start
    if (passwort == input_passwort) //Nur wenn das eingebene Passwort den richtigen Passwort (das der Methode übergeben) entspricht, dann wird entschlüsselt
    {
        key = passwort % MOD + 65;
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
    {
        printf("Der Code war falsch");
        printf("\n\nWeiter mit Enter Taste ...");
        getchar();
    }
}


