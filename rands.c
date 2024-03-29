#include "rands.h"

int gen_rand(int mul, int inc, int mod, int sum)
{
	return (mul * sum + inc) % mod;
}

int* gen_rand_arr(int seed, int mul, int inc, int mod, int num)
{
	int *rands = malloc(sizeof(int) * num);
	rands[0] = seed;
	for (int i = 1; i < num; i++) {
		rands[i] = gen_rand(mul, inc, mod, rands[i-1]);
	}
	return rands;
}

double *adjust_rands(int mod, int argc, int *rands)
{
	double *adj_rands = malloc(sizeof(double) * argc);
	int max_val = mod - 1;

	for (int i = 0; i < argc; i++) {
		adj_rands[i] = (double)rands[i]/max_val;	
	}

	return adj_rands;
}

int gen_rand_num(int low, int up)
{
	return (rand() % (up - low + 1)) + low;
}

int gen_rand_sign()
{
	int sign = gen_rand_num(1, 2);

	if(sign == 2)
		sign = -1;

	return sign;
}

double *adjust_rands_range(int mod, int argc, int low, int up, int *rands)
{
	double *adj_rands = malloc(sizeof(double) * argc);
	int max_val = mod - 1; 

	for (int i = 0; i < argc; i++) {
		adj_rands[i] = ((double)rands[i]/max_val) + ((max_val/2)*(gen_rand_num(low, up)/10));
		adj_rands[i] = adj_rands[i] * gen_rand_sign();
	}

	return adj_rands;
}

int is_valid_gen(int seed, int mul, int inc, int mod)
{
	if (mod > 0 && mul >= 0 && mul < mod && inc >= 0 && inc < mod && seed >= 0 && seed < mod) 
		return 1;
	else
		return 0;
}

void calc_percentages(double step, int slices_num, double *slices, int argc, double *arr)
{
	double tmp = 0;

	for (int i = 0; i < slices_num; i++) {
		slices[i] = ((double)count_range_in_arr(tmp, tmp+step, argc, arr) / (double)argc) * 100;
		tmp+=step;
	}
}

void read_gen(int *seed, int *mul, int *inc, int *mod, int *num)
{
	printf("%s", MSG_SEED);
	*seed = (int)read_num();
	printf("%s", MSG_MULT);
	*mul = (int)read_num();
	printf("%s", MSG_INCR);
	*inc = (int)read_num();
	printf("%s", MSG_MODI);
	*mod = (int)read_num();
	printf("%s", MSG_NUME);
	*num = (int)read_num();
}

void read_gen_without_num(int *seed, int *mul, int *inc, int *mod)
{
	printf("%s", MSG_SEED);
	*seed = (int)read_num();
	printf("%s", MSG_MULT);
	*mul = (int)read_num();
	printf("%s", MSG_INCR);
	*inc = (int)read_num();
	printf("%s", MSG_MODI);
	*mod = (int)read_num();
}
