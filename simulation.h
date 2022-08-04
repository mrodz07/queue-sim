#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include "rands.h"

#define MAX_SIZE						20

#define MINUTE							60
#define TIME_SHORTENER			0.1
#define TIME_WAIT						10	
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
	int attending;
	int avail;
	double waiting_time;
	pthread_t client_thread;
	pthread_mutex_t* lock;
} client;

typedef struct server 
{
	int server_id;
	int clients_served;
	int client_num;
	double *response_times;
	pthread_t server_thread;
	pthread_mutex_t* lock;
} server;

int client_num = 0;
int finished = 0;
int server_num = 0; 
int clients_served = 0;
double *client_time = NULL;
double *server_time = NULL;
client *client_arr = NULL;
server *server_arr = NULL;
pthread_mutex_t c_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t s_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t t_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t v_lock = PTHREAD_MUTEX_INITIALIZER;

int main();
void read_queue(int *nc, int *ns, int *a, int *s);
double* calc_arrival_times(int time, int a, int argc, double *rands);
double* calc_service_times(int time, int s, int argc, double *rands);
void* start_simulation();
void* client_generator();
void* server_generator();
void* client_main(void* args);
void* server_main(void* args);
char* get_time();
