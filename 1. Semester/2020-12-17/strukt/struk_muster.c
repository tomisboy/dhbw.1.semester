#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    // Struktur-Muster
    //Vorlage

    struct studentenvorlage
    {
        char name[20 + 1];
        char vorname[20 * 1];
        int pnr;
        float gehalt;
        int farbe[3];
    };

    //von muster student lege hannes, inf .. und den zeiger an
    struct studentenvorlage hannes, tinf20b[29], *zs;

    hannes.pnr = 123;
    hannes.gehalt = 7.85;
    strcpy(hannes.name, "Hannes");

    tinf20b[0].pnr = 123;
    tinf20b[0].gehalt = 7.85;
    strcpy(tinf20b[0].name, "Hannes");

    return (42);
}