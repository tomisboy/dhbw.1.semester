#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable:4996)


int main(void) 
{
union intParts 
{
    float f;
    char c[4];
}zahl;

zahl.f = 88.125;

return(42);
}