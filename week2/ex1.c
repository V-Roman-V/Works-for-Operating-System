#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
  int    i = INT_MAX;
  float  f = FLT_MAX;
  double d = DBL_MAX;
  printf("Integer: size = %lu byte, max_value = %d\n",sizeof(int   ),i);
  printf("Float  : size = %lu byte, max_value = %e\n",sizeof(float ),f);
  printf("Double : size = %lu byte, max_value = %e\n",sizeof(double),d);
  return 0;
}
