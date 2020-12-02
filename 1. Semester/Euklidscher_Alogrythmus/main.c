#include <stdio.h>

int main() {

  int x,y;
    printf("ZAHL 1 eingeben: \n ");
    scanf_s("%i",&x);
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
