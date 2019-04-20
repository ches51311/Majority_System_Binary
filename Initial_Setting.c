#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"
#include "Initial_Setting.h"
#include "rand.h"



void Read_Parameters(int *R, int *M, double *SNR, int *NUM_SIM, int *SUB_NUM_SIM, int *decode_type){
	char filename[300];
	FILE *fp_input;
    int swimdi;

	sprintf(filename,"sim_parameters.txt");
	fp_input=fopen(filename,"r");
	swimdi = fscanf(fp_input, "%d", R);
	swimdi = fscanf(fp_input, "%d", M);
	swimdi = fscanf(fp_input, "%lf", SNR);
	swimdi = fscanf(fp_input, "%d", NUM_SIM);
	swimdi = fscanf(fp_input, "%d", SUB_NUM_SIM);
	swimdi = fscanf(fp_input, "%d", decode_type);
    swimdi++;// just avoid warning =D
}



void Initial_Setting( int *R, int *M, int *ROW, int *COL, int **RMatrix){

	int i, j, k;

    for (i=0; i<*ROW; i++){
        for (j=0; j<*COL; j++){
            RMatrix[i][j] = 1;
        }
    }

    int num = 1;
    int position;
    int *cmbs;
    cmbs = malloc(*M*sizeof(int));

    for (i=0; i<*R+1; i++){
        if (i == 1){
            for (j=1; j<*M+1; j++){
                for (k=0; k<*COL; k++){
                    RMatrix[num][k] = k/int_pow(2, *M-j)%2;
                }
                num = num + 1;
            }
        }
        //generate the combination
        if (i > 1){
            for (j=0; j<i; j++){
                *(cmbs+j) = j+1;
                //here
                for (k=0; k<*COL; k++) RMatrix[num][k] = RMatrix[num][k] * RMatrix[*(cmbs+j)][k];
            }
            num = num + 1;
            position = i-1;
            while (1){
                if (*cmbs == *M-i+1) break;
                if (position == i-1){
                    if (*(cmbs+position) == *M){
                        position = position - 1;
                    }
                    else if (*(cmbs+position) < *M){
                        *(cmbs+position) = *(cmbs+position) + 1;
                    }
                }
                if (position < i-1){
                    while (*(cmbs+position)+1 == *(cmbs+position+1)){
                        position = position - 1;
                    }
                    *(cmbs+position) = *(cmbs+position) + 1;
                    while (position < i-1){
                        *(cmbs+position+1) = *(cmbs+position)+1;
                        position = position + 1;
                    }
                }
                for (int j=0; j<i; j++){
                    //here
                    for (int k=0; k<*COL; k++) RMatrix[num][k] = RMatrix[num][k] * RMatrix[*(cmbs+j)][k];
                }
                num = num + 1;
           }
        }
    }
    free(cmbs);
}