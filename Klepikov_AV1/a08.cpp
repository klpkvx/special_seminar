#include "tasks.h"

int
main (int argc, char *argv[])
{
  double *a = NULL, *b = NULL, *c = NULL;
  double t;
  int n1 = 0, p1 = 0, s1 = 0;
  int n2 = 0, p2 = 0, s2 = 0;
  int number_elements = 0;
  int init_error = 0;

  char *filename1 = NULL;
  char *filename2 = NULL;

  switch (argc)
    {
    case 7:
      if (!((sscanf (argv[1], "%d", &n1) == 1) && (n1 > 0)
            && (sscanf (argv[2], "%d", &p1) == 1) && (p1 >= 0)
            && (sscanf (argv[3], "%d", &s1) == 1) && (s1 >= 0) && (s1 <= 6)
            && (sscanf (argv[4], "%d", &n2) == 1) && (n2 > 0)
            && (sscanf (argv[5], "%d", &p2) == 1) && (p2 >= 0)
            && (sscanf (argv[6], "%d", &s2) == 1) && (s2 >= 0) && (s2 <= 6)))
        {
          fprintf (stdout, "Usage: %s n1 p1 s1 filename1 n2 p2 s2 filename2\n",
                   argv[0]);
          return 1;
        }
      break;

    case 8:
      if (!(sscanf (argv[3], "%d", &s1) == 1) && (s1 >= 0) && (s1 <= 6))
        {
          fprintf (stdout, "Usage: %s n1 p1 s1 filename1 n2 p2 s2 filename2\n",
                   argv[0]);
          return 1;
        }
      if (s1 != 0)
        {
          if (!((sscanf (argv[1], "%d", &n1) == 1) && (n1 > 0)
                && (sscanf (argv[2], "%d", &p1) == 1) && (p1 >= 0)
                && (sscanf (argv[4], "%d", &n2) == 1) && (n2 > 0)
                && (sscanf (argv[5], "%d", &p2) == 1) && (p2 >= 0)
                && (sscanf (argv[6], "%d", &s2) == 1) && (s2 >= 0)
                && (s2 <= 6)))
            {
              fprintf (stdout,
                       "Usage: %s n1 p1 s1 filename1 n2 p2 s2 filename2\n",
                       argv[0]);
              return 1;
            }
          filename2 = argv[7];
        }
      else
        {
          if (!((sscanf (argv[1], "%d", &n1) == 1) && (n1 > 0)
                && (sscanf (argv[2], "%d", &p1) == 1) && (p1 >= 0)
                && (sscanf (argv[5], "%d", &n2) == 1) && (n2 > 0)
                && (sscanf (argv[6], "%d", &p2) == 1) && (p2 >= 0)
                && (sscanf (argv[7], "%d", &s2) == 1) && (s2 >= 0)
                && (s2 <= 6)))
            {
              fprintf (stdout,
                       "Usage: %s n1 p1 s1 filename1 n2 p2 s2 filename2\n",
                       argv[0]);
              return 1;
            }
          filename1 = argv[4];
        }
      break;

    case 9:
      if (!((sscanf (argv[1], "%d", &n1) == 1) && (n1 > 0)
            && (sscanf (argv[2], "%d", &p1) == 1) && (p1 >= 0)
            && (sscanf (argv[3], "%d", &s1) == 1) && (s1 >= 0) && (s1 <= 6)
            && (sscanf (argv[5], "%d", &n2) == 1) && (n2 > 0)
            && (sscanf (argv[6], "%d", &p2) == 1) && (p2 >= 0)
            && (sscanf (argv[7], "%d", &s2) == 1) && (s2 >= 0) && (s2 <= 6)))
        {
          fprintf (stdout, "Usage: %s n1 p1 s1 filename1 n2 p2 s2 filename2\n",
                   argv[0]);
          return 1;
        }
      filename1 = argv[4];
      filename2 = argv[8];
      break;
    default:
      fprintf (stdout, "Usage: %s n1 p1 s1 filename1 n2 p2 s2 filename2\n",
               argv[0]);
      return 1;
    }

  a = (double *)(malloc (n1 * sizeof (double)));
  if (!a)
    {
      fprintf (stderr, "Cannot allocate memory!\n");
      return 2;
    }

  b = (double *)(malloc (n2 * sizeof (double)));
  if (!b)
    {
      fprintf (stderr, "Cannot allocate memory!\n");
      free (a);
      return 2;
    }

  c = (double *)(malloc ((n1 + n2) * sizeof (double)));
  if (!c)
    {
      fprintf (stderr, "Cannot allocate memory!\n");
      free (a);
      free (b);
      return 2;
    }

  if (filename1)
    {
      init_error = read_array (a, n1, filename1);
      if (init_error < 0)
        {
          free (a);
          free (b);
          free (c);
          return 3;
        }
    }
  else
    init_array (a, n1, s1);

  if (filename2)
    {
      init_error = read_array (b, n2, filename2);
      if (init_error < 0)
        {
          free (a);
          free (b);
          free (c);
          return 3;
        }
    }
  else
    init_array (b, n2, s2);

  fprintf (stdout, "Array a\n");
  print_array_a (a, n1, p1);

  fprintf (stdout, "Array b\n");
  print_array_b (b, n2, p2);

  t = clock ();
  number_elements = task08 (a, b, c, n1, n2);
  t = (clock () - t) / CLOCKS_PER_SEC;
  fprintf (stdout, "Array c\n");
  print_array_c (c, number_elements, p1 + p2);

  free (a);
  free (b);
  free (c);
  t = (clock () - t) / CLOCKS_PER_SEC;
  printf ("\nf_lapsed = %.2f\n", t);

  return 0;
}