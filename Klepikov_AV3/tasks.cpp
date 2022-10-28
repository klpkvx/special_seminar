#include "tasks.h"
#include "math.h"
#include "stdio.h"

int
check_array (double *x, int n)
{
  for (int k = 0; k < n; k++)
    for (int i = k + 1; i < n; i++)
      if (x[k] >= x[i] && x[k] <= x[i])
        return -1;

  return 0;
}

int
read_array (double *x, double *y, int n, char *filename)
{
  FILE *input = fopen (filename, "rt");
  if (!input)
    {
      fprintf (stderr, "Cannot open file %s\n", filename);
      return -1;
    }

  for (int i = 0; i < n; i++)
    {
      if (fscanf (input, "%lf", x + i) != 1)
        {
          fclose (input);
          return -2;
        }
      if (fscanf (input, "%lf", y + i) != 1)
        {
          fclose (input);
          return -3;
        }
    }
  fclose (input);
  return 0;
}

int
read_array_3 (double *x, double *y, double *d, int n, char *filename)
{
  FILE *input = fopen (filename, "rt");
  if (!input)
    {
      fprintf (stderr, "Cannot open file %s\n", filename);
      return -1;
    }

  for (int i = 0; i < n; i++)
    {
      if (fscanf (input, "%lf", x + i) != 1)
        {
          fclose (input);
          return -2;
        }
      if (fscanf (input, "%lf", y + i) != 1)
        {
          fclose (input);
          return -3;
        }
      if (fscanf (input, "%lf", d + i) != 1)
        {
          fclose (input);
          return -4;
        }
    }

  fclose (input);
  return 0;
}

void
print_array (double *a, int n, int m)
{
  for (int i = 0; i < (n > m ? m : n); i++)
    printf ("%lf ", a[i]);
  printf ("\n");
}

double
task01 (double x0, int n, double *x, double *y)
{
  double sum = 0;
  double proizved = 1;
  for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
        {
          if (j == i)
            continue;
          proizved *= (x0 - x[j]) / (x[i] - x[j]);
        }
      sum += y[i] * proizved;
      proizved = 1;
    }
  return sum;
}

double
task02 (double x0, int n, double *x, double *y)
{
  double result = 0;
  for (int j = 0; j < n - 1; j++)
    for (int i = n - 1; i > j; i--)
      y[i] = (y[i] - y[i - 1]) / (x[i] - x[i - 1 - j]);
  result = y[n - 1];
  for (int i = n - 2; i >= 0; i--)
    result = result * (x0 - x[i]) + y[i];
  return result;
}

double
task03 (double x0, int n, double *x, double *y, double *d)
{
  double sum = 0;
  for (int j = n - 1; j > 0; j--)
    y[j] = (y[j] - y[j - 1]) / (x[j] - x[j - 1]);

  for (int i = 1; i < 2 * n; i++)
    for (int j = 2 * n - 1; j > i; j--)
      j & 1 ? d[j >> 1]
              = (d[j >> 1] - y[j >> 1]) / (x[j >> 1] - x[(j - i - 1) >> 1])
            : y[j >> 1] = (y[j >> 1] - d[(j - 1) >> 1])
                          / (x[j >> 1] - x[(j - i - 1) >> 1]);

  for (int i = 2 * n - 1; i > 0; i--)
    {
      i & 1 ? sum += d[i >> 1] : sum += y[i >> 1];
      sum *= (x0 - x[(i - 1) >> 1]);
    }

  sum += y[0];
  return sum;
}

double
task04 (double (*function) (double), double a, double b, double eps, double *x)
{
  double c = 0;
  double value_a = (*function) (a);
  double value_b = (*function) (b);
  double value_c = 0;

  if (fabs (value_a) < eps)
    {
      *x = a;
      return 0;
    }

  if (fabs (value_b) < eps)
    {
      *x = b;
      return 0;
    }

  if ((value_a > 0 && value_b > 0) || (value_a < 0 && value_b < 0))
    return -1;

  for (int it = 1; it <= MXIT; it++)
    {
      c = (a + b) * 0.5;
      if (b - a < eps || (c <= a && c >= a) || (c >= b && c <= b))
        {
          *x = c;
          return it;
        }
      value_c = (*function) (c);

      if (fabs (value_c) < eps)
        {
          *x = c;
          return it;
        }

      if (!((sign (value_a) >= sign (value_c))
            && (sign (value_a) <= sign (value_c))))
        {
          b = c;
          value_b = value_c;
        }
      else
        {
          a = c;
          value_a = value_c;
        }
    }
  return -1;
}

int
task05 (double (*function) (double), double (*derivative) (double), double x0,
        double eps, double *x)
{
  double func_x0 = (*function) (x0);
  double derivative_x0 = (*derivative) (x0);
  int it = 0;

  if (fabs (func_x0) < eps)
    return it;

  for (it = 1; it <= MXIT; it++)
    {
      if ((derivative_x0 > 0) || (derivative_x0 < 0))
        {
          x0 = x0 - func_x0 / derivative_x0;
          func_x0 = (*function) (x0);
          derivative_x0 = (*derivative) (x0);

          if (fabs (func_x0) < eps)
            {
              *x = x0;
              return it;
            }
        }
      else
        return -1;
    }

  return -1;
}
double
task06 (double (*function) (double), double a, double b, double eps, double *x)
{
  double value_a = (*function) (a);
  double value_b = (*function) (b);
  double value_c = 0, c = 0;
  double dif = 0;
  if (fabs (value_a) < eps)
    {
      *x = a;
      return 0;
    }

  if (fabs (value_b) < eps)
    {
      *x = b;
      return 0;
    }

  if ((value_a > 0 && value_b > 0) || (value_a < 0 && value_b < 0))
    return -1;

  for (int it = 1; it <= MXIT; it++)
    {
      if (fabs (value_b - value_a) < eps)
        return -1;
      dif = ((b - a) * value_a) / (value_b - value_a);
      c = a - dif;
      if (c > b || c < a)
        return -1;
      value_c = (*function) (c);
      if (fabs (value_c) < eps)
        {
          *x = c;
          return it;
        }
      if (!((sign (value_c) >= sign (value_b))
            && (sign (value_c) <= sign (value_b))))
        {
          a = c;
          value_a = value_c;
        }
      else
        {
          b = c;
          value_b = value_c;
        }
    }
  return -1;
}

double
task07 (double (*function) (double), double a, double b, double eps, double *x)
{
  double value_a = (*function) (a);
  double value_b = (*function) (b);
  double y = 0, value_y = 0;
  double mid = 0.5 * (a + b);
  double value_mid = (*function) (mid);
  double f_a = 0, f_b = 0;
  double f_mid = 0, f_y = 0;

  if (fabs (value_a) < eps)
    {
      *x = a;
      return 0;
    }

  if (fabs (value_b) < eps)
    {
      *x = b;
      return 0;
    }

  if (fabs (value_mid) < eps)
    {
      *x = mid;
      return 0;
    }

  for (int it = 1; it <= MXIT; it++)
    {
      if (fabs (value_b - value_a) < eps || fabs (value_mid - value_b) < eps
          || fabs (value_mid - value_a) < eps)
        {
          return -1;
        }
      y = a - value_a * (b - a) / (value_b - value_a)
          + value_a * value_b
                * ((mid - b) / (value_mid - value_b)
                   - (b - a) / (value_b - value_a))
                / (value_mid - value_a);
      value_y = (*function) (y);
      if (fabs (value_y) < eps)
        {
          *x = y;
          return it;
        }
      f_a = fabs (value_a);
      f_b = fabs (value_b);
      f_mid = fabs (value_mid);
      f_y = fabs (value_y);
      if (f_a > f_b && f_a > f_mid && f_a > f_y)
        {
          a = y;
          value_a = value_y;
          continue;
        }
      if (f_b > f_mid && f_b >= f_y)
        {
          b = y;
          value_b = value_y;
          continue;
        }
      if (f_mid > f_y)
        {
          mid = y;
          value_mid = value_y;
          continue;
        }
      else
        return -1;
    }
  return -1;
}

double
task08 (double (*function) (double), double x0, double eps, double *x)
{
  double x_n = 0;
  for (int it = 1; it <= MXIT; it++)
    {
      x_n = (*function) (x0);
      if (fabs (x_n - x0) < eps)
        {
          *x = x0;
          return it;
        }
      x0 = x_n;
    }
  return -1;
}

#define MX100k 100000

int
task09 (double (*function) (double), double a, double b, double eps, double *x)
{
  double x_0 = a, x_1 = (a + b) * 0.5, x_2 = b;
  double f_0 = (*function) (x_0), f_1 = (*function) (x_1),
         f_2 = (*function) (x_2);
  int it = 0;
  double x4 = 0;
  double y_1 = 0, y_0 = 0;
  double y10 = 0, y21 = 0, y21_10 = 0;
  double s = 0;

  y_0 = f_1;
  for (it = 1; it < MX100k; it++)
    {
      s = x_1 - x_0;
      if (fabs (s) < eps)
        {
          it = MX100k;
          break;
        }
      y10 = (f_1 - f_0) / s;
      s = x_2 - x_1;
      if (fabs (s) < eps)
        {
          it = MX100k;
          break;
        }
      y21 = (f_2 - f_1) / s;
      s = x_2 - x_0;
      if (fabs (s) < eps)
        {
          it = MX100k;
          break;
        }

      y21_10 = (y21 - y10) / s;
      if (fabs (y21_10) < eps)
        {
          it = MX100k;
          break;
        }

      x4 = 0.5 * ((x_0 + x_1) - y10 / y21_10);
      y_1 = (*function) (x4);
      if (fabs (y_1 - y_0) < eps)
        break;
      y_0 = y_1;
      if (f_0 <= f_1)
        {
          if (f_0 <= f_2)
            {
              if (y_1 <= f_0)
                {
                  it = MX100k;
                  break;
                }
              else
                {
                  f_0 = y_1;
                  x_0 = x4;
                }
            }
          else
            {
              if (y_1 <= f_2)
                {
                  it = MX100k;
                  break;
                }
              else
                {
                  f_2 = y_1;
                  x_2 = x4;
                }
            }
        }
      else
        {
          if (f_1 <= f_2)
            {
              if (y_1 <= f_1)
                {
                  it = MX100k;
                  break;
                }
              else
                {
                  f_1 = y_1;
                  x_1 = x4;
                }
            }
          else
            {
              if (y_1 <= f_2)
                {
                  it = MX100k;
                  break;
                }
              else
                {
                  f_2 = y_1;
                  x_2 = x4;
                }
            }
        }
    }

  if (it < MX100k)
    {
      *x = x4;
      return it;
    }
  else
    return -1;
}