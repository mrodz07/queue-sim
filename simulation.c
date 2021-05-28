
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
	sim_vals* vals;
	pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  read_gen_without_num(&seed, &mul, &inc, &mod);
	read_queue(&nc, &ns, &a, &s);

	if(a < (s*ns) && a > 0)
	{
		rands  = malloc(sizeof(int) * nc);
		drands = malloc(sizeof(double) * nc);
		vals   = malloc(sizeof(sim_vals));

		rands  = gen_rand_arr(seed, mul, inc, mod, nc);
		drands = adjust_rands_range(mod, nc, low, up, rands);
		crands = calc_arrival_times(MINUTE, a, nc, drands);
		srands = calc_service_times(MINUTE, s, nc, drands);

		vals -> client_num = nc;
		vals -> server_num = ns;
		vals -> client_time = crands;
		vals -> server_time = srands;
		vals -> lock = &lock;
		vals -> client_threads = malloc(sizeof(pthread_t) * nc);
		vals -> server_threads = malloc(sizeof(pthread_t) * ns);

		start_simulation(vals);
	}
	else
	{
		printf(ERR_MSG);
	}
}

void start_simulation(sim_vals* vals)
{
	pthread_t client_gen;
	pthread_create(&client_gen, NULL, client_generator, (void*)vals);
	pthread_join(client_gen, NULL);
}

void* client_generator(void* args)
{
	sim_vals* vals = (sim_vals*)args;

	for(int i=0; i<vals -> client_num; i++)
	{
		sleep(vals -> client_time[i] * TIME_SHORTENER);
		pthread_create(&(vals -> client_threads[i]), NULL, client, (void*)vals);
	}
	return NULL;
}
	
void* client(void* args)
{
	sim_vals* vals = (sim_vals*)args;
	int client_id = vals -> clients_arrived;

	printf(CLIENT_ARRIVE_MSG, get_time(), client_id);
	pthread_mutex_lock(vals -> lock);
		vals -> clients_arrived++;
	pthread_mutex_unlock(vals -> lock);
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
