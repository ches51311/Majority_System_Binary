
// ****************************** General parameters ******************************
//#define NUM_SIM      				(1000000000)
//#define MAX_BLOCK_ERROR 			(100)
//#define NUM_SNR					(1) // Number of SNRs
//#define Show_Interval			(10000)
/*#if NUM_SNR	== 1
#define INPUT_SNR
#endif
*/
//#define BIT_P_SYM 	(6)
//#define GF_ORDER 	(64)
int BIT_P_SYM, GF_ORDER;
// ****************************** Random parameters ******************************

//#define FIXED_SEED
#define INITIAL_SEED 			(-1)


// ****************************** Decoding parameters ******************************
#define DECODING_ALGORITHM			(BIT_FLIP)
//---------------------------------------------------------
#define BP (1)   
#define BIT_FLIP (2) 
#if DECODING_ALGORITHM == BP
#define MinSum
//#define ZeroCodeword
#endif
#if DECODING_ALGORITHM == BIT_FLIP
#define BF_Method 		(WSRBI)
//---------------------------------------------------------
#define BF_MaxReliMeasure (1)   
#define MaxNode (2) 
#define WSRBI (3)
#define HRBI (4)   
#define OSMLG (5)   
//--------------------------------------------------------
#if BF_Method == HRBI
	#define NORMALIZATION
	#define HardReliability
	#define Accumulate
	#define SeperateChannel
	#define MaxInNode
#endif
#if BF_Method == WSRBI
	#define Weighting
	#define NORMALIZATION
	#define SoftReliability
	#define Accumulate
	#define SeperateChannel
	#define MaxInNode
	//#define Offset
	#define Scale
#endif
#if BF_Method == OSMLG
	#define HardReliability
#endif



#define Qantize
//#define ApproxNormal
#endif
//#define LUT
//#define UndetectedError
#define TuneFactor
//#define RandAssign
#ifdef RandAssign
#define ColBlock	(16)
#define RowBlock (8)
#define CPMSize  (63)
int AssignValue[RowBlock][ColBlock];
#endif
//#define RandAssign2
#ifdef RandAssign2
int AssignValue[64];
#endif
//---------------------------------------------------------

// ****************************** Channel parameters ******************************

#define CHANNEL_TYPE						(AWGN_CH) 	
//---------------------------------------------------
#define AWGN_CH				              	(0)
#define test									(1)
#define Rayleigh								(2)
//---------------------------------------------------
// ****************************** Modulation Type ******************************

#define Mod_TYPE						(BPSK) 	
//---------------------------------------------------
#define BPSK				              	(0)
#define QAM16							(2)
#define QAM64							(3)
//---------------------------------------------------
#if Mod_TYPE == BPSK
#define Mod_Dim  (1)
#endif
#if Mod_TYPE == QAM16
#define Mod_Dim  (4)
#endif
#if Mod_TYPE == QAM64
#define Mod_Dim  (6)
#endif
//#define NormalScale 1000
#define CLIPPING
#define LLR_BOUND 100
//#define SHOW_LLR
//#define NOISE_FREE
#define STATIC_CHANNEL


#define SNR_DEFINITION						(Eb_N0)	
//---------------------------------------------------
#define Eb_N0			              	(1)
//---------------------------------------------------



/* Constants */
#define Pi                            (3.14159265358979)
