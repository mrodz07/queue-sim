#include <stdio.h>
#include "rands.h"

#define MSG_NC ""
#define MSG_NS ""
#define MSG_A ""
#define MSG_S ""
#define ERR_MSG "El sistema no funcionará y caerá en una espera infinita\n"

int main();
void read_queue(int *nc, int *ns, int *a, int *s);
double* calc_arrival_times(int a, int argc, double *arr);
