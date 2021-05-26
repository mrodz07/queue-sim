#include <stdlib.h>
#include <math.h>
#include "myutils.h"

int calc_imedian(int argc, int *arr);
int calc_imode(int argc, int *arr);
double calc_iavg(int argc, int *arr);
double calc_ivariance(double avg, int argc, int *arr);
double calc_davg(int argc, double *arr);
double calc_dmedian(int argc, double *arr);
double calc_dmode(int argc, double *arr);
double calc_dvariance(double avg, int argc, double *arr);
double calc_stdev(double variance);
double calc_rel_freq(double element, double element_number);
double* calc_abs_freq_darr(int arrnum_argc, int arrsrc_argc, double *arrnum, double *arrsrc);
double* calc_abs_freq_ac_darr(int argc, double *arr_freq);
double* calc_rel_freq_darr(double element_num, int argc, double *arr_freq_ac);
double* calc_rel_freq_ac_darr(int argc, double *arr_relfreq);
