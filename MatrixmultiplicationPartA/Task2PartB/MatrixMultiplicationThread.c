#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define Matrix_Size 1024

//Compile this program using cc -o MatrixMultiplicationThread MatrixMultiplicationThread.c -pthread
//run this program using ./MatrixMultiplicationThread


typedef struct row_cols{
    int a,b;
}args;


int matrix1[Matrix_Size][Matrix_Size];
int matrix2[Matrix_Size][Matrix_Size];
int result[Matrix_Size][Matrix_Size];

int Num_Thread;


void *product(void* arg){
    args* mno=arg;

    for(int c=0;c<Matrix_Size;c++){
        result[mno->a][mno->b]+=matrix1[mno->a][c]*matrix2[c][mno->b];
       
    }
}


void start_multiplication(){

    int a=0,b=0;

    while(a<Matrix_Size){
         b=0;

        while(b<Matrix_Size){
            pthread_t threads[Num_Thread];
            args mno[Num_Thread]; 

            for(int i=0;i<Num_Thread;i++){
                
                if(b>=Matrix_Size){
                    break;
                }
                    mno[i].a=a;
                    mno[i].b=b;
                    pthread_create(&threads[i], NULL, product, (void *) &mno[i]);
                    pthread_join(threads[i],NULL);
                     b++;
            }
            
        }
        a++;
    }
}

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
{
    long long int ds = finish->tv_sec - start->tv_sec;
    long long int dn = finish->tv_nsec - start->tv_nsec;
    if(dn < 0 ) {
        ds--;
        dn += 1000000000;
    }
    *difference = ds * 1000000000 + dn;
    return !(*difference > 0);
}


int main(){

    for(int i=0;i<Matrix_Size;i++){
        for(int j=0;j<Matrix_Size;j++){
            matrix1[i][j]=rand()%10;
            matrix2[i][j]=rand()%10;
            result[i][j]=0;
        }
    }


    printf("How many thread do you want to use");
    scanf("%d",&Num_Thread);

    printf("Matrix1:%ld\nMatrix2:%ld\n",sizeof(matrix1)/sizeof(matrix1[0]),sizeof(matrix2)/sizeof(matrix2[0]));
    printf("Threads:%d\n",Num_Thread);
    
    struct timespec start, finish;
    long long int time_elapsed;
    clock_gettime(CLOCK_MONOTONIC, &start);
    clock_gettime(CLOCK_MONOTONIC, &finish);

    start_multiplication();    
    
    time_difference(&start, &finish, &time_elapsed);
    printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,(time_elapsed/1.0e9));


}
