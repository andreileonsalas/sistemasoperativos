#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define Minimo 300
#define Maximo 5000

int generarAleatorio();
int allocate_map(void);
int allocate_pid();
void release_pid();

bool* pid_map;

int main() {
    // initiate pid map
    if(allocate_map() == -1){
        printf("unable to create the pid map\n");
    }

    // sample pid for feature release
    int pid1, pid2;

    // allocate pids
    for(int i = 0; i < 1000; i ++){
        int pid = allocate_pid();
        if(i == 3) pid1 = pid;
        if(i == 4) pid2 = pid;
        printf("PID: %d\n", pid);
    }

    // release pids
    release_pid(pid1);
    release_pid(1000);
    release_pid(pid2);

}

int allocate_map(void){
    srand(time(0));
    pid_map = malloc(sizeof(bool) * Maximo); // yah, allocated extra 300 pid
    return pid_map == NULL ? -1 : 1;
}

int allocate_pid(){
    int pid = generarAleatorio();
    while(pid_map[pid] == true){
        pid = generarAleatorio();
    }
    pid_map[pid] = true;
    return pid;
}


void release_pid(int pid){
    if(pid_map[pid] == true){
        pid_map[pid] = false;
        printf("Release pid %d\n", pid);
    } else {
        printf("PID %d is not associated with any process\n", pid);
    }
}


//Generar un numero al azar entre el minimo y maximo
int generarAleatorio(){
    return (rand() % (Maximo - Minimo + 1) + Minimo);
}