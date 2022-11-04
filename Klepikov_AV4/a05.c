#include "func.h"
#include "tasks.h"

int main(int argc, char *argv[])
{
	int task = 5;
	double a = 0, b = 0;
	double eps = 0, t = 0;
	int k = 0;
	double (*function)(double), res = 0;
	double (*arr_func[])(double) = {f0, f1, f2, f3, f4, f5, f6};
	if (!(argc == 4 && sscanf(argv[1], "%lf", &a) == 1 && sscanf(argv[2], "%lf", &eps) == 1 && eps > 0 && sscanf(argv[3], "%d", &k) == 1) && k >= 0 && k <= 6)
	{
		printf("Usage: %s a eps k\n", argv[0]);
		return 1;
	}

	function = arr_func[k];
	t = clock();
	b = task05(function, a, eps, &res);
	if (b < 0)
	{
		fprintf(stderr, "Cannot calculate!\n");
		return -2;
	}
	t = (clock() - t) / CLOCKS_PER_SEC;
	printf("%s : Task = %d Res = %e B = %e Count = %d T = %.2f\n",
				 argv[0], task, res, b, get_count(), t);
	return 0;
}