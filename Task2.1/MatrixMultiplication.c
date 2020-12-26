#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//compile with gcc -0 MatrixMultiplication MatrixMultiplication.c
int StartMultiplication()
{
	int a[3][3], b[3][3], c[3][3];
	int i, j, k;
	printf("\nEnter Firt Matrix\n");
	 for(i=0; i<3; i++) {
	 for(j=0; j<3; j++) {
	  scanf("%d", &a[i][j]);
	  }
	}
	
	printf("Enter the Second Matrix\n");
	for(i=0; i<3; i++) {
	 for(j=0; j<3; j++) {
	  scanf("%d", &b[i][j]);
	 }
	}
	for(i=0; i<3; i++) {
	 for(j=0; j<3; j++) {
	  c[i][j]=0;
	  for(k=0; k<3; k++) {
		c[i][j]=c[i][j] + a[i][k] * b[k][j];
	   }
	  }
	}
	printf("\nThe results is…\n");
	for(i=0; i<3; i++) {
	 for(j=0; j<3; j++) {
	   printf("%d  ", c[i][j]); 
	  }
	printf("\n");
	}
	return 0;
}
int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main()
{
  struct timespec start, finish;   
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);
  StartMultiplication();
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9)); 

}

