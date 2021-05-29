
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "rands.h"

#define MAX_SIZE						20

#define MINUTE							60
#define TIME_SHORTENER			0.1
#define TIME_WAIT						35
#define TIME_NOTICE_DIVISOR	1	

#define MSG_NC							""
#define MSG_NS							""
#define MSG_A								""
#define MSG_S								""
#define ERR_MSG							"El sistema no funcionará y caerá en una espera infinita\n"
#define CLIENT_ARRIVE_MSG		"[%s]: Llega cliente #%d\n"
#define CLIENT_WAITING_MSG  "[%s]: Cliente #%d esperando a que un servidor se desocupe\n"
#define SERVER_START_MSG		"[%s]: Cliente #%d atendido por servidor #%d\n"
#define SERVER_END_MSG			"[%s]: Cliente #%d termina de ser atendido por servidor #%d\n"

typedef struct client
{
	int client_id;
	int is_finished;
	int avail;
	double waiting_time;
	pthread_t client_thread;
	pthread_mutex_t* lock;
	void (*wait)(double t);
	void (*set_avail)(int i);
} client;

typedef struct sim_vals
{
	int client_num;
	int server_num; 
	int clients_sirved;
	double *client_time;
	double *server_time;
	client *client_arr;
	pthread_mutex_t *c_lock;
	pthread_mutex_t *s_lock;
} sim_vals;

typedef struct client_thread_vals 
{
	int* client_id;
	int* is_finished;
	int* avail;
	double* waiting_time;
	pthread_mutex_t* lock;
	void (*wait)(double t);
	void (*set_avail)(int i);
} client_thread_vals;

typedef struct server 
{
	int server_id;
	int clients_served;
	int client_num;
	double *response_times;
	sim_vals* simu_vals;
	pthread_t server_thread;
	pthread_mutex_t* lock;
	client*	client_threads;
	void (*attend)(int i);
} server;

typedef struct server_gen_vals
{
	sim_vals* simu_vals;	
	client* client_threads;
} server_gen_vals;

typedef struct server_thread_vals 
{
	int* server_id;
	int* clients_served;
	int* client_num;
	client* client_threads;
	double* response_times;
	pthread_mutex_t* lock;
	sim_vals* simu_vals;
	void (*attend)(int i);
} server_thread_vals;

int main();
void read_queue(int *nc, int *ns, int *a, int *s);
double* calc_arrival_times(int time, int a, int argc, double *rands);
double* calc_service_times(int time, int s, int argc, double *rands);
void* start_simulation(void* args);
void* client_generator(void* args);
void* server_generator(void* args);
void* client_main(void* args);
void	client_set_avail(int a);
void	client_wait(double t);
void* server_main(void* args);
char* get_time();
void	server_attend(int i);
