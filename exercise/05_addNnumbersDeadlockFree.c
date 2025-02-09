#include <stdio.h>
#include <omp.h>

#define n 10

int main()
{
	double a[n];
	double sum=0;
	float startTime, endTime,execTime;
	int i;
	int omp_rank;

	startTime = omp_get_wtime();
	#pragma omp parallel private (i) shared (a) reduction(+:sum)
	{
		#pragma omp for
		for(i=0;i<n;i++)
		{
			omp_rank = omp_get_thread_num();
			a[i] = i; //* 10.236;  	// Use Random function and assign a[i]
			sum = sum + a[i];
			printf("The value of a[%d] = %lf and sum = %lf done by worker Thread ID = %d\n", i, a[i], sum, omp_rank);
		}		
	
	}
	endTime = omp_get_wtime();
	printf("\n Final Sum is %f\n", sum );
	execTime = endTime - startTime;
	printf("%f \n",execTime);
	return(0);
}
