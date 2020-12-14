#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)


int main(void) 
{
 int i , l , summe , prueziffer; 
 char ersterTeil[3+1] = {0};
 char zweiterTeil[3+1] = {0};
 char bezeichnung[9+1] = {0};
 int berechnung[6+1] = {0};

 printf("Bitte Bezeichnung im Format xxx-xxx eingeben: \n");
 scanf("%s", bezeichnung);

//Überprunfung noch machen;


//schreibe die ersten 3 Chars in den Array erterTeil
for ( i = 0; i < 3; i++)
{
ersterTeil[i] = bezeichnung[i];
// debug printf("\n ersten 3 Zeichen: %c ", ersterTeil[i]);
}
//schreibe den zweiten block in den "ZweiterTeil Array" 
for ( i = 0; i < 3; i++)
{
zweiterTeil[i] = bezeichnung[i+4];
// DEBUG printf("\n ersten 3 Zeichen: %c ", zweiterTeil[i]);
}

//berechnung
//Alle ungeraden stelle können nicht größer als 10 werden da *1 
//also können alle ungeraden stellen schonmal einfach so geschrieben werden 

 berechnung[0] = (ersterTeil[0] -48) *1 ; //1.Ziffer
 berechnung[2] = (ersterTeil[2] -48) *1 ; //3.Ziffer
 berechnung[4] = (zweiterTeil[1] -48) *1 ; //5. Ziffer 

if ((ersterTeil[1] -48)*2 >=10)
    berechnung[1] = ((ersterTeil[1] -48)*2)%10 +1; // 2. Ziffer
else
  berechnung[1]  =(ersterTeil[1] -48) *2 ; // 2.Ziffer

if ((zweiterTeil[0] -48)*2 >=10)
    berechnung[3] = ((zweiterTeil[0] -48)*2)%10 +1; // 4. Ziffer 
else
  berechnung[3]  =(zweiterTeil[0] -48) *2 ; // 4. Ziffer 

if ((zweiterTeil[2] -48)*2 >=10)
    berechnung[5] = ((zweiterTeil[2] -48)*2)%10 +1; // 6. Ziffer 
else
  berechnung[5]  =(zweiterTeil[2]-48) *2 ; // 6. Ziffer 





summe= 0 ;
for ( i = 0; i < 6; i++)
{
   summe = summe + berechnung[i];
}
//Berechungn der Prüfsummer
prueziffer = 10- summe % 10;


//hänge Prüfsumme an der char Array
bezeichnung[7]= '-';
bezeichnung[8] = prueziffer+48;



printf("Die Wagenbezichnung lautet\n");


for ( i = 0; i <=9; i++)
{
   printf("%c", bezeichnung[i]);
}










return(42);
}