#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "mystatistics.h"
#include "myutils.h"

#define MSG_SEED ""
#define MSG_MULT ""
#define MSG_INCR ""
#define MSG_MODI ""
#define MSG_NUME ""

int gen_rand(int mul, int inc, int mod, int sum);
int* gen_rand_arr(int seed, int mul, int inc, int mod, int num);
int is_valid_gen(int seed, int mul, int inc, int mod);
void read_gen(int *seed, int *mul, int *inc, int *mod, int *num);
double* adjust_rands(int mod, int argc, int *rands);
void calc_percentages(double step, int slices_num, double *slices, int argc, double *arr);
double* adjust_rands_range(int mod, int argc, int *rands);
void read_gen_without_num(int *seed, int *mul, int *inc, int *mod);
