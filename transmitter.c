#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "main.h"
#include "rand.h"
#include "transmitter.h"
 

void transmitter(double *Channel_In, int *CodeBits, int *COL)
{
    for (int i=0; i<*COL; i++){
        if (*(CodeBits+i)==0) *(Channel_In+i) = 1;
        if (*(CodeBits+i)==1) *(Channel_In+i) = -1;
    }
}
