#include "tasks.h"
int
main (int argc, char *argv[])
{
  int task = 2;
  double (*function) (double) = 0;
  double (*derivative) (double) = 0;
  double x0 = 0, eps = 0;
  double x = 0, solution_check = 0, t = 0;
  int k = 0, it = 0;
  if (!(argc == 4 && sscanf (argv[1], "%lf", &x0) == 1
        && sscanf (argv[2], "%lf", &eps) == 1
        && sscanf (argv[3], "%d", &k) == 1))
    {
      printf ("Usage: %s x eps k\n", argv[0]);
      return -1;
    }
  switch (k)
    {
    case 0:
      function = f0;
      derivative = d0;
      break;
    case 1:
      function = f1;
      derivative = d1;
      break;
    case 2:
      function = f2;
      derivative = d2;
      break;
    case 3:
      function = f3;
      derivative = d3;
      break;
    case 4:
      function = f4;
      derivative = d4;
      break;
    case 5:
      function = f5;
      derivative = d5;
      break;
    case 6:
      function = f6;
      derivative = d6;
      break;
    default:
      printf ("Usage: %s a b eps k\n", argv[0]);
      return -2;
    }

  t = clock ();
  it = task05 (function, derivative, x0, eps, &x);
  t = (clock () - t) / CLOCKS_PER_SEC;
  if (it < 0 || (k == 0 && eps <= 1))
    {
      printf ("Solution is not exist!\n");
      return -3;
    }
  solution_check = (*function) (x);

  printf ("%s : Task = %d X = %e Res = %e Its = %d Count = %d T = %.2f\n",
          argv[0], task, x, solution_check, it, get_count (), t);
  return 0;
}