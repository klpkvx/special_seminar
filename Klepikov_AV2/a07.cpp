#include "tasks.h"

int
main (int argc, const char *argv[])
{
  int task = 7;
  const char *filename_a = NULL, *filename_b = NULL, *string = NULL;
  int res = 0;
  double t = 0;

  if (argc != 4)
    {
      fprintf (stderr, "Usage: %s filename_a filename_b s \n", argv[0]);
      return -1;
    }

  filename_a = argv[1];
  filename_b = argv[2];
  string = argv[3];

  t = clock ();
  res = task05 (filename_a, filename_b, string);
  t = (clock () - t) / CLOCKS_PER_SEC;

  if (res < 0)
    return res;

  printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res,
          t);
  return 0;
}