#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "main.h"
#include "rand.h"
#ifdef WORK_STATION
#include <sys/types.h>
#include <unistd.h>
#endif

long static *idum;

void Rand_init()
{

idum = (long *)malloc(sizeof(long));

#ifdef	FIXED_SEED
*idum = (long)INITIAL_SEED;
#else
	#ifdef WORK_STATION
	long now;
	*idum = -1*(unsigned)(time(&now)+getpid()) ;
	if(*idum >0) *idum = 0 - *idum;
	#else
	*idum = -1*(unsigned)time( NULL ) ;
	#endif
#endif

}


double ran1()
{
	int j;
	long k;
	static long iy=0;
	static long iv[NTAB];
	double temp;

	
	if (*idum <= 0 || !iy) 
	{
		if (-(*idum) < 1) 
			*idum=1; 
		else 
			*idum = -(*idum);
		for (j=NTAB+7;j>=0;j--) 
		{
			k=(*idum)/IQ;
			*idum=IA*(*idum-k*IQ)-IR*k;
			if (*idum < 0) 
				*idum += IM;
			if (j < NTAB) 
				iv[j] = *idum;
		}
		iy=iv[0];
	}
	k=(*idum)/IQ; 
	*idum=IA*(*idum-k*IQ)-IR*k; 
	if (*idum < 0) 
		*idum += IM;
	j=iy/NDIV; 
	iy=iv[j]; 
	iv[j] = *idum;
	if ((temp=AM*iy) > RNMX) 
		return RNMX;
	else 
		return temp;
}


void normal(double *n,double sigma)
{
    double x1,x2, ss;
	do{
		x1=ran1();
		x2=ran1();
		x1=2.0*x1-1.0;
		x2=2.0*x2-1.0;
		ss=pow(x1,2)+pow(x2,2);
	}while(ss>=1.0);
	n[0]=sigma*x1*sqrt((-2)*log(ss)/ss);
	n[1]=sigma*x2*sqrt((-2)*log(ss)/ss);
} 


int int_pow(int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
           result *= base;
        exp /= 2;
        base *= base;
    }
    return result;
}



int perm(int N, int K)
{
	if (N<K) return 1;
    int ans = 1;
    while (K--) ans *= N--;
    return ans;
}

int comb(int N, int K)
{
	if (N<K) return 1;
    int ans = 1;
    for (int k=1, n=N; k<=K; k++, n--)
        ans = ans * n / k;
    return ans;
}




