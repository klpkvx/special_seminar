#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#ifndef TASKS_H
#define TASKS_H

#define LEN 1234

int task01 (const char *filename_a, const char *filename_b, const char *s);
int is_okay_task1 (const char *curr_str, const char *s, int flag);

int task02 (const char *filename_a, const char *filename_b,
            const char *string);

int task03 (const char *filename_a, const char *filename_b,
            const char *string);
int is_okay_task3 (const char *curr_str, const char *string, char *spaces);

int task04 (const char *filename_a, const char *filename_b,
            const char *string);
int is_okay_task4 (const char *curr_str, const char *string, char *spaces);

int task05 (const char *filename_a, const char *filename_b,
            const char *string);

int is_okay_task5 (const char *curr_str, const char *string);

int task06 (const char *filename_a, const char *filename_b,
            const char *string);
int is_okay_task6 (const char *curr_str, const char *string);

#endif // TASKS_H
