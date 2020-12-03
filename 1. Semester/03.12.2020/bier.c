#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

<<<<<<< HEAD

int main(void) {
=======
int main() {
>>>>>>> 392aa0679f768e95a8d491701d1b50176b284a0a

float grundflaeche;
float radius = 50;
grundflaeche = 3.1415*radius*radius;


printf("%f Grundflaeche = ", grundflaeche);
float volumen = 0;
for (float i = 0; i < 200; i= i +10 )
{
    volumen = ((grundflaeche *i*0.0000001));
    printf("\n Das Volumen Betraegt: %f",volumen );
}





<<<<<<< HEAD
printf("\n Fast alle sind flei  %c   ig",0xe1);
=======
//noch testen
printf("\n Fast alle sind flei %c ig",0xe1);
>>>>>>> 392aa0679f768e95a8d491701d1b50176b284a0a
//printf("\n text=---%s---", text);




return(1);
}

