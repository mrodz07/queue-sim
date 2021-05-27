
#include "simulation.h"

int main() 
{
  int seed, mul, inc, mod;
  int nc, ns, a, s;
	int low = 1, up = 5;
	int* rands;
	double* drands;
	double* arands;
	double* srands;

  read_gen_without_num(&seed, &mul, &inc, &mod);
	read_queue(&nc, &ns, &a, &s);

	if(a < (s*ns) && a > 0)
	{
		rands = malloc(sizeof(int) * nc);
		drands = malloc(sizeof(double) * nc);

		rands = gen_rand_arr(seed, mul, inc, mod, nc);
		drands = adjust_rands_range(mod, nc, low, up, rands);
		arands = calc_arrival_times(MINUTE, a, nc, drands);
		drands = adjust_rands_range(mod, nc, low, up, rands);
		srands = calc_service_times(MINUTE, s, nc, drands);
		printf("Llegada de usuarios\n");
		for(int i=0; i<nc; i++)
			printf("%f\n", arands[i]);
		printf("Tiempo de servicio\n");
		for(int i=0; i<nc; i++)
			printf("%f\n", srands[i]);
	}
	else
	{
		printf(ERR_MSG);
	}
}

double* calc_service_times(int time, int s, int argc, double *rands)
{
	double* adjserv;
	adjserv = malloc(sizeof(double) * argc);
	double range = ((time/s)/2);
	for(int i=0; i<argc; i++)
		adjserv[i] = ((time/s) + (range * rands[i]));
	
	return adjserv;
}

double* calc_arrival_times(int time, int a, int argc, double *rands)
{
	double* adjarr;
	adjarr = malloc(sizeof(double) * argc);
	double range = ((time/a)/2);

	for(int i=0; i<argc; i++) {
		if(i>0)
			adjarr[i] = adjarr[i-1] + ((time/a) + (range * rands[i]));
		else
			adjarr[i] = ((time/a) + (range * rands[i]));
	}

	return adjarr;
}

void read_queue(int *nc, int *ns, int *a, int *s)
{
	printf("%s", MSG_NC);
	*nc = (int)read_num();
	printf("%s", MSG_NS);
	*ns = (int)read_num();
	printf("%s", MSG_A);
	*a = (int)read_num();
	printf("%s", MSG_S);
	*s = (int)read_num();
}
