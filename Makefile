
C_FLAGS = -Wall -O3 -I.  -D WORK_STATION 
	CC  = gcc -c ${C_FLAGS}
	
# MS_RX_FLAGS = -U LOG_OUTPUTS -D FIXED_SEED -D RANDOM_SEED=1288

#------------------------------------------------------------------------------------------------
Majority: main.o Initial_Setting.o transmitter.o Channel.o Majority_Decoder.o Majority_Encoder.o rand.o
	gcc -o Majority $^ -lm

#	make clean
# ---------------------------------------------------------------------------------------------------------

########################
# compile object files #
########################
main.o: main.h main.c
	${CC} main.c
Initial_Setting.o: Initial_Setting.h Initial_Setting.c
	${CC} Initial_Setting.c
transmitter.o: transmitter.h transmitter.c
	${CC} transmitter.c
Channel.o: Channel.h Channel.c
	${CC} Channel.c
Majority_Decoder.o: Majority_Decoder.h Majority_Decoder.c
	${CC} Majority_Decoder.c
Majority_Encoder.o: Majority_Encoder.h Majority_Encoder.c
	${CC} Majority_Encoder.c
rand.o: rand.h rand.c
	${CC} rand.c
# ----------------------------------------------------------------------------------------------------

# remove all files that are named "*~" and "*.o" under ${SIM_DIR} , also confirm to remove MS_TX_main*
clean:
	rm *.o Majority

exp_all:
	mkdir ./exp_${date_in}/${BW}_${CH}
	cp -rf ./sim_script/ ./exp_${date_in}/${BW}_${CH}/
#	mv ./exp_${date_in}/${BW}_${CH}/sim_script/SimScript_${BW}_${CH}.h ./exp_${date_in}/${BW}_${CH}/sim_script/SimScript.h
	cp -rf ./files/ ./exp_${date_in}/${BW}_${CH}/.
	rm -rf ./exp_${date_in}/${BW}_${CH}/files/module_IO_data/Rx/main/*
	cp MS_RX_main_default_rx ./exp_${date_in}/${BW}_${CH}/.
	cp calc_ber_avg_var ./exp_${date_in}/${BW}_${CH}/.
#	ln -s `pwd`/exp_${date_in}/${BW}_${CH}/MS_RX_main_default_rx ./exp_${date_in}/${BW}_${CH}/wcp1.csh
	cp RunCase_N1N2S3.csh ./exp_${date_in}/${BW}_${CH}/.
	cp RunCase_N1N2S3_UNLOG.csh ./exp_${date_in}/${BW}_${CH}/.
	cp bkill_N1_N2.csh ./exp_${date_in}/${BW}_${CH}/.
	chmod -R 777 ./exp_${date_in}/.
# ------------------------------------------------------------------------------------------------------------------------

