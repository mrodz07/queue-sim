
#include "simulation.h"

int main() 
{
  int seed, mul, inc, mod;
  int nc, ns, a, s;
	int low = 1, up = 5;
	int* rands;
	double* drands;
	double* crands;
	double* srands;

  read_gen_without_num(&seed, &mul, &inc, &mod);
	read_queue(&nc, &ns, &a, &s);

	if(a < (s*ns) && a > 0)
	{
		rands = malloc(sizeof(int) * nc);
		drands = malloc(sizeof(double) * nc);

		rands = gen_rand_arr(seed, mul, inc, mod, nc);
		drands = adjust_rands_range(mod, nc, low, up, rands);
		crands = calc_arrival_times(MINUTE, a, nc, drands);
		srands = calc_service_times(MINUTE, s, nc, drands);
		start_simulation(nc, ns, crands, srands);
	}
	else
	{
		printf(ERR_MSG);
	}
}

void start_simulation(int nc, int ns, double *crands, double *srands)
{
	int clients = 0;
	pthread_t client_thread;
	pthread_t* server_threads; 

	server_threads = malloc(sizeof(pthread_t) * ns);
	
	pthread_create(&client_thread, NULL, client_generator(clients, nc, crands), NULL);

	for(int i=0; i<ns; i++)
		pthread_create(&server_threads[i], NULL, client_generator(clients, nc, crands), NULL);
}
	
void* client_generator(int clients, int argc, double *time_arr)
{
	for(int i=0; i<argc; i++)
	{
		sleep(time_arr[i] * TIME_SHORTENER);
		clients++;
		printf(CLIENT_ARRIVE_MSG, get_time(), i);
	}
	return NULL;
}

double* calc_service_times(int time, int s, int argc, double *rands)
{
	double* adjserv;
	adjserv = malloc(sizeof(double) * argc);
	double range = ((time/s)/2);
	for(int i=0; i<argc; i++)
		adjserv[i] = ((time/s) + (range * rands[i]));
	
	return adjserv;
}

double* calc_arrival_times(int time, int a, int argc, double *rands)
{
	double* adjarr;
	adjarr = malloc(sizeof(double) * argc);
	double range = ((time/a)/2);

	for(int i=0; i<argc; i++) 
			adjarr[i] = ((time/a) + (range * rands[i]));

	return adjarr;
}

void read_queue(int *nc, int *ns, int *a, int *s)
{
	printf("%s", MSG_NC);
	*nc = (int)read_num();
	printf("%s", MSG_NS);
	*ns = (int)read_num();
	printf("%s", MSG_A);
	*a = (int)read_num();
	printf("%s", MSG_S);
	*s = (int)read_num();
}

char* get_time()
{
	time_t hour;
	char *str_hour;
	struct tm *lc_time;

	hour = time(NULL);
	lc_time = localtime(&hour);
	str_hour = malloc(sizeof(char) * MAX_SIZE);
	strftime(str_hour, MAX_SIZE, "%x - %H:%M:%S", lc_time);

	return str_hour;
}
