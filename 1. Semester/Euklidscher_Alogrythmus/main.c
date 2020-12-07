#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PI 3.1415
// ersetze PI durch 3.1415
#define NIX void
#define MEINMACRO a*b/c



int main() {

  int x,y;
  printf("%f \n ", PI);
    printf("ZAHL 1 eingeben: \n ");
    scanf("%i",&x);
    fflush(stdin);
    printf("ZAHL 2 \n");
    scanf("%i",&y);
    fflush(stdin);
    while ( x !=y ){
        if (x > y)
        {
            x = x-y;
        }
        else
        {
            y = y-x;
        }
    }
printf("GGT=    %i ",x);

    return 0;
}
