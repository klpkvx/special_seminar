
#include "tasks.h"

int
main (int argc, const char *argv[])
{
  int task = 4;
  double t = 0.0, d = 0.0;
  int res = 0; /* number elements in input file */

  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s filename\n", argv[0]);
      return -1;
    }

  t = clock ();
  res = task04 (argv[1], &d);
  t = (clock () - t) / CLOCKS_PER_SEC;

  if (res < 0)
    {
      fprintf (stderr, "ERROR:%d\n", res);
      return -1;
    }

  printf ("%s : Task = %d Length = %d Result = %e Elapsed = %.2f\n", argv[0],
          task, res, d, t);

  return 0;
}