//ran1 parameters
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

void Rand_init(void);
double ran1(void);
void normal(double *n, double sigma);


int int_pow(int base, int exp);
int perm(int N, int K);
int comb(int N, int K);
