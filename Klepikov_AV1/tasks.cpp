#include "tasks.h"
#include "math.h"
#include "stdio.h"

int
euclidean_algorithm (int a, int b)
{
  while (a != b)
    {
      if (a > b)
        {
          a -= b;
        }
      else
        {
          b -= a;
        }
    }
  return a;
}

double
f (int s, int n, int i)
{
  i++;
  switch (s)
    {
    case 1:
      return (i);
    case 2:
      return (n - i);
    case 3:
      return (i / 2);
    case 4:
      return (n - i / 2);
    case 5:
      return (2 * i);
    case 6:
      return (n - 2 * i);
    default:
      return 0;
    }

  return 0;
}

int
read_array (double *array, int n, const char *filename)
{
  FILE *input = NULL;
  input = fopen (filename, "rt");

  if (!input)
    {
      fprintf (stderr, "Cannot open %s!\n", filename);
      return -1;
    }

  for (int i = 0; i < n; i++)
    {
      if (fscanf (input, "%lf", array + i) != 1)
        {
          if (!feof (input))
            {
              fprintf (stderr, "Cannot read %s!\n", filename);
              fclose (input);
              return -3;
            }

          fprintf (stderr, "Cannot read %s!\n", filename);
          fclose (input);
          return -2;
        }
    }

  fclose (input);
  return 0;
}

void
init_array (double *array, int n, int s)
{
  for (int i = 0; i < n; i++)
    {
      array[i] = f (s, n, i);
    }
}

void
print_array (double *array, int n, int p)
{
  if (p > n)
    p = n;
  for (int i = 0; i < p; i++)
    {
      fprintf (stdout, "array[%d] = %lf\n", i, *array);
      array++;
    }
}

void
print_array_a (double *a, int n, int p)
{
  if (p > n)
    p = n;
  for (int i = 0; i < p; i++)
    {
      fprintf (stdout, "a[%d] = %lf\n", i, *a);
      a++;
    }
}

void
print_array_b (double *a, int n, int p)
{
  if (p > n)
    p = n;
  for (int i = 0; i < p; i++)
    {
      fprintf (stdout, "b[%d] = %lf\n", i, *a);
      a++;
    }
}

void
print_array_c (double *a, int n, int p)
{
  if (p > n)
    p = n;
  for (int i = 0; i < p; i++)
    {
      fprintf (stdout, "c[%d] = %lf\n", i, *a);
      a++;
    }
}

int
task03 (const char *filename)
{
  FILE *input = NULL;
  int result = 0;
  int count = 0;
  double a_1 = 0, a_2 = 0, a_3 = 0;
  int is_arithmetical = 1, is_geometrical = 1, is_constant = 1;
  input = fopen (filename, "rt");

  if (!input)
    {
      fprintf (stderr, "cannot open %s!\n", filename);
      return 0;
    }

  if (fscanf (input, "%lf", &a_1) != 1)
    {
      if (!feof (input))
        {
          fprintf (stderr, "Cannot read %s\n", filename);
          fclose (input);
          return -1;
        }
      else
        {
          fprintf (stderr, "File is empty! %s\n", filename);
          fclose (input);
          return -2;
        }
    }

  count++;

  if (fscanf (input, "%lf", &a_2) != 1)
    {
      if (!feof (input))
        {
          fprintf (stderr, "Cannot read %s\n", filename);
          fclose (input);
          return -1;
        }
      else
        {
          fclose (input);
          return 4;
        }
    }
  count++;

  while (fscanf (input, "%lf", &a_3) == 1)
    {
      count++;

      if (is_arithmetical && !(fabs (a_2 - (a_1 + a_3) * 0.5) < 1e-14))
        is_arithmetical = 0;

      if (is_geometrical && !(fabs (a_2 * a_2 - a_1 * a_3) < 1e-14))
        is_geometrical = 0;

      if (is_constant
          && !(fabs (a_1 - a_2) < 1e-14 && fabs (a_2 - a_3) < 1e-14))
        is_constant = 0;

      if (!is_arithmetical && !is_geometrical && !is_constant)
        {
          fclose (input);
          return 0;
        }

      a_1 = a_2;
      a_2 = a_3;
    }

  if (!feof (input))
    {
      fprintf (stderr, "Cannot read %s\n", filename);
      fclose (input);
      return -1;
    }
  fclose (input);

  if (count < 3)
    return 4;

  if (is_arithmetical && is_geometrical && is_constant)
    result = 3;
  else
    {
      if (is_arithmetical && is_geometrical && !is_constant)
        result = 4;
      else
        {
          if (is_arithmetical && !is_geometrical && is_constant)
            result = 3;
          else
            {
              if (is_arithmetical && !is_geometrical && !is_constant)
                result = 1;
              else
                {
                  if (!is_arithmetical && is_geometrical && is_constant)
                    result = 3;
                  else
                    {
                      if (!is_arithmetical && is_geometrical && !is_constant)
                        result = 2;
                      else
                        {
                          if (!is_arithmetical && !is_geometrical
                              && is_constant)
                            result = 3;
                        }
                    }
                }
            }
        }
    }

  switch (result)
    {
    case 1: /* arithmetic progression */ // b_n = (a_{n-1} + a_{n+1} )* 0.5
      return 1;
    case 2: /*geometric progression  */ // b_n^2=b_{n-1}*b_{n+1}
      return 2;
    case 3: /* constant progression */ // b_n == b_n+1
      return 3;
    case 4: /*not enough elements to make a decision */ // < 2 elements or //
                                                        // arithmetic and
                                                        // geometric
      return 4;
    default: /* another case */ // Если >=3 elements and !arithmetic &&
                                // _geometric && !const

      return 0;
    }
}

int
task04 (const char *filename, double *d)
{
  FILE *input = NULL;
  int count = 0;
  double sum = 0.0, sum_square = 0.0, avg_arith = 0.0;
  double tmp = 0;
  input = fopen (filename, "rt");

  if (!input)
    {
      fprintf (stderr, "Cannot open %s!\n", filename);
      return -1;
    }

  if (fscanf (input, "%lf", &tmp) != 1)
    {
      if (!feof (input))
        {
          fprintf (stderr, "Cannot read %s\n", filename);
          fclose (input);
          return -2;
        }
      fprintf (stderr, "File is empty! %s\n", filename);
      fclose (input);
      return -3;
    }

  count++;
  sum = sum + tmp;
  sum_square = sum_square + tmp * tmp;

  while (fscanf (input, "%lf", &tmp) == 1)
    {
      sum = sum + tmp;
      sum_square = sum_square + tmp * tmp;
      count++;
    }

  if (!feof (input))
    {
      fprintf (stderr, "Cannot read %s\n", filename);
      fclose (input);
      return -3;
    }

  fclose (input);
  avg_arith = sum / count;
  *d = (count * avg_arith * avg_arith - 2 * avg_arith * sum + sum_square)
       / count;

  return count;
}

int
task05 (double *array, int n, int k)
{
  double *tmp_1 = NULL, *tmp_2 = NULL, *array_new = NULL;
  int number = 0, begin = 0, end = 0;
  double tmp = 0;

  if (k < 0)
    k += n;

  k %= n;

  if (k == 0)
    return 0;

  number = euclidean_algorithm (k, n);
  array_new = array + n - 1;

  for (int i = 0; i < number; i++)
    {
      tmp = *array_new;
      tmp_2 = array_new - k;
      end = i;

      while (tmp_2 != array_new)
        {
          begin = (k + end) % n;
          tmp_1 = array + n - 1 - end;
          tmp_2 = array + n - 1 - begin;

          if (tmp_2 != array_new)
            *tmp_1 = *tmp_2;

          end = begin;
        }

      *tmp_1 = tmp;
      array_new--;
    }

  return 0;
}

int
task06 (double *array, int n, int k)
{
  int len = 0, i = 0, size = 0, count = 0;
  double sum = 0, sum_2 = 0, avg_sum = 0;

  for (i = 0; i < n - 1; i++) // calc sum
    {
      if (array[i] >= array[i + 1])
        {
          sum += array[i];
          len++;
        }
      else
        {
          len++;
          sum += array[i];
          if (len >= k)
            {
              sum_2 += sum;
              count += len;
            }
          sum = 0;
          len = 0;
        }
    }

  if (len > 0)
    {
      len++;
      sum += array[i];
      if (len >= k)
        {
          sum_2 += sum;
          count += len;
        }
      sum = 0;
      len = 0;
    }

  if (count > 0)
    avg_sum = sum_2 / (double)count;

  for (int i = 0; i < n; i++) // delete
    {
      if (array[i] >= avg_sum)
        {
          array[size] = array[i];
          size++;
        }
    }

  return size;
}



int
task07 (double *array, int n, const char *b)
{
  FILE *input = NULL;
  int count = 0;
  int i_0 = 0, i_1 = 0, j_0 = 0, j_1 = 0, k = 0;
  double b_elem = 0;

  input = fopen (b, "rt");
  if (!input)
    {
      fprintf (stderr, "Cannot open file %s\n", b);
      return -1;
    }

  while (fscanf (input, "%lf", &b_elem) == 1)
    {
      if (!(fabs (b_elem - array[i_0]) < 1e-14))
        {
          if (i_0 == 0)
            continue;
          else
            i_1 = i_0;

          for (k = 1; k <= i_1; k++)
            {
              for (j_0 = k, j_1 = 0; j_0 < i_1; j_0++, j_1++)
                if (!(fabs (array[j_0] - array[j_1]) < 1e-14))
                  break;

              if (j_0 != i_1 - 1)
                i_0 = j_1;

              if (fabs (b_elem - array[i_0]) < 1e-14)
                break;
            }

          if (k == i_1 + 1)
            i_0 = 0;
          else
            i_0++;
        }
      else
        i_0++;

      if (i_0 == n)
        {
          count++;
          for (k = 1; k < n; k++)
            {
              for (j_0 = k, j_1 = 0; j_0 < n; j_0++, j_1++)
                if (!(fabs (array[j_0] - array[j_1]) < 1e-14))
                  break;

              if (j_0 == n)
                {
                  i_0 = j_1;
                  break;
                }
            }
          if (k == n)
            i_0 = 0;
        }
    }

  if (!feof (input))
    {
      fprintf (stderr, "Cannot read! %s\n", b);
      fclose (input);
      return -2;
    }

  fclose (input);
  return count;
}

int
task08 (double *a, double *b, double *c, int n1, int n2)
{
  int sum = n1 + n2;
  int i = 0, j = 0;
  int count = 0;

  while ((i < n1) && (j < n2))
    {
      if (a[i] < b[j])
        {
          c[count] = a[i];
          count++;
          i++;
        }
      else
        {
          if (a[i] > b[j])
            {
              c[count] = b[j];
              count++;
              j++;
            }
          else
            {
              c[count] = a[i];
              i++;
              j++;
              count++;
            }
        }
    }

  if (i + j < sum)
    {
      if (i < n1)
        {
          while (i < n1)
            {
              c[count] = a[i];
              i++;
              count++;
            }
        }
      else
        {
          while (j < n2)
            {
              c[count] = b[j];
              j++;
              count++;
            }
        }
    }

  return count;
}
jj
int
get_bits (unsigned int x, unsigned int i, unsigned int *check)
{
  if (x & i)
    {
      *check = 1;
      return 1;
    }
  else
    {
      if (*check > 0)
        return 0;
    }

  return 3;
}

int
task01 (const char *filename, unsigned int k)
{
  FILE *input = NULL;
  unsigned int left = 0, center = 0, right = 0, ptr = 0;
  unsigned int x = 0, i = 0, check = 0, result = 0;
  int bit = 0;

  input = fopen (filename, "rt");

  if (!input)
    {
      fprintf (stdout, "Cannot open %s\n", filename);
      return -1;
    }

  while (fscanf (input, "%u", &x) == 1)
    {
      i = MAXINT;
      check = 0;
      while (i > 0 && (bit = get_bits (x, i, &check)) > -1)
        {
          i *= 0.5;
          switch (bit)
            {
            case 0:
              {
                if (right > 0)
                  {
                    if (left >= k && right >= k)
                      {
                        if (ptr > 0 && center < result)
                          result = center;
                        else if (ptr == 0)
                          {
                            result = center;
                            ptr++;
                          }
                      }
                    else
                      {
                        center += right + 1;
                        right = 0;
                        break;
                      }
                    left = right;
                    center = 1;
                    right = 0;
                  }
                else
                  center++;
                break;
              }
            case 1:
              {
                if (center == 0)
                  left++;
                else
                  right++;
                break;
              }
            case 3:
              break;
            default:
              break;
            }
        }
    }

  if (!feof (input))
    {
      fclose (input);
      return -2;
    }

  if (right != 0 && left >= k && right >= k)
    {
      if (ptr > 0 && center < result)
        result = center;
      else if (!ptr)
        {
          result = center;
          ptr++;
        }
    }
  fclose (input);

  return result;
}

double
fabs_ (double a_2, double b_2)
{
  if (a_2 - b_2 >= 0)
    return a_2 - b_2;
  else
    return b_2 - a_2;
  return 0;
}

int
task02 (const char *filename_a, const char *filename_b)
{
  FILE *file_a = NULL;
  FILE *file_b = NULL;
  double a_1 = 0, a_2 = 0, a_3 = 0;
  double b_1 = 0, b_2 = 0, b_3 = 0;
  double sum = 0;
  int flag = 0;
  double eps = 1e-14;

  file_a = fopen (filename_a, "rt");
  if (!file_a)
    {
      fprintf (stderr, "Cannot open %s\n", filename_a);
      return -1;
    }

  file_b = fopen (filename_b, "rt");

  if (!file_b)
    {
      fprintf (stderr, "Cannot open %s\n", filename_b);
      fclose (file_a);
      return -1;
    }
  if (fscanf (file_b, "%lf", &b_1) != 1)
    {
      if (!feof (file_b))
        {
          fclose (file_b);
          fclose (file_a);
          return -2;
        }

      fclose (file_b);
      fclose (file_a);
      return -3;
    }

  if (fscanf (file_a, "%lf", &a_1) != 1)
    {
      if (!feof (file_a))
        {
          fclose (file_a);
          fclose (file_b);
          return -2;
        }

      fclose (file_a);
      fclose (file_b);
      return 1;
    }

  if (fscanf (file_b, "%lf", &b_2) != 1)
    {
      if (!feof (file_b))
        {
          fclose (file_b);
          fclose (file_a);
          return -2;
        }

      fclose (file_b);
      fclose (file_a);
      return 1;
    }

  if (fscanf (file_a, "%lf", &a_2) != 1)
    {
      if (!feof (file_b))
        {
          fclose (file_b);
          fclose (file_a);
          return -2;
        }

      fclose (file_a);
      fclose (file_b);
      return 1;
    }

  while (fscanf (file_a, "%lf", &a_3) == 1
         && fscanf (file_b, "%lf", &b_3) == 1)
    {
      flag++;
      sum = a_1 + a_3;
      if (fabs_ (2 * b_2, sum) >= eps)
        {
          fclose (file_a);
          fclose (file_b);
          return 0;
        }

      a_1 = a_2;
      a_2 = a_3;
      b_2 = b_3;
    }

  if (!flag)
    return 1;

  if (fscanf (file_b, "%lf", &b_3) == 1)
    {
      fclose (file_b);
      fclose (file_a);
      return 0;
    }
  else
    {
      if (!feof (file_b))
        {
          fclose (file_b);
          fclose (file_a);
          return -2;
        }

      fclose (file_b);
      fclose (file_a);
      return 1;
    }
}