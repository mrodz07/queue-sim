
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
	pthread_t sim;

  read_gen_without_num(&seed, &mul, &inc, &mod);
	read_queue(&nc, &ns, &a, &s);

	if(a < (s*ns) && a > 0)
	{
		rands  = malloc(sizeof(int) * nc);
		drands = malloc(sizeof(double) * nc);

		rands  = gen_rand_arr(seed, mul, inc, mod, nc);
		drands = adjust_rands_range(mod, nc, low, up, rands);
		crands = calc_arrival_times(MINUTE, a, nc, drands);
		srands = calc_service_times(MINUTE, s, nc, drands);

		client_num = nc;
		server_num = ns; 
		client_time = crands;
		server_time = srands;

		pthread_create(&sim, NULL, start_simulation, NULL);
		pthread_join(sim, NULL);
	}
	else
	{
		printf(ERR_MSG);
	}
}

void* start_simulation()
{
	pthread_t client_gen;
	pthread_t server_gen;

	pthread_create(&client_gen, NULL, client_generator, NULL);
	pthread_join(client_gen, NULL);

	pthread_create(&server_gen, NULL, server_generator, NULL);
	pthread_join(server_gen, NULL);

	return NULL;
}

void* client_generator()
{
	client_arr = calloc(client_num, sizeof(client));

	for(int i=0; i<client_num; i++)
	{
		client_arr[i].client_id			= i; 
		client_arr[i].is_finished		= 0;
		client_arr[i].waiting_time	= client_time[i];
		
		pthread_create(&(client_arr[i].client_thread), NULL, client_main, (void*)&client_arr[i]);
	}

	return NULL;
}

void* server_generator()
{
	server_arr = calloc(server_num, sizeof(server));
	
	for(int i=0; i<server_num; i++)
	{
		server_arr[i].server_id				= i;
		server_arr[i].response_times	= server_time;
		server_arr[i].client_num			= client_num;

		pthread_create(&(server_arr[i].server_thread), NULL, server_main, (void*)&server_arr[i]);
	}

	while(finished < client_num) {
	}

	return NULL;
}
	
void* client_main(void* args)
{
	client* vals = (client*)args;
	
	pthread_mutex_lock(&c_lock);
		sleep(vals -> waiting_time * TIME_SHORTENER);
		printf(CLIENT_ARRIVE_MSG, get_time(), vals -> client_id);
		vals -> avail = 1;
	pthread_mutex_unlock(&c_lock);

	sleep((TIME_WAIT * TIME_SHORTENER) / TIME_NOTICE_DIVISOR);

	while(vals -> attending == 0)
	{
		pthread_mutex_lock(&t_lock);
			sleep(TIME_WAIT * TIME_SHORTENER);
			if(vals -> attending == 0)
				printf(CLIENT_WAITING_MSG, get_time(), vals -> client_id);
		pthread_mutex_unlock(&t_lock);
	}

	return NULL;
}

void* server_main(void* args)
{
	server* vals = (server*)args;
	int tmp_client;

	while(finished < client_num)
	{
		pthread_mutex_lock(&s_lock);
		if(client_arr[clients_served].avail) {
				printf(SERVER_START_MSG, get_time(), client_arr[clients_served].client_id, vals -> server_id);
				client_arr[clients_served].attending = 1;
				tmp_client = clients_served;
				clients_served++;
			pthread_mutex_unlock(&s_lock);

			sleep(server_time[tmp_client] * TIME_SHORTENER);

			printf(SERVER_END_MSG, get_time(), client_arr[tmp_client].client_id, vals -> server_id);
			client_arr[tmp_client].is_finished = 1;

			pthread_mutex_lock(&v_lock);
				finished++;
			pthread_mutex_unlock(&v_lock);
			
		}
		pthread_mutex_unlock(&s_lock);
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

	for(int i=0; i<argc; i++) {
	//	if(i>0)
	//		adjarr[i] = adjarr[i-1] + ((time/a) + (range * rands[i]));
	//  else
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
