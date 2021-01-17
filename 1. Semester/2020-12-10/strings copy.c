#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)


int main(void) {

int i;
char text[200]; //reserviert aber nicht initiaisiert


for ( i = 0; i < 200; i++)
{
    printf(" '%c'", text[i]);
}

return(42);
}