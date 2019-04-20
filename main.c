#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

#include "main.h"
#include "Initial_Setting.h"
#include "transmitter.h"
#include "Channel.h"
#include "Majority_Encoder.h"
#include "Majority_Decoder.h"
#include "rand.h"

int main()
{
	int R, M;
	int ROW, COL;
	int **RMatrix;

	double SNR, sigma;
	int NUM_SIM, SUB_NUM_SIM;
	int decode_type;

	int *Info_Symbol, *CodeBits, *Est_Codeword;
	double *Channel_In, *Channel_Out;

	int Block_error, Bit_error;
	int tmp_cnt;

	int i = 0, j = 0, k=0;

	Read_Parameters(&R, &M, &SNR, &NUM_SIM, &SUB_NUM_SIM, &decode_type);

    for (i=0; i<R+1; i++){
        ROW = ROW + comb(M,i);
    }
    COL = int_pow(2, M);
    int *tmp;
    RMatrix = (int**)malloc( ROW * sizeof(int *));
    tmp = (int*)malloc(ROW * COL * sizeof(int));
    for (i=0; i<ROW; tmp += COL){
        RMatrix[i++] = tmp;
    }
	
	Initial_Setting(&R, &M, &ROW, &COL, RMatrix);


	sigma = sqrt(1/(2 * ((double) ROW/ (double) COL) * SNR));
	Info_Symbol = malloc(ROW*sizeof(int));
	CodeBits = malloc(COL*sizeof(int));
	Est_Codeword = malloc(COL*sizeof(int));
	Channel_In = malloc(COL*sizeof(double));
	Channel_Out = malloc(COL*sizeof(double));

	Rand_init();

	Block_error =  0;
	Bit_error =  0;

	printf("R = %d, M = %d, Info_Symbol = %d, CodeBits = %d\n", R, M, ROW, COL);

	printf("SNR = %lf, sigma = %lf, NUM_SIM = %d, SUB_NUM_SIM = %d\n", 
			SNR, sigma, NUM_SIM, SUB_NUM_SIM);
	if (decode_type == 0)
	printf("decode_type = hard \n");
	if (decode_type == 1)
	printf("decode_type = soft \n");
	if (decode_type != 0 && decode_type != 1) {
		printf("error decode_type!!\n");
		return 0;
	}


	for (i=0; i<NUM_SIM/SUB_NUM_SIM; i++){
		for (j=0; j<SUB_NUM_SIM; j++){
			Majority_Encode(CodeBits, Info_Symbol, &ROW, &COL, RMatrix);
			transmitter(Channel_In, CodeBits, &COL);
 			AWGN_Channel(Channel_Out, Channel_In, &COL, &sigma);
			if (decode_type == 0)
				Majority_Decode_hard(Est_Codeword, Channel_Out, &R, &M, &ROW, &COL, RMatrix);
			if (decode_type == 1)
				Majority_Decode_soft(Est_Codeword, Channel_Out, &R, &M, &ROW, &COL, RMatrix, &sigma);
			tmp_cnt = 0;
			for (k=0; k<ROW; k++){
				if (*(Est_Codeword+k) != *(Info_Symbol+k)){
					tmp_cnt = tmp_cnt + 1;
				}
			}
			if (tmp_cnt > 0){
				Bit_error = Bit_error + (double) tmp_cnt;
				Block_error = Block_error + 1;
			}
		}
		printf("*******************************************\n");
		printf("simulation time: %d\n", (i+1)*SUB_NUM_SIM);
		printf("Block_error_rate = %lf (%d/%d)\n", ((double) Block_error) / ((double) ((i+1)*SUB_NUM_SIM)), Block_error, (i+1)*SUB_NUM_SIM);
		printf("Bit_error_rate = %lf (%d/%d)\n", ((double) Bit_error) / ((double) ((i+1)*SUB_NUM_SIM*ROW)), Bit_error, (i+1)*SUB_NUM_SIM*ROW);

	}

	printf("The end of simulation.\n");


	free(Info_Symbol);
	free(CodeBits);
	free(Est_Codeword);
	free(Channel_In);
	free(Channel_Out);
	free(RMatrix);

	return 0;
}



