#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{

    char name[2][80 + 1]; //Array mit 2 Felder erstellen für 2 Spieler
    int input, high = 10000, low = 0, counter, randomseed, randomnumber, i;
    int checker = 0; //checker Variable Welcher spieler drann ist.
    printf("Bitte Name des 1. Spielers eingeben: ");
    scanf("%s", name[0]);
    fflush(stdin);
    printf("Bitte Name des 2. Spielers eingeben: ");
    scanf("%s", name[1]);
    fflush(stdin);

    //START HIER
    printf("%s oder %s, bitte gebt einen Zufalls Seed ein: ", name[0], name[1]);
    scanf("%d", &randomseed);
    fflush(stdin);

    srand(randomseed);             //INIT SEED FÜR RAND
    randomnumber = rand() % 10000; // Zahl ist zwischen 0 und 999

    //DEBUG
    /*
for( i = 0 ; i < 10 ; i++ ) {
      printf("%d\n",  rand() % 10000);
   }
*/

    do
    {
        //abwechselnd a und b
        if (checker == 0)
        {
            printf("%s Bitte gebe eine Zahl zwische %i und %i ein ", name[0], low, high);
            checker = 1;
        }
        else
        {
            printf("%s Bitte gebe eine Zahl zwische %i und %i ein ", name[1], low, high);
            checker = 0;
        }

        scanf("%d", &input);
        fflush(stdin);
        if (input <= low)
        {
            //wiederholen checker wird zurückgesetzt, sodass wieder die Person drann ist die drann war.
            if (checker == 1 )
                checker = 0; 
            else
            checker =1;
            
            printf("\nDeine Zahl liegt unterhalb des Bereiches. Gib bitte eine Zahl ein, die gr%c%cer als %i ist \n", 0x94 , 0xe1,low);
        }
        else if (input >= high)
        {
           printf("\nDeine Zahl liegt %cberhalb des Bereiches. Gib bitte eine Zahl ein, die kleiner als %i ist \n",0x81 ,high);
            //wiederholen checker wird zurückgesetzt, sodass wieder die Person drann ist die drann war.
            if (checker == 1 )
                checker = 0; 
            else
            checker =1;
            
        } 
        // hier ist man im richtigen Bereich nun
        else if (input < randomnumber) // zahl unter der zufalls nummer = grenze wird von untern an gehoben 
        {
            low = input;
            counter++;
        }
        else
        { // zahl größer als die randomnumber = grenze wird von ober nach herunter gestuft 
            high = input;
            counter++;
        }
        
    } while (input != randomnumber);
    printf("\n richtig :) \n die Zahl war: %d ", randomnumber);

    //Überprüfen wer letzter Player dran war
    if (checker == 1)
    {
        printf("\n %s hat mit %d Zügen gewonnen  ", name[0], counter);
    }
    else
        printf("\n %s hat mit %d Zügen gewonnen  ", name[1], counter);
    return (42);
}