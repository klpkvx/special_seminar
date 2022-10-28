#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#ifndef TASKS_H
#define TASKS_H

#define LEN 1234

int read_array (double *x, double *y, int n, char *filename);
int read_array_3 (double *x, double *y, double *d, int n, char *filename);
int check_array (double *x, int n);
void print_array (double *a, int n, int m);

double f0 (double x);
double f1 (double x);
double f2 (double x);
double f3 (double x);
double f4 (double x);
double f5 (double x);
double f6 (double x);
double d0 (double x);
double d1 (double x);
double d2 (double x);
double d3 (double x);
double d4 (double x);
double d5 (double x);
double d6 (double x);
double sign (double x);
int get_count ();
#define MXIT 10000

double task01 (double x0, int n, double *x, double *y);
double task02 (double x0, int n, double *x, double *y);
double task03 (double x0, int n, double *x, double *y, double *d);
double task04 (double (*function) (double), double a, double b, double eps,
               double *x);
int task05 (double (*function) (double), double (*derivative) (double),
            double x0, double eps, double *x);
double task06 (double (*function) (double), double a, double b, double eps,
               double *x);
double task07 (double (*function) (double), double a, double b, double eps,
               double *x);

double task08 (double (*function) (double), double x0, double eps, double *x);
int task09 (double (*function) (double), double a, double b, double eps,
            double *x);

#endif // TASKS_H
