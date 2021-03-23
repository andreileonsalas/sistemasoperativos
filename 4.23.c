//https://github.com/twseptian/Operating-System-Codes/blob/master/4.18_omp_montecarlo.c

//how to run 
//gcc -fopenmp -o 4.23 4.23.c
//./4.23 999

/*
 * Name     : Tri Wanda Septian
 * 
 * How to compile the source code (Linux)
 * $gcc -fopenmp -o outfile sourcecode.c
 *
 * 4.18*: Repeat exercise 4.17, but instead of using a separate thread to generate random points, use OpenMP to parallelize the generation of points.
 * Be careful not to place the calculation of phi in the parallel region, since you want to calculate phi only once.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>

int i = 0; //loop counter
int count = 0; //count holds all the number of how many good coordinates
double x,y; //x,y value for thre random coordinate
double z; //used to check if x*x+y*y <=1
int totalpoints; //number if iterations per FOR LOPP

void *runner(void *param){
#pragma omp parallel private(x,y,z,i) shared(count)
    //The omp parallel directive explicitly instructs the compiler to parallelize the chosen block of code.
    {
        srandom((unsigned int)time(NULL) ^ omp_get_thread_num());
#pragma omp for
        //initialize random number of x and y
        for (i=0; i< totalpoints; i++){
            x = (double)rand() / RAND_MAX; //generate random x coordinate number
            y = (double)rand() / RAND_MAX; //generate random y coordinate number

            z = x*x+y*y;
            if(z<=1){
                count++;
            }
        }
    }
}
int main(int argc, char *argv[]){
    pthread_t thread;

    printf("\nWelcome to Thread Process with Monte Carlo Technique and OpenMP\n");
    printf("\nName : Tri Wanda Septian\n");

    if(argc !=2 ){
        fprintf(stderr,"\nUsage : openmp.out <integer value>\n");
        return -1;
    }
    if (atoi(argv[1]) < 0){
        fprintf(stderr,"\n%d must be >= 0\n",atoi(argv[1]));
        return -1;
    }

    int numberIter = atoi(argv[1]); //number if iterations per FOR LOPP
    totalpoints = numberIter;

    pthread_create(&thread,NULL,&runner, NULL); //create the thread
    pthread_join(thread,NULL);//wait forthre thread to exit

    double phi = 4*((double)count/(double)totalpoints); //phi calculation formula
    printf("\nNumber of trials: %d, estimate of phi is %g \n",totalpoints,phi);
}