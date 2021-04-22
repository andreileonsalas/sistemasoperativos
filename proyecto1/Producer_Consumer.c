#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "buffer.h"

#include <pthread.h>
#include <semaphore.h>
#include <time.h>


buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t full, empty;
int count, in, out;
void *consumer(void *param);
void *producer(void *param);
int insert_item(buffer_item item);
int remove_item(buffer_item *item);


int main(int argc, char **argv){
  if (argc != 4){
    printf("Ponga solamente 3 Argumentos\n");
    exit(1);
  }
  const long int sleeptime = strtol(argv[1], NULL, 0);
  const long int producersthreads = strtol(argv[2], NULL, 0);
  const long int consumersthreads = strtol(argv[3], NULL, 0);
  int i;
  srand(time(NULL));
  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, BUFFER_SIZE); 
  sem_init(&full, 0, 0);
  count = 0;
  in = 0;
  out = 0;
  pthread_t producers[producersthreads];
  pthread_t consumers[consumersthreads];
  for(i = 0; i < producersthreads; i++)
    pthread_create(&producers[i], NULL, producer, NULL);
  for(i = 0; i < consumersthreads; i++)
    pthread_create(&consumers[i], NULL, consumer, NULL);
  sleep(sleeptime);
  return 0;
}

int insert_item(buffer_item item){
  int success;
  sem_wait(&empty);
  pthread_mutex_lock(&mutex);
  if( count != BUFFER_SIZE){
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    count++;
    success = 0;
  }
  else
    success = -1;
  pthread_mutex_unlock(&mutex);
  sem_post(&full);
  return success;
}


int remove_item(buffer_item *item){
  int success;  
  sem_wait(&full);
  pthread_mutex_lock(&mutex);
  if( count != 0){
    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    count--;
    success = 0;
  }
  else
    success = -1;
  pthread_mutex_unlock(&mutex);
  sem_post(&empty);
  return success;
}

void *producer(void *param){
  buffer_item item;
  while(1){
	/* sleep for a ra
	ndom period of time */
    sleep(rand() % 10); 
    /* generate a random number */
    item = rand();
    if(insert_item(item))
      printf("report error condition\n");
    else
      printf("producer produced %d\n", item);
  }
}


void *consumer(void *param){
  buffer_item item;
  while(1){
	/* sleep for a random period of time */
    sleep(rand() % 10);
    if(remove_item(&item))
      printf("report error condition\n");
    else
      printf("consumer consumed %d\n", item);
  }
}