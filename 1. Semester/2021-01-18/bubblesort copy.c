#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ANZAHL 20

void up_init(int *f);
void up_ausgabe(int *f);
void up_bubble(int *f);

int main() {


    int array[ANZAHL];
    int *f = array;
    srand(time(NULL));


    printf("BUBBLE-SORT\n\n");

    up_init(f);             //init up für array

    up_ausgabe(f);          //bevor sortierung
    up_bubble(f);           //sortierUP
    up_ausgabe(f);          //nach sortierung

    return 0;
}

void up_init(int *f){

    int i;

    for (i = 0; i < ANZAHL ; i++) {
        f[i] = rand() %100 +1;
    }

}

void up_ausgabe(int *f){

    int i;

    printf("\nZahlen im Array:\n");

    for (i = 0; i < ANZAHL ; i++) {
        printf("%d\n", f[i]);
    }

}

void up_bubble(int *f){

    int i,j, tmp;

    for (i = 0; i < ANZAHL-1 ; i++) {
        for (j = 0; j < ANZAHL-1 ; j++) {
            if (f[j] > f[j+1]){
                tmp = f[j];
                f[j] = f[j+1];
                f[j+1] = tmp;
            }
        }
    }

}