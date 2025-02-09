#include <stdio.h>
#include <omp.h>

#define n 10

int main()
{
	double a[n];
	double sum=0, psum;
	float startTime, endTime,execTime;
	int i;
	int omp_rank;

	startTime = omp_get_wtime();
	#pragma omp parallel private (i,psum) shared (a, sum) 
	{
		psum=0;
		#pragma omp  for 
		for(i=0;i<n;i++)
		{
			omp_rank = omp_get_thread_num();
			a[i] = i ;  	// Use Random function and assign a[i]
			psum = psum + a[i];
			printf("The value of a[%d] = %f and psum = %f done by worker Thread ID = %d\n", i, a[i], psum, omp_rank);
		}
		#pragma omp critical(dosum)		
		{
			//omp_rank = omp_get_thread_num();
			sum = sum + psum;
			printf("Final Sum = %f\n", sum);
		}

	}
	endTime = omp_get_wtime();

	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}
