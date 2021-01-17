#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    int a;
    int b;
    int c; 
    int temp;

    for (a = 3; a < 100; a++)
    {
        for (b = 1; b < 100; b++)
        {
            for (c = 1; c < 100; c++)
            {
                temp = pow(a,2) + pow(b,2) -pow(c,2);
                if ( temp ==  0)
                {
                    printf("TRIPPEL IST %d, %d, %d \n", a, b, c);
                }
                else
                {
                    
                }
                
            }
            
        }
        
    }
    
    return (42);
}