#include "tasks.h"

double
task01(double (*function)(double), double a, double b, int n)
{
  double step = (b - a) / n;
  double sum = 0.5 * step * (*function)(a) + 0.5 * step * (*function)(b);
  double x = a;
  for (int i = 1; i < n; i++)
  {
    x += step;
    sum += step * (*function)(x);
  }
  return sum;
}

double
task02(double (*function)(double), double a, double b, int n)
{

  double step = (b - a) / (2 * n);
  double sum = step * (*function)(a) / 3.0 + step * (*function)(b) / 3.0;
  double x = a + step;
  double sum1 = step * (*function)(x);
  double sum2 = 0;
  for (int i = 1; i < n; i++)
  {
    x += step;
    sum2 += step * (*function)(x);
    x += step;
    sum1 += step * (*function)(x);
  }
  sum1 *= 4.0 / 3.0;
  sum2 *= 2.0 / 3.0;
  return sum + sum1 + sum2;
}

int task03(double (*function)(double), double a, double b, double eps, double *res)
{
  int n = 2;
  double step = (b - a) / 2.0;
  double tmp;
  double fa = function(a), fb = function(b), x = 0;
  double sum1 = ((fa + fb) * 0.5 + function(a + step)) * step, sum2;
  for (int i = 1; i < MXIT_; ++i)
  {
    tmp = 0;
    step *= 0.5;
    x = a + step;
    for (int j = 0; j < n; ++j)
    {
      tmp += function(x) * step;
      x += 2 * step;
    }
    sum2 = 0.5 * sum1 + tmp;
    if (fabs(sum2 - sum1) < eps)
    {
      *res = sum2;
      return 2 * n;
    }
    n *= 2;
    sum1 = sum2;
  }
  return -1;
}

int task04(double (*function)(double), double a, double b, double eps, double *res)
{
  int n = 2;
  double step = (b - a) / 2.0;
  double x;
  double fa = function(a), fb = function(b);
  double sn_1 = step * (fa + fb) / 3.0;
  double sn_2 = step * 2 * function(a + step) / 3.0;
  double sum_1 = sn_1 + 2 * sn_2;
  double sum_2 = 0, s2n_2 = 0, s2n = 0;
  double tmp = 0;
  for (int i = 1; i < MXIT_; ++i)
  {
    sum_2 = (sn_1 + sn_2) * 0.5;
    tmp = 0;
    step *= 0.5;
    x = a + step;
    for (int j = 0; j < n; ++j)
    {
      tmp += function(x) * step;
      x += 2 * step;
    }
    s2n_2 = 2.0 * tmp / 3.0;
    s2n = sum_2 + 2 * s2n_2;
    if (fabs(s2n - sum_1) < eps)
    {
      *res = s2n;
      return 2 * n;
    }
    n *= 2;
    sn_1 = sum_2;
    sn_2 = s2n_2;
    sum_1 = s2n;
  }
  return -1;
}

double task05(double (*function)(double), double a, double eps, double *res)
{
  double b;
  int count = 0, step = 1;
  double tmp = 0, sum = 0;
  for (int i = 0; i < MXIT_; ++i)
  {
    b = a + step;
    count = task03((*function), a, b, eps, &tmp);
    if (count < 0)
      return -1;
    sum += tmp;
    if (fabs(tmp) < eps)
    {
      *res = sum;
      return b;
    }
    step = step * 2;
    a = b;
  }
  return -1;
}

double task06(double (*function)(double), double a, double eps, double *res)
{
  double b;
  int count = 0, step = 1;
  double tmp = 0, sum = 0;
  for (int i = 0; i < MXIT_; ++i)
  {
    b = a + step;
    count = task03((*function), a, b, eps, &tmp);
    if (count < 0)
      return -1;
    sum += tmp;
    if (fabs(tmp) < eps)
    {
      *res = sum;
      return b;
    }
    step = step * 2;
    a = b;
  }
  return -1;
}