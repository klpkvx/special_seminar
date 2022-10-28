#include "tasks.h"

static int count = 0;

int
get_count ()
{
  return count;
}

double
f0 (double x)
{
  (void)x;
  count++;
  return x;
}

double
f1 (double x)
{
  count++;
  return x - 1e+100;
}

double
f2 (double x)
{
  count++;
  return 4 - x * x;
}

double
f3 (double x)
{
  count++;
  return x * x * x + 3 * x * x + 16;
}

double
f4 (double x)
{
  count++;
  return 3 - 2 * x * x - x * x * x * x;
}

double
f5 (double x)
{
  count++;
  return sqrt (fabs (x) + 1) - 2;
}

double
f6 (double x)
{
  count++;
  return sqrt (sqrt (fabs (x) + 1) + 1) - 2;
}

double
d0 (double x)
{
  (void)x;
  return 0;
}

double
d1 (double x)
{
  (void)x;
  return 1;
}

double
d2 (double x)
{
  return (-2) * x;
}

double
d3 (double x)
{
  return 3 * x * x + 6 * x;
}

double
d4 (double x)
{
  return (-4) * x - 4 * x * x * x;
}

double
d5 (double x)
{
  return x >= 0 ? (0.5 / sqrt (x + 1)) : (-0.5 / sqrt (1 - x));
}

double
d6 (double x)
{
  return x >= 0 ? (0.25 / (sqrt (x + 1) * sqrt (sqrt (x + 1) + 1)))
                : (0.25 / (sqrt (1 - x) * sqrt (sqrt (1 - x) + 1)));
}

double
sign (double x)
{
  return x >= 0 ? 1 : -1;
}


int
minimum (double x1, double x2, double x3, double x4)
{
  double f1 = fabs (x1), f2 = fabs (x2), f3 = fabs (x3), f4 = fabs (x4);
  if (f1 < f2 && f1 < f3 && f1 < f4)
    return 1;
  if (f2 < f3 && f2 < f4)
    return 2;
  if (f3 < f4)
    return 3;
  else
    return 4;
}
