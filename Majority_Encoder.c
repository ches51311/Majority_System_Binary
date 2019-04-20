#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"
#include "rand.h"
#include "Majority_Encoder.h"


void Majority_Encode(int *CodeBits, int *Info_Symbol, int *ROW, int *COL, int **RMatrix)
{
	int i = 0, j=0;
	double random_double;
	for (i=0; i<*ROW; i++)
    {
	    random_double = ran1();
	    if (random_double > 0.5){
	    *(Info_Symbol+i) = 1;
	    }
	    else{
	    *(Info_Symbol+i) = 0;
	    }
    }

    for (i=0; i<*COL; i++){
        *(CodeBits+i)=0;
        for (j=0; j<*ROW; j++){
            *(CodeBits+i) = *(CodeBits+i) + *(Info_Symbol+j)*RMatrix[j][i];
        }
        *(CodeBits+i) = *(CodeBits+i)%2;
    }

}
