#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {



float grundflaeche;
float radius = 50;
grundflaeche = 3.1415*radius*radius;

 
printf("%f Grundflaeche = ", grundflaeche);
float volumen = 0;
for (float i = 0; i < 200; i= i +10 )
{
    volumen = ((grundflaeche *i/1));
    printf("\n Das Volumen Betraegt: %f",volumen );
}





printf("\n Fast alle sind flei  %c   ig",0xe1);
//printf("\n text=---%s---", text);




return(1);
}

