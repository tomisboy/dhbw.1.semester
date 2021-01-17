#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)



struct
{
    char name[20 + 1];
    int prn;
} dhler;

typedef struct m_dhler
{
    char name[20 + 1];
    int prn;
    struct m_dhler *davor;
    struct m_dhler *danach;
} t_dhler;

t_dhler *start = 0;
t_dhler *mom = 0;
t_dhler *zwischen = 0;


void up_listeAdd(void);
void up_struct_liste(void);
void up_hex(void);

int main(void)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        printf("\n Gib %d.Namen ein :) ", i + 1);
        scanf("%s", &dhler.name);
        fflush(stdin);
        up_listeAdd();
    }

    up_hex();

    return (42);
}

void up_listeAdd(void)
{
    mom = (t_dhler *)malloc(sizeof(t_dhler)); // holt hauptspeciher
    up_struct_liste();                        //( inhalt wird in listelemet übertragen)

    mom->davor = zwischen;
    mom->danach = 0;
    if (zwischen == 0) // (!zwischen)
    {
        start = mom;
    }
    else
    {
        zwischen->danach = mom;
    }
    zwischen = mom;
}

void up_struct_liste(void) // kopiert inhalt globaler vairable in Listelement
{
    strcpy(mom->name, dhler.name);
    //.. alle weiteren werden übertragen
}

void up_hex(void)
{
    mom = start;
    while (mom)
    {
        printf("\n %-10s momentan Zeigen: %10X   \n momentan DAVOR : %10X \n momentan DANCH : %10X", mom->name, mom, mom->davor, mom->danach);

            mom = mom->danach;
    }
}