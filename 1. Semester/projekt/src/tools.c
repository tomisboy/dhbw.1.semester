//Thomas Alpert
#include "header.h"


void up_neues_Listenelement(t_feld *f, char text[99 + 1])
{

    f->mom = (t_studenten *)malloc(sizeof(t_studenten)); // Reserviert Hauptspeicher von der Größe des Struct-elements t_studenten für nächstes Listenelement

    if (f->mom == 0) //es konnte kein Speicher reserviert werden
        printf("Achtung es konnte, kein Speicher reserviert werden, Element wurde nicht gespeichert!!");
    else
    {
        up_text_zu_Liste(f, text); //( inhalt wird in listelemet übertragen)

        //Hier werden die Zeiger listen verknüpfungen erstellt

        f->mom->davor = f->temp;      //Von aktelle neu erzeugtem mom element das Feld davor ist temp, was der vorgänger ist ----
        f->mom->danach = 0;           //Von aktelle neu erzeugtem mom element das Feld danach wird 0 gesetzt.                   |
        if (f->temp == 0)             //erster Fall temp ist noch von der Initi auf 0                                           |
            f->start = f->mom;        //erstes Element der Liste wird festgelegt                                                |
        else                          //                                                                                        |
            f->temp->danach = f->mom; //vom Vorgänger, das Zeigerelement "danach" wird der akutell neu erzeugt mom Zeiger       |
        f->temp = f->mom;             //temp Zeiger wird der aktuelle neu erzeugte mom zeiger       <----------------------------
    }
}
void up_text_zu_Liste(t_feld *f, char text[99 + 1])
{
    //In dieser Methode wird der eingelesene Text aufgeteil in die Listenelemente:
    //vorname, nachname, kursnummer, email, ects gespeichert

    //Der eingelesene Text ist eine ganze Zeile und wird der Methode als char text[99 + 1] mitgegeben.

    strncpy(f->mom->vorname, text, 20); //kopiert den Vornamen, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (vorname)
    f->mom->vorname[20] = '\0';

    strncpy(f->mom->nachname, text + 20, 20); //kopiert den Nachnamen, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (nachname)
    f->mom->nachname[20] = '\0';

    strncpy(f->mom->kursnummer, text + 40, 10); //kopiert die Kursnummer, von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (kurnummer)
    f->mom->kursnummer[10] = '\0';

    strncpy(f->mom->email, text + 50, 45); //kopiert die E-Mail , von der korrekten stelle des übergebenen Textes, in die aktuelle Liste an die passende Stelle (email)
    f->mom->email[45] = '\0';

    strncpy(f->mom->ects, text + 95, 5);
    f->mom->ects[5] = '\0'; //Speichert die, an der Stelle 95 stehenden 5 Zeichenelemente ,die die ECTSPunkte abbilden in die aktuelle Liste an die passende Stelle (ects)
}

void up_bereinige(char *bekommenerZeiger, int langeArray)
{
    // Methode zur Bereinigung von char[] entferne von \n und/oder einer vorzeitigen terminierenden \0
    // überprüft ob innerhalb einer char[] bis zur vorletzten stelle ein \n oder eine \0 steht
    // Wenn ja dann wir dieses Zeichen und folgende (bis zur vorletzen stelle) durch ein " " (Leerzeichen) ersetzt
    // Text verarbeitung dadurch einfacher vereinfacht
    int i;
    for (i = 0; i < langeArray - 1; i++)                               //überprüfe bis zur vorletzen element ob eine termierende 0 oder \n vorkommt
        if ((bekommenerZeiger[i] == 10) || (bekommenerZeiger[i] == 0)) // Wenn ein \n oder \0 auftaucht, wir diesesdurch ein Leerezeichen ersetzt
            bekommenerZeiger[i] = 32;
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
        if (bekommenerZeiger[i] >= '0' && bekommenerZeiger[i] <= '9') //Überprüft die einzelnen Zeichen ob sie Zahlen sind
        {
        }
        else
        {
            if (bekommenerZeiger[i] == '\n') //Sobald ein \n gefunden wurde bedeutet dies, das Char Array ist nicht vollständig gefüllt!
            {
                fehler = 1; // Fehler weil char array nicht die notwendige Anzahl der Stellen erfüllt
                printf("\nEingaben enthielt zu wenig Stellen\n ");
                printf("Sie muessen %d Stellen angeben (Wenn Eingabe kleiner als %d Stellen ist, geben sie 0 an den Anfang\n", langeArray - 1, langeArray - 1);
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
    //Es gibt bisher im Programm 2 Möglichkeiten, wie die char[] (vorname und nachname) gefüllt werden können:

    //1 Fall:
    //das Char Array wurde vollständig gefüllt bis an stelle 15 -->
    //[0]'t'
    //[1]'h'
    //[...]'x'
    //[13]'e'
    //[14]'\0' <-- Terminierende 0 an der letzten (richtigen) Stelle
    //[15]' '<-- hier kommen noch die 5 Leerzeichen, als Trennungszeichen für die ausgaben später
    //[...]' '
    //[19]'\0'

    //2. Fall:
    //wenn aber die Eingabe der Zeichen kleiner als 15 war, kommt an die letzte stelle ein '\n' das Enter
    //tmpvorname könnte folgerdermaßen aussehen, wenn die eingabe unter 10 Zeichen ist
    //[0]'t'
    //[1]'h'
    //[2]'\n'  <-- Vorzeitiges Ende wird mit \n gekennzeichnet
    //[3]'\0' <-- Terminierende 0 an der falschen (vorzeitige) Stelle
    //[4]' ' <-- hier kommen noch die 5 Leerzeichen, als Trennungszeichen für die ausgaben später
    //[...]' '
    //[19]'\0'

    //Trittfall 2 auf,  muss beim Kopieren nur zu der Stelle geschehen, bis das '\n' kommt

    char mailzusatz[7 + 1] = {'@', 'u', 'n', 'i', '.', 'd', 'e'};
    int i, j, fehler = 0;

    for (i = 0; i < (laengevorname - 5 - 1); i++) // gehe bis index 14 des vornamens. Eins vor der Terminierenden null, bis hierhin könnte Text stehen
    {
        //Kopiere jedes Zeichen vom Vonamen in das E-Mail Feld solange bis man eben entwerder ein vorzeitiges Ende (FALL 2) (\n) gefunden hat,
        //oder man an der Vorletzten stelle ist (FALL 1)
        if (zeigervorname[i] != 10)            // 10 ist \n .
            zeigeremail[i] = zeigervorname[i]; //Kopiere nun die Zeichen des Vornamens in die E-Mail
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
    for (j = 0; j < 7; j++) //hänge zeichenweise mit einer for schleife die E-Mail domaine an
    {
        zeigeremail[i + 1] = mailzusatz[j];
        i++; //es muss auch der index von Zeigermail hochgezählt werden
    }

    zeigeremail[45] = '\0'; //terminierende 0 setzen

    f->mom = f->start; //gehe auf den Startzeiger

    // Es wird überprüft, ob die E-Mail bereits in der der Liste vorkommt
    fehler = up_suche_doppelte_elemente(f, zeigeremail);

    if (fehler == 1)
        printf("\n\n\tAchtung E-Mail ist bereits vorhanden\n\n\tDieser Benutzer kann nicht angelegt werden !");

    return fehler;
}
void up_zeiger_tausch(t_feld *f)
{
    int zeigerspeichen;
    //zeigerspeichen = f->mom; // merke dir die aktuelle position vor der vertauschung
    int temp;

    //Hier passiert die Magie des Vertauschen 2er aufeinanderfolgenden Elemente einer Liste:
    // Es müssen 6 Zeiger umgebogen werden
    //Dabei gibt es 2 Fälle zum Beachten dass entweder das erste oder das Letzte element getauscht wird

    //IST Situation:

    //####################################################################################################################
    //              [6]                                           [1]                                      [3]          //
    //      <---------------------  [ELEMENT  X     ]        <-----------    [ELEMENT  Y           ] <----------------  //
    //                              [ x = f->mom    ]	                     [ y = f->mom->danach  ]                    //
    //       ---------------------> [ELEMENT  X     ]        ----------->    [ELEMENT  Y           ] ---------------->  //
    //              [5]                                         [2]                                        [4]          //
    //####################################################################################################################

    //SOLL  Situation:
    //####################################################################################################################
    //              [6]                                        [1]                                  [3]                 //
    //      <---------------------  [ELEMENT Y          ]   <-----------    [ELEMENT x     ] <----------------          //
    //                              [ y = f->mom->danach]	                [ x = f->mom   ]                            //
    //      --------------------->  [ELEMENT  Y         ]   ----------->    [ELEMENT x     ] ---------------->          //
    //              [5]                                        [2]                                  [4]                 //
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
    // f->mom = zeigerspeichen;
    f->mom = f->mom->davor; //setzte aktuellen Zeiger um eine stelle zurück
}
void up_char_init(char *array, int lange)
{
    //Fülle Char arrays mit Leerzeichen
    int i;
    for (i = 0; i < lange; i++)
        array[i] = 32;
}
int up_suche_doppelte_elemente(t_feld *f, char *zeigertext)
{
    //Methode überprüft, ob die Inhalte der neu eingelesenen Zeile bereits in einer der Listenelementen vorkommt.
    //Als entscheidendes Kriterium,(und Übergabeparamter) wird die E-Mail benutze, da diese einmalig ist und nicht doppelt vorkommen darf/kann.

    int fehler = 0;
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