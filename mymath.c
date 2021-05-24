#include "mymath.h"

int countprimes(int maxnum)
{
  int prime_count = 0;
  int not_prime = 0;

  for(int n=1; n<=maxnum; n++)
  {
    // El numero al no ser divisible sobre 2 se truncara hacia cero, ya no podremos llegar a el, tiene mas posibilidad de ser primo
    for(int i=2; i<=n/2; i++)
    {
      if(n%i == 0)
      {
        not_prime++;
        i = n/2;
      }
    }
    if(!not_prime && n!=1)
      prime_count++;
    else
      not_prime = 0;
  }

  return prime_count;
}

int* primearr(int maxnum)
{
  int arr_size  = 0;
  int arr_count = 0;
  int not_prime = 0;
  int *primearr = NULL;

  arr_size = countprimes(maxnum);
  primearr = malloc(sizeof(int) * arr_size); 

  for(int n=1; n<=maxnum; n++)
  {
    for(int i=2; i<=n/2; i++)
    {
      if(n%i == 0)
      {
        not_prime++;
        i = n/2;
      }
    }
    if(!not_prime && n!=1)
    {
      primearr[arr_count] = n;
      arr_count++;
    }
    else
    {
      not_prime = 0; 
    }
  }

  return primearr;
}

int greatestcommondivisor(int n1, int n2)
{
  if(n1 == 0)
    return n2;
  return greatestcommondivisor(n2%n1, n1);
}
