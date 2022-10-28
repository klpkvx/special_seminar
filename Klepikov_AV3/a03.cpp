#include "tasks.h"

int
main (int argc, char *argv[])
{
  int task = 3;
  int n = 0, error = 0; // число узлов
  double t = 0, r = 0, x0 = 0;
  double *x = 0, *y = 0, *d = 0;

  if (argc != 4
      || !(sscanf (argv[1], "%lf", &x0) == 1
           && sscanf (argv[2], "%d", &n) == 1))
    {
      fprintf (stderr, "Usage: %s x0 n filename\n", argv[0]);
      return -1;
    }

  x = (double *)malloc (n * sizeof (double));
  if (!x)
    {
      fprintf (stderr, "Cannot allocate!\n");
      return -2;
    }

  y = (double *)malloc (n * sizeof (double));
  if (!y)
    {
      free (x);
      fprintf (stderr, "Cannot allocate memory!\n");
      return -2;
    }

  d = (double *)malloc (n * sizeof (double));
  if (!d)
    {
      free (x);
      free (y);
      fprintf (stderr, "Cannot allocate!\n");
      return -2;
    }

  error = read_array_3 (x, y, d, n, argv[3]);
  if (error < 0)
    {
      printf ("we here\n");
      free (x);
      x = 0;
      free (y);
      y = 0;
      free (d);
      d = 0;
      return error;
    }

  error = check_array (x, n);
  if (error < 0)
    {
      printf ("Error!\n");
      free (x);
      free (y);
      free (d);
      return -1;
    }

  t = clock ();
  r = task03 (x0, n, x, y, d);
  t = (clock () - t) / CLOCKS_PER_SEC;

  printf ("%s : Task = %d Result = %e Elapsed = %.2f\n", argv[0], task, r, t);

  free (x);
  free (y);
  free (d);
  return 0;
}