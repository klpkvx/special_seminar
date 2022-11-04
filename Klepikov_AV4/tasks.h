#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef TASKS_H
#define TASKS_H
#define MXIT_ 30
double task01(double (*function)(double), double a, double b, int n);
double task02(double (*function)(double), double a, double b, int n);
int task03(double (*function)(double), double a, double b, double eps, double *res);
int task04(double (*function)(double), double a, double b, double eps, double *res);
double task05(double (*function)(double), double a, double eps, double *res);
double task06(double (*function)(double), double a, double eps, double *res);
#endif // TASKS_H