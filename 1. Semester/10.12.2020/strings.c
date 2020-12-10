#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)


int main(void) {

char t1[80+1], t2[80+1],t3[80+1] ,t4[80+1];


int l;

strcpy(t1,"Hannes");
strcpy(t2,t1);


strcat(t1," ist schlau");
printf("\n ---%s---", t1);



strncpy(t3,t1,6); //kopiere die ersten  6 Zeichen von t1 nach t3
t3[6] = 0;
printf("\n ---%s---", t3);

strncpy(t3,t1+7,3);
t3[3] = 0; // letztes null machen damit der "string" zuende ist (definiert das ennde eines Strings)
printf("\n ---%s---", t3);

printf("\n t4---%s---", t4);


l = strlen(t1);
printf("\n laenge = %d", l);


strrev(t1);
printf("\ \n---%s---", t1);


return(42);
}