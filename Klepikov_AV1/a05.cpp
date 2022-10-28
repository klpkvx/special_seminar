#include "tasks.h"

int
main (int argc, char *argv[])
{
  int task = 5;
  int n = 0, p = 0, s = 0, k = 0;
  double t = 0.0;
  double *array = NULL;
  char *filename = 0;

  if (!(((argc == 5) || (argc == 6)) && (sscanf (argv[1], "%d", &k) == 1)
        && (sscanf (argv[2], "%d", &n) == 1) && (n > 0)
        && (sscanf (argv[3], "%d", &p) == 1) && (p >= 0)
        && (sscanf (argv[4], "%d", &s) == 1) && (s >= 0) && (s <= 6)))
    {
      fprintf (stdout, "Usage: %s k n p s\n", argv[0]);
      return -1;
    }

  if (argc == 6)
    {
      if (s == 0)
        filename = argv[5];
      else
        {
          fprintf (stdout, "Usage: %s k n p 0 filename\n", argv[0]);
          return -1;
        }
    }

  array = (double *)(malloc (n * sizeof (double)));

  if (!array)
    {
      fprintf (stderr, "Cannot allocate memory!\n");
      return -2;
    }

  if (filename)
    {
      int init_error = read_array (array, n, filename);

      if (init_error < 0)
        {
          free (array);
          return -3;
        }
    }
  else
    init_array (array, n, s);

  fprintf (stdout, "Before:\n");
  print_array (array, n, p);

  t = clock ();
  task05 (array, n, k);
  t = (clock () - t) / CLOCKS_PER_SEC;

  fprintf (stdout, "After:\n");
  print_array (array, n, p);

  free (array);
  fprintf (stdout, "%s : Task = %d Elapsed = %.2f\n", argv[0], task, t);

  return 0;
}