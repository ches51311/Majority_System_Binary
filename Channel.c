#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"
#include "rand.h"
#include "Channel.h"



void AWGN_Channel(double *Channel_Out, double *Channel_In, int *COL, double *sigma)
{
    double x[2];
    for (int i=0; i<*COL/2; i++)
    {
        normal(x, *sigma);
        *(Channel_Out+i*2)=*(Channel_In+i*2) + x[0];
        *(Channel_Out+i*2+1)=*(Channel_In+i*2+1) + x[1];
    }
    if (*COL%2 == 1){
        normal(x, *sigma);
        *(Channel_Out+*COL-1) = *(Channel_In+*COL-1) + x[0];
    }

}
