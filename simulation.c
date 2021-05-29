
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
	pthread_t sim;
	pthread_mutex_t lockc = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t locks = PTHREAD_MUTEX_INITIALIZER;

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
		vals -> c_lock = &lockc;
		vals -> s_lock = &locks;
		vals -> clients_sirved = 0;

		pthread_create(&sim, NULL, start_simulation, (void*)vals);
		pthread_join(sim, NULL);
	}
	else
	{
		printf(ERR_MSG);
	}
}

void* start_simulation(void* args)
{
	sim_vals* vals = (sim_vals*)args;

	pthread_t client_gen;
	pthread_t server_gen;
	server_gen_vals sgv;

	pthread_create(&client_gen, NULL, client_generator, (void*)vals);
	pthread_join(client_gen, NULL);

	sgv.simu_vals = vals;
	sgv.client_threads = vals -> client_arr;

	pthread_create(&server_gen, NULL, server_generator, (void*)&sgv);
	pthread_join(server_gen, NULL);

	return NULL;
}

void* server_generator(void* args)
{
	server_gen_vals* vals = (server_gen_vals*)args;
	server_thread_vals* server_vals;
	server*		servers;
	servers = malloc(sizeof(server) * vals -> simu_vals -> server_num);
	server_vals = malloc(sizeof(server_thread_vals) * vals -> simu_vals -> client_num);
	
	for(int i=0; i<vals -> simu_vals -> server_num; i++)
	{
		servers[i].server_id = i;
		servers[i].client_threads = vals -> client_threads;
		servers[i].attend = &server_attend;
		servers[i].response_times = vals -> simu_vals -> server_time;
		servers[i].lock = vals -> simu_vals -> s_lock;
		servers[i].client_num = vals -> simu_vals -> client_num;
		servers[i].simu_vals = vals -> simu_vals;

		server_vals[i].server_id = &servers[i].server_id;
		server_vals[i].clients_served = &servers[i].simu_vals->clients_sirved;
		server_vals[i].client_threads = servers[i].client_threads;
		server_vals[i].response_times = servers[i].response_times;
		server_vals[i].lock = servers[i].lock;
		server_vals[i].attend = servers[i].attend;
		server_vals[i].client_num = &servers[i].client_num;
		server_vals[i].simu_vals = servers[i].simu_vals;

		pthread_create(&(servers[i].server_thread), NULL, server_main, (void*)&server_vals[i]);
	}

	while(vals -> simu_vals -> clients_sirved < vals -> simu_vals -> client_num) {
	}

	return NULL;
}

void* client_generator(void* args)
{
	sim_vals* vals = (sim_vals*)args;
	client* clients;
	client_thread_vals* client_vals;
	vals -> client_arr = malloc(sizeof(client) * vals -> client_num);
	clients = vals -> client_arr;
	client_vals = malloc(sizeof(client_thread_vals) * vals -> client_num);

	for(int i=0; i<vals -> client_num; i++)
	{
		clients[i].client_id = i; 
		clients[i].is_finished = 0;
		clients[i].waiting_time = vals -> client_time[i];
		clients[i].wait = &client_wait;
		clients[i].set_avail = &client_set_avail;
		clients[i].lock = vals -> c_lock;
		
		client_vals[i].client_id = &clients[i].client_id;
		client_vals[i].is_finished = &clients[i].is_finished;
		client_vals[i].avail = &clients[i].avail;
		client_vals[i].waiting_time = &clients[i].waiting_time;
		client_vals[i].lock = clients[i].lock;

		pthread_create(&(clients[i].client_thread), NULL, client_main, (void*)&client_vals[i]);
	}

	return (void *)clients;
}
	
void* client_main(void* args)
{
	client_thread_vals* vals = (client_thread_vals*)args;

	client_wait(*vals -> waiting_time);
	printf(CLIENT_ARRIVE_MSG, get_time(), *vals -> client_id);
	pthread_mutex_lock(vals -> lock);
		*vals -> avail = 1;
	pthread_mutex_unlock(vals -> lock);

	sleep((TIME_WAIT * TIME_SHORTENER) / TIME_NOTICE_DIVISOR);

	while(*vals -> is_finished == 0)
	{
		pthread_mutex_lock(vals -> lock);
			sleep(TIME_WAIT * TIME_SHORTENER);
			printf(CLIENT_WAITING_MSG, get_time(), *vals -> client_id);
		pthread_mutex_unlock(vals -> lock);
	}

	return NULL;
}

void client_wait(double t)
{
	sleep(t * TIME_SHORTENER);
}

void client_set_avail(int a)
{
	a = 1;
}

void* server_main(void* args)
{
	server_thread_vals* vals = (server_thread_vals*)args;

	while(*vals -> clients_served < *vals -> client_num)
	{
		pthread_mutex_lock(vals -> lock);
		if(vals -> client_threads[*vals -> clients_served].avail)
		{
			//pthread_mutex_lock(vals -> lock);
			printf(SERVER_START_MSG, get_time(), vals -> client_threads[*vals -> clients_served].client_id, *vals -> server_id);
			//pthread_mutex_unlock(vals -> lock);

			sleep(vals -> response_times[*vals -> clients_served] * TIME_SHORTENER);

			//pthread_mutex_lock(vals -> lock);
			printf(SERVER_END_MSG, get_time(), vals -> client_threads[*vals -> clients_served].client_id, *vals -> server_id);
			vals -> client_threads[*vals -> clients_served].is_finished = 1;
			//printf("Clients sirved 1: %d\n", *vals -> clients_served);
			*vals -> clients_served = *vals -> clients_served + 1;
			//printf("Clients sirved 2: %d\n", *vals -> clients_served);
			//pthread_mutex_unlock(vals -> lock);
		}
		pthread_mutex_unlock(vals -> lock);
	}

	return NULL;
}

void server_attend(int i)
{
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

	for(int i=0; i<argc; i++) {
		if(i>0)
			adjarr[i] = adjarr[i-1] + ((time/a) + (range * rands[i]));
		else
			adjarr[i] = ((time/a) + (range * rands[i]));
	}

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
