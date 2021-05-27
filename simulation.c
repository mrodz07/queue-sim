
#include "simulation.h"

int main() 
{
  int seed, mul, inc, mod;
  int nc, ns, a, s;
	int low = 1, up = 5;
	int* rands;
	double* drands;
	double* arands;

  read_gen_without_num(&seed, &mul, &inc, &mod);
	read_queue(&nc, &ns, &a, &s);

	if(a < (s*ns) && a > 0)
	{
		rands = malloc(sizeof(int) * nc);
		drands = malloc(sizeof(double) * nc);

		rands = gen_rand_arr(seed, mul, inc, mod, nc);
		drands = adjust_rands_range(mod, nc, low, up, rands);
		arands = calc_arrival_times(a, nc, drands);

		for(int i=0; i<nc; i++)
			printf("%f\n", arands[i]);
	}
	else
	{
		printf(ERR_MSG);
	}
}

double* calc_arrival_times(int a, int argc, double *arr)
{
	double* adjarr;
	adjarr = malloc(sizeof(double) * argc);
	double range = ((60/a)/2);

	for(int i=0; i<argc; i++)
		adjarr[i] = range * arr[i];

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
