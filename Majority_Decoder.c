#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//#include <conio.h>
#include "main.h"
#include "Majority_Decoder.h"


void Majority_Decode_hard(int *Est_Codeword, double *Channel_Out, int *R, int *M, int *ROW, int *COL, int **RMatrix){
    int *Channel_Out_int;
    Channel_Out_int = malloc(*COL*sizeof(int));

	int i=0, j=0, k=0, l=0, s=0, t=0;

    for (i=0; i<*COL; i++)
    {
        if (*(Channel_Out+i) >= 0) *(Channel_Out_int+i) = 0;
        if (*(Channel_Out+i) < 0) *(Channel_Out_int+i) = 1;
    }
    for (i=0; i<*ROW; i++){
        *(Est_Codeword+i) = -2;
    }


    int V_encode_pos;
    int V_encode_size;


    int position;
    int *V_pos_nums;
    V_pos_nums = malloc(*M*sizeof(int));//at most m
    int *V_pos_nums_exclu;
    V_pos_nums_exclu = malloc(*M*sizeof(int));//at most m
    int tmp;
    int check;

    int vote_size;//the i'th V encode's total vote
    int sub_vote_size;//in each vote, have this group size
    int *Aj;
    Aj = malloc(int_pow(2,*M)*sizeof(int));
    int Aj_sum;

    int *j_fix;
    j_fix = malloc(*M*sizeof(int));//at most fix m number;
    int *j_no_fix;
    j_no_fix = malloc(*M*sizeof(int));//at most no fix m number;

    int *sub_vote;
    sub_vote = malloc(*M*sizeof(int));// (x1,x2,x3,x4,x5)
    int sub_vote_int;


    int l_tmp, s_tmp;
    
    for (i=*R; i>-1; i--){
        V_encode_pos = 0;
        for (j=0; j<i; j++){
                V_encode_pos = V_encode_pos + comb(*M, j);//if i=3, then RM35 start from 16
            }
        V_encode_size = comb(*M,i);

        for (j=0; j<i; j++) {
            *(V_pos_nums+j) = j+1;//if i=3, then num start from a123 = (1,2,3)
        }

        position = i-1;

        vote_size = int_pow(2, *M-i);

        for (k=V_encode_pos; k<V_encode_pos+V_encode_size; k++){

            tmp = 0;
            for (l=1; l<*M+1; l++){
                check = 0;
                for (s=0; s<i; s++){
                    if (*(V_pos_nums+s) == l) check = 1;
                }
                if (check == 0){
                    *(V_pos_nums_exclu + tmp) = l;
                    tmp = tmp + 1;
                }
            }
            
            for (l=0; l<vote_size; l++){
                *(Aj+l) = 0;
                sub_vote_size = int_pow(2, i);
                l_tmp = l;
                //printf("\nj_fix:");
                for (t=0; t<*M-i; t++){
                    *(j_fix+t) = l_tmp%2;
                    //printf("%d", *(j_fix+t));
                    l_tmp = l_tmp/2;
                }

                for (s=0; s<sub_vote_size; s++){
                    s_tmp = s;
                    //printf("\nj_no_fix:");
                    for (t=0; t<i; t++){
                        *(j_no_fix+t) = s_tmp%2;
                        //printf("%d", *(j_no_fix+t));
                        s_tmp = s_tmp/2;
                    }
                    for (t=0; t<i; t++){
                        *(sub_vote+*(V_pos_nums+t)-1) = *(j_no_fix+t);//-1 is let (1,2,3) to (0,1,2)
                    }
                    for (t=0; t<*M-i; t++){
                        *(sub_vote+*(V_pos_nums_exclu+t)-1) = *(j_fix+t);
                    }//here get the sub_vote binary
                    
                    sub_vote_int = 0;
                    //printf("\nsub_vote : ");
                    for (t=0; t<*M; t++) {
                        //printf("%d", *(sub_vote+t));
                        sub_vote_int = sub_vote_int + *(sub_vote+t)*int_pow(2,*M-t-1);
                    }

                    //printf("\n%lf ", *(V_get_tanh+sub_vote_int));


                    *(Aj+l) = *(Aj+l) + *(Channel_Out_int+sub_vote_int);

                    for (t=V_encode_pos+V_encode_size; t<*ROW; t++){
                        if (RMatrix[t][sub_vote_int] == 1){
                            //printf("\nt, sub_vote_int, U_ans:");
                            //printf("%d %d %d", t, sub_vote_int, *(U_ans+t));
                            *(Aj+l) = *(Aj+l) + *(Est_Codeword+t);
                            //printf(" Aj%lf", *(Aj+l));
                            }
                    }
                }
                //printf("\nAj%lf", *(Aj+l));
            }

            Aj_sum = 0;
            for (l=0; l<vote_size; l++){
                //*(Aj+l) = *(Aj+l)%2;
                Aj_sum = Aj_sum + *(Aj+l)%2;
            }
            //printf("\nAj_sum= %lf", Aj_sum);
            if (Aj_sum >= vote_size/2){
                *(Est_Codeword+k) = 1;
            }
            if (Aj_sum < vote_size/2){
                *(Est_Codeword+k) = 0;
            }


            //V_pos_nums
            if (position == i-1){
                if (*(V_pos_nums+position) == *M){
                    position = position - 1;
                }
                else if (*(V_pos_nums+position) < *M){
                    *(V_pos_nums+position) = *(V_pos_nums+position) + 1;
                }
            }
            if (position < i-1){
                while (*(V_pos_nums+position)+1 == *(V_pos_nums+position+1)){
                    position = position - 1;
                }
                *(V_pos_nums+position) = *(V_pos_nums+position) + 1;
                while (position < i-1){
                    *(V_pos_nums+position+1) = *(V_pos_nums+position)+1;
                    position = position + 1;
                }
            }


        }
    }

    //free(Channel_Out_int);// these two can't free lol;
    //free(V_pos_nums);
    free(V_pos_nums_exclu);
    free(Aj);
    free(j_fix);
    free(j_no_fix);
    free(sub_vote);


}


void Majority_Decode_soft(int *Est_Codeword, double *Channel_Out, int *R, int *M, int *ROW, int *COL, int **RMatrix, double *sigma){

    double *Channel_Out_tanh;
    Channel_Out_tanh = malloc(*COL*sizeof(double));

	int i=0, j=0, k=0, l=0, s=0, t=0;

    for (i=0; i<*COL; i++)
    {
        *(Channel_Out_tanh+i) = (double)tanh(2 * *(Channel_Out+i)/(*sigma * *sigma));
    }
    for (i=0; i<*ROW; i++){
        *(Est_Codeword+i) = -2;
    }


    int V_encode_pos;
    int V_encode_size;


    int position;
    int *V_pos_nums;
    V_pos_nums = malloc(*M*sizeof(int));//at most m
    int *V_pos_nums_exclu;
    V_pos_nums_exclu = malloc(*M*sizeof(int));//at most m
    int tmp;
    int check;

    int vote_size;//the i'th V encode's total vote
    int sub_vote_size;//in each vote, have this group size
    double *Aj;
    Aj = malloc(int_pow(2,*M)*sizeof(double));
    double Aj_sum;

    int *j_fix;
    j_fix = malloc(*M*sizeof(int));//at most fix m number;
    int *j_no_fix;
    j_no_fix = malloc(*M*sizeof(int));//at most no fix m number;

    int *sub_vote;
    sub_vote = malloc(*M*sizeof(int));// (x1,x2,x3,x4,x5)
    int sub_vote_int;


    int l_tmp, s_tmp;
    
    for (i=*R; i>-1; i--){
        V_encode_pos = 0;
        for (j=0; j<i; j++){
                V_encode_pos = V_encode_pos + comb(*M, j);//if i=3, then RM35 start from 16
            }
        V_encode_size = comb(*M,i);

        for (j=0; j<i; j++) {
            *(V_pos_nums+j) = j+1;//if i=3, then num start from a123 = (1,2,3)
        }

        position = i-1;

        vote_size = int_pow(2, *M-i);

        for (k=V_encode_pos; k<V_encode_pos+V_encode_size; k++){

            tmp = 0;
            for (l=1; l<*M+1; l++){
                check = 0;
                for (s=0; s<i; s++){
                    if (*(V_pos_nums+s) == l) check = 1;
                }
                if (check == 0){
                    *(V_pos_nums_exclu + tmp) = l;
                    tmp = tmp + 1;
                }
            }
            
            for (l=0; l<vote_size; l++){
                *(Aj+l) = 1;
                sub_vote_size = int_pow(2, i);
                l_tmp = l;
                //printf("\nj_fix:");
                for (t=0; t<*M-i; t++){
                    *(j_fix+t) = l_tmp%2;
                    //printf("%d", *(j_fix+t));
                    l_tmp = l_tmp/2;
                }

                for (s=0; s<sub_vote_size; s++){
                    s_tmp = s;
                    //printf("\nj_no_fix:");
                    for (t=0; t<i; t++){
                        *(j_no_fix+t) = s_tmp%2;
                        //printf("%d", *(j_no_fix+t));
                        s_tmp = s_tmp/2;
                    }
                    for (t=0; t<i; t++){
                        *(sub_vote+*(V_pos_nums+t)-1) = *(j_no_fix+t);//-1 is let (1,2,3) to (0,1,2)
                    }
                    for (t=0; t<*M-i; t++){
                        *(sub_vote+*(V_pos_nums_exclu+t)-1) = *(j_fix+t);
                    }//here get the sub_vote binary
                    
                    sub_vote_int = 0;
                    //printf("\nsub_vote : ");
                    for (t=0; t<*M; t++) {
                        //printf("%d", *(sub_vote+t));
                        sub_vote_int = sub_vote_int + *(sub_vote+t)*int_pow(2,*M-t-1);
                    }

                    //printf("\n%lf ", *(V_get_tanh+sub_vote_int));


                    *(Aj+l) = *(Aj+l) * *(Channel_Out_tanh+sub_vote_int);

                    for (t=V_encode_pos+V_encode_size; t<*ROW; t++){
                        if (RMatrix[t][sub_vote_int] == 1){
                            //printf("\nt, sub_vote_int, U_ans:");
                            //printf("%d %d %d", t, sub_vote_int, *(U_ans+t));
                            *(Aj+l) = *(Aj+l) * (double)*(Est_Codeword+t);
                            //printf(" Aj%lf", *(Aj+l));
                            }
                    }
                }
                //printf("\nAj%lf", *(Aj+l));
            }

            Aj_sum = 0;
            for (l=0; l<vote_size; l++){
                Aj_sum = Aj_sum + *(Aj+l);
            }
            //printf("\nAj_sum= %lf", Aj_sum);
            if (Aj_sum >= 0){
                *(Est_Codeword+k) = 1;
            }
            if (Aj_sum < 0){
                *(Est_Codeword+k) = -1;
            }


            //V_pos_nums
            if (position == i-1){
                if (*(V_pos_nums+position) == *M){
                    position = position - 1;
                }
                else if (*(V_pos_nums+position) < *M){
                    *(V_pos_nums+position) = *(V_pos_nums+position) + 1;
                }
            }
            if (position < i-1){
                while (*(V_pos_nums+position)+1 == *(V_pos_nums+position+1)){
                    position = position - 1;
                }
                *(V_pos_nums+position) = *(V_pos_nums+position) + 1;
                while (position < i-1){
                    *(V_pos_nums+position+1) = *(V_pos_nums+position)+1;
                    position = position + 1;
                }
            }


        }
    }

	for (i=0; i<*ROW; i++){
		if (*(Est_Codeword+i) == -1) *(Est_Codeword + i) = 1;
		else *(Est_Codeword + i) = 0;
	}

    //free(Channel_Out_tanh);// these two can't free lol;
    //free(V_pos_nums);
    free(V_pos_nums_exclu);
    free(Aj);
    free(j_fix);
    free(j_no_fix);
    free(sub_vote);

}


