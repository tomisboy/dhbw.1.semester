#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.14159
// ersetze PI durch 3.1415
#define NIX void
#define MEINMACRO a*b/c

typedef struct 
{
///....
}meinEigenerDatentyp;


int main() {

  printf("%f \n ", PI);
char        c1;
signed char c2;
unsigned    c3;


c1 = 'A';  //0100 0001
c1 = 65;
c1 = 0x41;

printf("%c",c1);
printf("%c",c3);


int i1 = 123;
unsigned int i2 =0xffffffff;
int i3 = 'A';
printf("\n");

printf("%i\n",i1);
printf("%u\n",i2);
printf("%i\n",i3);





  return(42);
}
