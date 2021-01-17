#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(void) {

int a = 'a'; //0000 0110 0001
    a = 97; 
printf(" %i\n", a);
a = a << 2; // 0001 1000 0100 = 388 = 97*4
printf(" %i\n", a);
a = a >> 4; // 
printf(" %i\n", a);
return(42); // 0000 0001 1000 = 388/16
}