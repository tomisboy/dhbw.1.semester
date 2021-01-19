#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#pragma warning(disable : 4996)

int main(void)
{
    char tmpvorname[10 + 1] = {'a', 'b', 'c'};
    char *zeigervorname = tmpvorname;
    bereinige(zeigervorname);

    return (42);
}
void bereinige(char *bekommenerZeiger)
{
    int i;
    for (i = 0; i < 10; i++)
    {
        printf("%c\n", bekommenerZeiger[i]);
    }
    // prinft("%s" ,bekommenerZeiger);
}