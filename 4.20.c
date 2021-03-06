//how to run 
//gcc -pthread -o 4.20 4.20.c
//./4.20

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

#define MIN_PID 100
#define MAX_PID 1000
#define NO_OF_P 8   //Numero de hilos

int pid[MAX_PID-MIN_PID]={0};

int allocate_pid(void){
    int i,flag=1;
    for(i=0; i<MAX_PID-MIN_PID; i++){
        if(pid[i]==0){
            pid[i]=1;
            flag=0;
            break;
        }
    }
    return flag?-1:i;
}
void release_pid(int id){
    pid[id]=0;
}
void *threadRoutine(void *arg){
    int tid =  *(( int* )arg);
    int id = allocate_pid();


    if(id==-1){
        puts("No hay PID.");
    }
    else{
        printf("Hilo [%3d] PID [%3d] Acomodado\n",tid,id+MIN_PID);
        
        int r=1+rand()%30;
        //para dormir segun el ejercicio
        sleep(r);

        printf("Hilo [%3d] PID [%3d] Liberado despues de %d segundos\n",tid,id+MIN_PID,r);
        release_pid(id);
    }
    pthread_exit(NULL);
}

int main(){
    int i;
    
    pthread_t process[NO_OF_P];
    srand(time(NULL));
    for(i=0; i<NO_OF_P; i++){
        if(pthread_create(&process[i],NULL,threadRoutine,(void*)&i))
            return -1*printf("Error en la crecion del hilo %d \n",i);
    }

    for(i=0; i<NO_OF_P; i++)
        pthread_join(process[i],NULL);
    
    return 0*printf("\nSaliendo...\n");
}