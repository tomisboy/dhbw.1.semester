#include <stdio.h>
#include <math.h>
#include <time.h>

#define ARRAYLENGTH 100000000

void SieveFunc(int cnt);

//declaring array
char numbers[ARRAYLENGTH+1];

int main()
{
    //declaring variables
    int CntPrimes = 3;
    int i, start, end;

    //fill array
    for(i = 0; i <= ARRAYLENGTH; i++)
    {
        numbers[i] = 1;
    }

    //storing first point of time
    start = clock();

    //calling sieve function with parameter: 2
    SieveFunc(CntPrimes);

    //storing second point of time
    end = clock();

    //count prime numbers (ignoring even numbers)
    for(i = 3; i <= ARRAYLENGTH; i+=2)
    {
        if(numbers[i] == 1)
        {
            CntPrimes++;
        }
    }

    //printing result
    printf("Number of primes: %i", CntPrimes-2);
    printf("\n Time: %i ms", end-start);

    //the number with all answers
    return 42;
}

//takes number (parameter: cnt) and set multiplies to 0;
void SieveFunc(int cnt)
{
    //variable for loop
    int i;
    int squareroot = (int)sqrt(ARRAYLENGTH);

    //goes through all uneven numbers (even can be ignored because they are multiples of 2)
    for(cnt;cnt <= squareroot;cnt+=2)
    {
        //if cnt is not a prime skip second loop (Idea from Benjamin Arp)
        if(!numbers[cnt])
            continue;

        //starts at square of cnt, stops at end of array, adds cnt every pass
        for(i = cnt*cnt; i <= ARRAYLENGTH; i+=cnt)
        {
            //setting non prime to zero
            numbers[i] = 0;
        }
    }
}