#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)


int main(void) {

char t1[80+1], t2[80+1],t3[80+1] ,t4[80+1];


int l, rc;

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
printf(" \n---%s---", t1);





rc = strcmp(t1,t1);
printf ("\n rc=%d %s %s",rc,t1,t1);


strcpy(t1, "Hannes");
strcpy(t2, "HaNnes");
strcpy(t3, "Hannes ist schlau");
strcpy(t4, "Hannes ist faul");

rc = strcmp(t1,t1);
printf ("\n rc=%d %s %s",rc,t1,t1);

rc = strcmp(t1,t2);
printf ("\n rc=%d %s %s",rc,t1,t2);

rc = strcmp(t1,t3);
printf ("\n rc=%d %s %s",rc,t1,t3);

rc = strncmp(t1,t2,2); // schauen nur nach den ersten 2 Zeichen
printf ("\n TEST rc=%d %s %s",rc,t1,t2);

rc = strncmp(t3+7, t4+7,4);
printf ("\n TEST1 rc=%d %s %s",rc,t3,t4);



char *t3x, *t4x; //Zeiger

t3x = strstr(t3, "ist"); //Es wird die Zeigeradresse gespeichert
printf("\n %X", t3x);

t4x = strstr(t4, "ist");
printf("\n %X", t4x);


rc = strncmp(t3x,t4x,16);
printf ("\n 1hmmrc= %d ---%s--- ---%s---",rc,t3x,t4x);
return(42);
}