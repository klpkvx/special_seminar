#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#ifndef TASKS_H
#define TASKS_H
#define MAXINT 2147483648
int read_array (double *array, int k, const char *filename);
void init_array (double *array, int n, int f);
void print_array (double *array, int n, int p);
void print_array_a (double *a, int n, int p);
void print_array_b (double *a, int n, int p);
void print_array_c (double *a, int n, int p);

double f (int s, int n, int i);
int fdiff (double x1, double x2);

int euclidean_algorithm (int a, int b);
int get_bits (unsigned int x, unsigned int i, unsigned int *check);
int task01 (const char *filename, unsigned int k);
int task02 (const char *a, const char *b);
int task03 (const char *filename);
int task04 (const char *filename, double *d);
int task05 (double *array, int n, int k);
int task06 (double *array, int n, int k);
int task07 (double *array, int n, const char *b);
int task08 (double *a, double *b, double *c, int n1, int n2);
#endif // TASKS_H