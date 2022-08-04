#include "myutils.h"

int count_num_in_arr(int num, int argc, double *arr)
{
	int cnt = 0;

	for (int i=0; i<argc; i++)
	{
		if (num == arr[i]) 
		{
			cnt++;
		}
	}

	return cnt;
}

double* copy_arr(int argc, char **argv) 
{
	// Save an extra for '\0'
	double *arr = malloc((1+argc)*sizeof(double));
	double *beg = arr;

	for (int i=0; i<argc; i++) 
	{
		*arr = strtod(* (argv + i), NULL);
		arr++;
	}

	arr = beg;
	return arr; 
}

char** read_str_arr(int lines, int argc) 
{
	char **str_arr = malloc(lines * sizeof(char*));

	for(int i=0; i<lines; i++) 
	{
		// An extra space to include the null character
		str_arr[i] = malloc(argc+1);
		fgets(str_arr[i], argc+1, stdin);
	}
	
	return str_arr;
}

char* read_str(int argc)
{
	char *str = malloc(argc);
	// An extra space to include the null character
	fgets(str, argc+1, stdin);
	return str;
}

double read_num()
{
	char *str = malloc((int)DBL_MAX);

	fgets(str, (int)DBL_MAX-1, stdin);
	return strtod(str, NULL);
}

int find_pow_ten(double n) 
{
	int cnt;

	while(n/10 > 0)
	{
		n = n/10;
		cnt++;
	}
	return cnt;
}

int search_char(char c, int argc, char *arr)
{ 
	int i = 0; 
	int found = 0; 

	while(!found && i< argc)
	{ 
			if(arr[i] == c)
					found++; 
			else
					i++; 
	}
	return i; 
}

int search_int(int b, int e, int num, int* arr)
{ 
	int i = b; 
	int found = 0; 

	while (!found && i<e)
	{ 
			if (arr[i] == num)
					found++; 
			else
					i++; 
	}
	if (found)
		return i; 
	else
		return -1;
}

int search_int_dup(int argc, int *arr)
{
	int num = -1;

	for (int i = 0; i < argc; i++) {
		for (int j = 0; j < i; j++) {
				if(arr[i] == arr[j])
				{
					num = arr[i];
					i = argc;
					j = i;
				}
		}
	}

	return num;
}

int count_range_in_arr(double dl, double ul, int argc, double *arr)
{
	int cnt = 0;

	for (int i=0; i<argc; i++)
	{
		if(dl == 0.0)
		{
			if (arr[i] >= dl && arr[i] <= ul) 
			{
				cnt++;
			}
		}
		else
		{
			if (arr[i] > dl && arr[i] <= ul) 
			{
				cnt++;
			}
		}
	}


	return cnt;
}

char* make_substring(int b, int e, char *str)
{ 
	int i = 0; 
	char *sub_str = malloc(sizeof(char)*((e-b)+1)); 
	for(i = 0; i<(e-b); i++) { 
			sub_str[i] = str[b+i]; 
	}
	sub_str[i+1] = '\0'; 
	return sub_str;
}

void print_int_arr(char sep, char end, int argc, int *arr)
{
	if (argc > 0)
	{
		for (int i = 0; i < argc; i++) {
			if (i!=argc-1)
				printf("%d%c ", arr[i], sep);
			else
				printf("%d%c", arr[i], end);
		}
	}
	else
		printf("%c", end);
}

void print_str_arr(char sep, char end, int argc, char **arr)
{
	if (argc > 0)
	{
		for (int i = 0; i < argc; i++) {
			if (i != argc-1)
				printf("%s%c ", arr[i], sep);
			else
				printf("%s%c", arr[i], end);
		}
	}
	else
		printf("%c", end);
}

void print_double_arr(char sep, char end, int argc, double *arr)
{
	if (argc > 0)
	{
		for (int i = 0; i < argc; i++) {
			if (i != argc-1)
				printf("%f%c ", arr[i], sep);
			else
				printf("%f%c", arr[i], end);
		}
	}
	else
		printf("%c", end);
}

void print_str_pad(int pad, char *str)
{
  printf("%*s%s", pad, "", str);
}
