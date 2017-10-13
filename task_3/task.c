#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#define N 1000000
int a[100];
int k;
scanf("%d", &k);
void * f(int i)
{
	a[i] = 0;
	int j;
	double x, y;
	for (j = 0; j < N / k; j++)
	{
		srand(time(0) * j);
		x = (double)rand() / (double)RAND_MAX;
		srand(time(0) * time(0) * j);
		y = (double)rand() / (double)RAND_MAX;
		if (y < x * x)
			a[i] += 1;
	}
	return;
}
int main()
{
  int i, n = 0;
  pthread_t t[100];
  for(i = 0; i < k; i++)
    pthread_create(t + i, NULL, f, &i);
  for(i = 0; i < k; i++)
  {
    pthread_join(t[i], NULL);
    n += a[i];
  }
	printf("%lf", (double)n / (double)N);
	return 0;
}
/* N = 1000000 points; function y = x * x; k threads; if k = 4(number of kernels) 3.6 times faster than if without threads
k = 8 is the fastest(no more growth) - 6.5 times faster than if without threads */
