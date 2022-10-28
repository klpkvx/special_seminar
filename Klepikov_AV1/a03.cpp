
#include "tasks.h"

int
main (int argc, const char *argv[])
{
  int task = 3;
  double t = 0.0;
  int res = 0;

  if (argc != 2)
    {
      fprintf (stderr, "Usage: %s filename\n", argv[0]);
      return -1;
    }

  t = clock ();
  res = task03 (argv[1]);
  t = (clock () - t) / CLOCKS_PER_SEC;

  fprintf (stdout, "%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0],
           task, res, t);

  return 0;
}