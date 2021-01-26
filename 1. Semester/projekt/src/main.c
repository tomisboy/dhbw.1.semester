#include "header.h"
//Thomas Alpert
//Ein Programm zur Verwaltung und Pflege von Studenten Daten
//mit Ihren Vor und Nachnamen ihrer Kursnummer einer E-Mail und deren ECTS Punkte
//durch das Zeilenweise einlesen einer input.txt werden die darin enthaltendnen Informationen entsprechend aufgeteilt
//und an ihre entsprechene Stelle in einer verketteten Liste gespeichert.
//Es werden nur Zeilen eingelesen die Mit einem Großbuchstaben beginnen

//Aufbau der input.txt:
//  Vorraussetzung dieses Programmablaufes ist dass die input.txt fehlerfrei ist  (Sowohl für die Strucktur als auch für die Werte an sich)
//  an Stelle des Vornames  stehen max 15 Zeichen nur Buchstaben angefangen mit einem Großbuchstaben) Es folgen 5 Leerzeichen
//  an Stelle des Nachnames stehen max 15 Zeichen nur Buchstaben angefangen mit einem Großbuchstaben) Es folgen 5 Leerzeichen
//  an Stelle der Kursnummer steht eine 7 stellige Zahl (mit 0 gefüllt, wenn die Zahl kleiner ist)    Es folgen 3 Leerzeiche
//  an Stelle des E-Mail stehen max 45 Zeichen, zusammengesetzt aus dem vornamen.nachnamen mit der Zusaz "@uni.de" Es folgen 5 Leerzeichen
//  an Stelle der ECTS-Punkte steht eine 3 stellige Zahl (mit 0 gefüllt, wenn die Zahl kleiner ist)   Es folgt ein Zeilenumbruch

//BEISPIEL input.txt
// [15           ][5  ][15           ][ 5 ][7    ][3][45                                     [5  ][3][\n]
// [VORNAME]           [NACHNAME]          [KURS ]   [E-MAIL]                                      [ECTS]   
// Markus              Singer              1100000   Markus.Singer@uni.de                          050

// input.txt und output.txt müssen sowohl vorhanden in dem selben pfad liegen in dem die main.exe läuft

//Folgende mindestanforderungungs Funktionen sind gegeben:
//  1.  Einlesen einer Datei und Schreiben der Inhalte in eine Verkette Liste
//          Es werden auschließlich Zeilen eingelesen die mit einem Großbuchstaben beginnen
//              Überprüung auf doppelte einträge
//              Es werden nur Zeilen verarbeitet wenn der Inhalt dieser Zeile noch nicht in einem Listelemet vorhanden ist  

//  2.  Manuelles eingeben von Daten 
//          Der Benutzer kann neue Studeneten anlegen a
//          Der Benutzer gibt den Vornamen, Nachnamem, Kursnummer und ECTS Punkte ein alle Eingaben werden auf Fehler überprüft!
//          Die E-Mail wird automatisch erstellt
//          Es wird überprüft ob dieser Student (E-Mail bereit schonmal eingelesen wurde) 
//                      Wenn ja gibt es einen Fehler und der Benutzer wird nicht eingelsen

//  3.  Sortieren (mittels Bubble Sort)
//          Die Sortierung verschiebung der Listenelement wurde durch eine Zeiger "umbiegung" gelöst
//          Der Benutzer kann die Liste nach
//              Vornamen 
//              Nachname
//              Kursnummer 
//              jeweills auf oder absteigend sortieren 
//
//  4.  Anzeigen der Daten
//          Der Benutzer kann sich den Inhalt der Listenelemete (formatiert wie die input.txt) anzeigen lassen
//
//  5.  Entfernen eines Datensatzes
//          Der Benutzer kann alle Listenelemente zurücksetzten
//          Der Benutzer kann einzellne Studenen anhand ihrers eindeutiges Unterscheidungsmerkmals (die E-Mail) löschen lassen
//
//  6.  Speichern der Datei
//          Der Inhalt aller LIstenelemente wird formiert in eine output.txt geschrieben
//
//  7.  Anzeigen der Zeiger
//          Listet alle Zeiger der Listenelemte auf.
//
//  8.  Verschluesseln
//          Der Benutzer kann die E-Mail aller Studenten durch die eingabe verschlüsseln
//              Es wird nur der E-Mail präfix verschlüsselt (alles vor dem @ Zeichen),,
//
//  9.  Entschluesseln
//          Der Benutzer kann durch die Eingaben des richtigen Schlüssles alle E-Mails wieder entschlüsseln

int main(void)
{
    int auswahl = 1;
    t_feld feld;       // erstell ein "Objekt" feld vom TYP des Structurelements
    t_feld *f = &feld; //erstelle den Zeiger *f

    //Setze StartParameter der Zeiger
    f->mom = 0; //Setze StartParameter der Zeiger
    f->start = 0;
    f->temp = 0;

    printf("Willkommen zur Studentenverwaltung\n\n");
    while (auswahl != 0)
        auswahl = up_menu(f); //wiederhole solange den aufruf des Menus, bis die 0 Ausgewählt wird, diese Beendet das Programm
    return (42);
}