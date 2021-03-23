//how to run 
//gcc -fopenmp -g -lpthread -lm -o 4.24 4.24.c
//where 999 is the number to check and 4 is the number of threats
//./4.24 999 4


#include <stdio.h>
#include <math.h>
#include <pthread.h>  

#define MAX_N 100000000
#define MAX_THREADS 25

//definicion de variables
int thread_qty,  
    n,  
    prime[MAX_N+1],  
    nextbase;  
	
//
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
pthread_t id[MAX_THREADS];

//multiplos de k
void crossout(int k)
{  int i;
   for (i = 3; i*k <= n; i += 2)  {
      prime[i*k] = 0;
   }
}


void *worker(int tn)  
{  
	//tn es el numero de thread
	int lim,base,
       work = 0;  // trabajo hecho por este thread
   
   lim = sqrt(n);
   do  {
      
      pthread_mutex_lock(&nextbaselock);
      base = nextbase;
      nextbase += 2;
  
      pthread_mutex_unlock(&nextbaselock);
      if (base <= lim)  {
       
         if (prime[base])  {
            crossout(base);
            work++;  // sumar trabajo hecho por este thread
         }
      }
      else return work; 
   } while (1);
}

main(int argc, char **argv)
{  	
	int nprimes,  // cantidad de numeros primos encontrados
       i,work;
   n = atoi(argv[1]);
   thread_qty = atoi(argv[2]);
 
   for (i = 3; i <= n; i++)  {
      if (i%2 == 0) prime[i] = 0;
      else prime[i] = 1;
   }
   nextbase = 3;
 // inicializar threads
   for (i = 0; i < thread_qty; i++)  {
 
      pthread_create(&id[i],NULL,worker,i);
   }

   // wait
   for (i = 0; i < thread_qty; i++)  {
      pthread_join(id[i],&work);
      printf("%d values of base done\n",work);
   }
   
   // imprimir resultados
   nprimes = 1;
   for (i = 3; i <= n; i++)
      if (prime[i])  {
         nprimes++;
      }
   printf("la cantidad de numeros primos encontrados es %d\n",nprimes);
}