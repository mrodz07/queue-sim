
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "rands.h"

#define MAX_SIZE						20

#define MINUTE							60
#define TIME_SHORTENER			0.1

#define MSG_NC							""
#define MSG_NS							""
#define MSG_A								""
#define MSG_S								""
#define ERR_MSG							"El sistema no funcionará y caerá en una espera infinita\n"
#define CLIENT_ARRIVE_MSG		"[%s]: Llega cliente #%d\n"
#define CLIENT_WAITING_MSG  "[%s]: Cliente #%d esperando a que un servidor se desocupe"
#define SERVER_START_MSG		"[%s]: Cliente #%d atendido por servidor #%d\n"
#define SERVER_END_MSG			"[%s]: Cliente #%d termina de ser atendido por servidor #%d\n"

typedef struct sim_vals {
	int client_num;
	int server_num; 
	int clients_served;
	int clients_arrived;
	double *client_time;
	double *server_time;
	pthread_t* client_threads;
	pthread_t* server_threads;
	pthread_mutex_t *lock;
} sim_vals;

int main();
void read_queue(int *nc, int *ns, int *a, int *s);
double* calc_arrival_times(int time, int a, int argc, double *rands);
double* calc_service_times(int time, int s, int argc, double *rands);
void start_simulation(sim_vals* vals);
void* client_generator(void* args);
void* client(void* args);
void* server(void* args);
char* get_time();
