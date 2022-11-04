#include "func.h"
#include "tasks.h"

int main(int argc, char *argv[])
{
  int task = 4;
  double a = 0, b = 0;
  double eps = 0, t = 0;
  int k = 0;
  double (*function)(double), res = 0;
  int count = 0;
  double (*arr_func[])(double) = {f0, f1, f2, f3, f4, f5, f6};
  if (!(argc == 5 && sscanf(argv[1], "%lf", &a) == 1 && sscanf(argv[2], "%lf", &b) == 1 && sscanf(argv[3], "%lf", &eps) == 1 && eps > 0 && sscanf(argv[4], "%d", &k) == 1) && k >= 0 && k <= 6)
  {
    printf("Usage: %s a b eps k\n", argv[0]);
    return 1;
  }

  function = arr_func[k];
  t = clock();
  count = task04(function, a, b, eps, &res);
  t = (clock() - t) / CLOCKS_PER_SEC;
  printf("%s : Task = %d Res = %e N = %d Count = %d T = %.2f\n", argv[0],
         task, res, count, get_count(), t);
  return 0;
}