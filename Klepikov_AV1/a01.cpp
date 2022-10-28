#include "tasks.h"

int
main (int argc, const char *argv[])
{
  int task = 1;
  unsigned int k = 0;
  double t = 0.0;
  int res = 0;

  if (argc != 3 || sscanf (argv[2], "%u", &k) != 1)
    {
      fprintf (stderr, "Usage: %s file k\n", argv[0]);
      return -1;
    }

  t = clock ();
  res = task01 (argv[1], k);
  t = (clock () - t) / CLOCKS_PER_SEC;

  fprintf (stdout, "%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0],
           task, res, t);

  return 0;
}