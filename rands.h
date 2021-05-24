#include <stdio.h>
#include "my_statistics.h"
#include "my_utils.h"
#include <string.h>

/*
#define MSG_SEED "Ingresa la semilla\n"
#define MSG_MULT "Ingresa el multiplicador\n"
#define MSG_INCR "Ingresa el corrimiento\n"
#define MSG_MODI "Ingresa el módulo\n"
#define MSG_NUME "Ingresa el número de elementos\n"
#define MSG_ERRO "Ingresa datos validos\n"
*/

///*
#define MSG_SEED ""
#define MSG_MULT ""
#define MSG_INCR ""
#define MSG_MODI ""
#define MSG_NUME ""
#define MSG_ERRO ""
//*/

/*
#define MSG_QUEU "Cola: "
#define MSG_PERI "Periodo: "
#define MSG_CICL "Ciclo: "
#define MSG_AVRG "Media: "
#define MSG_MEDI "Mediana: "
#define MSG_MODE "Moda: "
#define MSG_SDEV "Desviación estandar: "
#define MSG_VARI "Varianza: "
#define MSG_LONGQUE "Longitud de la cola: "
#define MSG_LONGPER "Longitud del periodo: "
#define MSG_LONGCIC "Longitud del ciclo: "
#define MSG_SL_P1		"Porcentaje de valores ajustados a el subintervalo ("
#define MSG_SL_P2   " < x <= "	
#define MSG_SL_P3   ")\n"
*/



#define MSG_QUEU ""
#define MSG_PERI ""
#define MSG_CICL ""
#define MSG_AVRG ""
#define MSG_MEDI ""
#define MSG_MODE ""
#define MSG_SDEV ""
#define MSG_VARI ""
#define MSG_LONGQUE ""
#define MSG_LONGPER ""
#define MSG_LONGCIC ""
#define MSG_SL_P1		""
#define MSG_SL_P2   ""	
#define MSG_SL_P3   ""


int main();
int gen_rand(int mul, int inc, int mod, int sum);
int* gen_rand_arr(int seed, int mul, int inc, int mod, int num);
int is_valid_gen(int seed, int mul, int inc, int mod);
void read_gen(int *seed, int *mul, int *inc, int *mod, int *num);
double *adjust_rands(int mod, int argc, int *rands);
void calc_percentages(double step, int slices_num, double *slices, int argc, double *arr);
void print_result(int queue_size, int *queue, int period_size, int *period, int cicle_size, int *cicle, double avg, int median, int mode_size, int *mode, double sd, double variance, double step, int slices_size, double *slices);
