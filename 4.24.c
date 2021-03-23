//how to run 
//gcc -fopenmp -g -lpthread -lm -o 4.24 4.24.c
//where 999 is the number to check and 4 is the number of threats
//./4.24 999 4


#include <stdio.h>
#include <math.h>
#include <pthread.h>  // required for threads usage

#define MAX_N 100000000
#define MAX_THREADS 25

// shared variables; in threaded programs, all global variables are
// shared among all the threads; USE OF GLOBALS IS CENTRAL TO THREADED
// PROGRAMMING
int nthreads,  // number of threads (not counting main())
    n,  // range to check for primeness
    prime[MAX_N+1],  // in the end, prime[i] = 1 if i prime, else 0
    nextbase;  // next sieve multiplier to be used
// lock for the shared variable nextbase
pthread_mutex_t nextbaselock = PTHREAD_MUTEX_INITIALIZER;
// ID structs for the threads
pthread_t id[MAX_THREADS];

// "crosses out" all odd multiples of k
void crossout(int k)
{  int i;
   for (i = 3; i*k <= n; i += 2)  {
      prime[i*k] = 0;
   }
}

// each thread runs this routine
void *worker(int tn)  // tn is the thread number (0,1,...)
{  int lim,base,
       work = 0;  // amount of work done by this thread
   // no need to check multipliers bigger than sqrt(n)
   lim = sqrt(n);
   do  {
      // get next sieve multiplier
      // to avoid duplication across threads, change nextbase only with
      // the lock locked
      // lock the lock; if the lock is currently unlocked, this call
      // will return immediately and the lock state will be locked; if
      // on the other hand the lock is currently locked, this thread
      // will "block" (i.e. the call will NOT return) until the thread
      // that locked it does an unlock operation
      pthread_mutex_lock(&nextbaselock);
      base = nextbase;
      nextbase += 2;
      // unlock the lock
      pthread_mutex_unlock(&nextbaselock);
      if (base <= lim)  {
         // don't bother crossing out if base known composite
         if (prime[base])  {
            crossout(base);
            work++;  // log work done by this thread
         }
      }
      else return work; 
   } while (1);
}

main(int argc, char **argv)
{  int nprimes,  // number of primes found 
       i,work;
   n = atoi(argv[1]);
   nthreads = atoi(argv[2]);
   // mark all even numbers nonprime, and the rest "prime until
   // shown otherwise"
   for (i = 3; i <= n; i++)  {
      if (i%2 == 0) prime[i] = 0;
      else prime[i] = 1;
   }
   nextbase = 3;
   // get threads started
   for (i = 0; i < nthreads; i++)  {
      // this call says create a thread, record its ID in the array
      // id, and get the thread started executing the function worker(), 
      // passing the argument i to that function
      pthread_create(&id[i],NULL,worker,i);
   }

   // wait for all done
   for (i = 0; i < nthreads; i++)  {
      // this call says wait until thread number id[i] finishes
      // execution, and assign the return value of that thread to our
      // local variable "work" here (to judge whether the work is evenly
      // balanced among the threads)
      pthread_join(id[i],&work);
      printf("%d values of base done\n",work);
   }
   
   // report results
   //nprimes = 1;
   for (i = 3; i <= n; i++)
      if (prime[i])  {
         nprimes++;
      }
   printf("the number of primes found was %d\n",nprimes);
}