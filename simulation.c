
#include "rands.h"

int main() 
{
  int seed, mul, inc, mod, num;
  read_gen(&seed, &mul, &inc, &mod, &num);
  printf("%d, %d, %d, %d, %d\n", seed, mul, inc, mod, num);
}
