//how to run 
//gcc -pthread -o 4.22 4.22.c
//./4.22

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int i         = 0;	
int cantidaddepuntos = 0;
int puntostotales  = 0;

void *count(void *X)
{ 
    for (i=0; i < cantidaddepuntos; i++)
    {	
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;
        
        if (((X * X) + (Y * Y)) <= 1)
        {
            puntostotales++;
        }
    }
    return NULL;
}

int main()
{
    printf("\n\nWelcome to Threaded Monte Carlo, by Sean Staz\n\n");
    srand(time(NULL));
    pthread_t thread;

    do
	{
        printf("Please enter a positive number for the amount of points you would like to generate? \n");
        scanf("%d", &cantidaddepuntos);  	
	}while (cantidaddepuntos <= 0);
  
    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);
    
    double points = 4.0 * puntostotales;
    double pi = points / cantidaddepuntos;
    printf("The approximate value of pi for the desired amount of points (%d) is: %f \n", cantidaddepuntos, pi);  
    return 0;
}
