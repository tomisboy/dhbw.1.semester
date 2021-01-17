#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    union intParts
    {
        float f;
        char c[4];
    } zahl;

    zahl.f = 12.625;
    printf("%d \n %d \n %d \n %d", zahl.c[0], zahl.c[1], zahl.c[2], zahl.c[3]);
    // unions geben das Char array anders rum an bsp
    //
    // 12.625 :ist in der float schreibweise: 01000001||01001010||00000000||00000000
    //so steht es auch in zahl.f
    //zahl.c[i] steh aber [0]=00000000 [1]= 00000000 [2]= 01001010 [3] = 01000001
    //                           0               0           74              65

    char reverse_f[32 + 1] = {0};
    char reverse_temp[4][9] = {0};

    int i;
    int j = 0;
    for (i = 3; i > 0; i--)
    {
        
        itoa(zahl.c[i], reverse_temp[j], 2);
        j++;
    }

    for (i = 0; i < 8; i++)
    {
        printf("%d", !!((zahl.c[3] << i) & 0x80));
    }
    printf("\n");

    return 0;
    return (42);
}


//88.125 : 01000010||10110000||01000000||00000000

//12.625 : 01000001||01001010||00000000||00000000