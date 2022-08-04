#include "mystatistics.h"

double calc_davg(int argc, double *arr) 
{
	double *tmp = arr; 
	double cnt = 0; 

	for (int i=0; i<argc; i++) {
		cnt+=*tmp;
		tmp++;
	}

	return cnt/argc;
}

double calc_iavg(int argc, int *arr) 
{
	int *tmp = arr; 
	double cnt = 0; 

	for (int i=0; i<argc; i++) {
		cnt+=*tmp;
		tmp++;
	}

	return cnt/(double)argc;
}

double calc_dmedian(int argc, double *arr) 
{
	if(argc%2==1)
	{
		return arr[argc/2];
	}
	else
	{
		// Sums are due to the array starting at 0
		return (arr[(argc/2)-1] + arr[(argc/2)])/2;
	}
}

int calc_imedian(int argc, int *arr) 
{
	if(argc%2==1)
	{
		return arr[argc/2];
	}
	else
	{
		// Sums are due to the array starting at 0
		return (arr[(argc/2)-1] + arr[(argc/2)])/2;
	}
}

double calc_dmode(int argc, double *arr)
{
	double tmp_num = *arr;
	double mode = tmp_num;
	int cnt = 1;
	int cnt_max = 1;

	for (int i=1; i<argc+1; i++)
	{
		if (tmp_num == arr[i]) 
		{
			cnt++;
		}
		else
		{
			if(cnt > cnt_max) 
			{
				cnt_max = cnt;
				mode = tmp_num;
			}
			cnt = 1;
			tmp_num = arr[i];
		}
	}

	return mode;
}

int calc_imode(int argc, int *arr)
{
	int tmp_num = *arr;
	int mode = tmp_num;
	int cnt = 1;
	int cnt_max = 1;

	for (int i=1; i<argc+1; i++)
	{
		if (tmp_num == arr[i]) 
		{
			cnt++;
		}
		else
		{
			if(cnt > cnt_max) 
			{
				cnt_max = cnt;
				mode = tmp_num;
			}
			cnt = 1;
			tmp_num = arr[i];
		}
	}

	return mode;
}

double calc_dvariance(double avg, int argc, double *arr)
{
	double cnt = 0;
	for(int i=0; i<argc; i++)
	{
		cnt+=pow((arr[i]-avg), 2);
	}
	return cnt/((double)argc-1);
}

double calc_ivariance(double avg, int argc, int *arr)
{
	double cnt = 0;
	for(int i=0; i<argc; i++)
	{
		cnt+=pow((arr[i]-avg), 2);
	}
	return cnt/((double)argc-1);
}

double calc_stdev(double variance)
{
	return sqrt(variance);
}

double calc_rel_freq(double element, double element_number)
{
	return element/element_number;
}

double* calc_abs_freq_darr(int arrnum_argc, int arrsrc_argc, double *arrnum, double *arrsrc) 
{
	double *abs_freq = malloc(sizeof(double)*arrnum_argc);
	for(int i=0; i<arrnum_argc; i++)
	{
		abs_freq[i] = count_num_in_arr(arrnum[i], arrsrc_argc, arrsrc);
	}
	return abs_freq;
}

double* calc_abs_freq_ac_darr(int argc, double *arr_freq) 
{
	double *abs_freq_ac = malloc(sizeof(double)*argc);
	abs_freq_ac[0] = arr_freq[0];
	for(int i=1; i<argc; i++)
	{
		abs_freq_ac[i] += abs_freq_ac[i-1] + arr_freq[i];
	}
	return abs_freq_ac;
}

double* calc_rel_freq_darr(double element_num, int argc, double *arr_freq_ac) 
{
	double *rel_freq_arr = malloc(sizeof(double)*argc);
	for(int i=0; i<argc; i++)
	{
		rel_freq_arr[i] = calc_rel_freq(arr_freq_ac[i], element_num);
	}
	return rel_freq_arr;
}

double* calc_rel_freq_ac_darr(int argc, double *arr_relfreq) 
{
	double *rel_freq_arr_ac = malloc(sizeof(double)*argc);
	rel_freq_arr_ac[0] = arr_relfreq[0];
	for(int i=1; i<argc; i++)
	{
		rel_freq_arr_ac[i] += rel_freq_arr_ac[i-1] + arr_relfreq[i];
	}
	return rel_freq_arr_ac;
}
