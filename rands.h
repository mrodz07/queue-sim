#include <stdio.h>
#include "my_statistics.h"
#include "my_utils.h"
#include <string.h>

int gen_rand(int mul, int inc, int mod, int sum);
int* gen_rand_arr(int seed, int mul, int inc, int mod, int num);
int is_valid_gen(int seed, int mul, int inc, int mod);
void read_gen(int *seed, int *mul, int *inc, int *mod, int *num);
double *adjust_rands(int mod, int argc, int *rands);
void calc_percentages(double step, int slices_num, double *slices, int argc, double *arr);
