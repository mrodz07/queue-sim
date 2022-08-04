#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

//#define MAX_ERR 0.00001

int count_num_in_arr(int num, int argc, double *arr);
int count_range_in_arr(double ul, double dl, int argc, double *arr);
double* copy_arr(int argc, char **argv);
char** read_str_arr(int lines, int argc);
char* read_str(int argc);
double read_num();
int find_pow_ten(double n);
int search_char(char c, int argc, char *arr);
int search_int(int b, int e, int num, int* arr);
int search_int_dup(int argc, int *arr);
char* make_substring(int b, int e, char *str);
void print_int_arr(char sep, char end, int argc, int *arr);
void print_double_arr(char sep, char end, int argc, double *arr);
void print_str_arr(char sep, char end, int argc, char **arr);
void print_str_pad(int pad, char *str);
