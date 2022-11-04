#include "func.h"

static int count = 0;

int
get_count (void)
{
  return count;
}

double
f0 (double x)
{
  (void)x;
  count++;
  return 1;
}

double
f1 (double x)
{
  count++;
  return 1 + x;
}

double
f2 (double x)
{
  count++;
  return 1 + x + x * x;
}

double
f3 (double x)
{
  count++;
  return 1 + x + x * x + x * x * x;
}

double
f4 (double x)
{
  count++;
  return 1 + x + x * x + x * x * x + x * x * x * x;
}

double
f5 (double x)
{
  count++;
  return exp (-x);
}

double
f6 (double x)
{
  count++;
  return 1 / (25 * x * x + 1);
}