#include "header.h"

int main(void)
{
    int ausgwaehlt = 1;
    t_feld feld;
    t_feld *f = &feld;

    f->mom = 0;
    f->start = 0;
    f->temp = 0;

    printf("Willkommen zur Studentenverwaltung\n\n");
// do while ?
    while (ausgwaehlt != 0)
    {
        ausgwaehlt = up_menu(f); //wiederhole solange den aufruf des Menus, bis die 0 Ausgewählt wird, diese Beendet das Programm
    }
    return (42);
}
//Einlesen funktioniert
//Eingabe mit fehlerüberpüfung mich gemacht werden