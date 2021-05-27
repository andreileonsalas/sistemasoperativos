#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
 
//how to run : gcc -pthread TheDiningPhilosophersProblem.c -o Dining;./Dining

#define n 5
#define Comiendo 0
#define Hambriento 1
#define Pensando 2
#define Izquierda (num_filosofo + 4) % n
#define Derecha (num_filosofo + 1) % n
 
int estado[n];
int filosofos[n] = { 0, 1, 2, 3, 4 }; //filosofos
 
sem_t mutex;
sem_t S[n];
 
void probar(int num_filosofo)
{
    if (estado[num_filosofo] == Hambriento
        && estado[Izquierda] != Comiendo
        && estado[Derecha] != Comiendo) {
        estado[num_filosofo] = Comiendo;
        sleep(2);
        printf("El filosofo %d toma los utensilios %d and %d\n", num_filosofo + 1, Izquierda + 1, num_filosofo + 1);
        printf("El filosofo %d esta comiendo\n", num_filosofo + 1);
        sem_post(&S[num_filosofo]);
    }
}
 
// tomar utensilios
void tomar_utensilios(int num_filosofo)
{
    sem_wait(&mutex);
    //asignar estado hambriento
    estado[num_filosofo] = Hambriento;
    printf("El filosofo %d tiene hambre\n", num_filosofo + 1);
    // comer si los filosofos al lado no estan comiendo
    probar(num_filosofo);
    sem_post(&mutex);
    // esperar a comer
    sem_wait(&S[num_filosofo]);
    sleep(1);
}
 

void dejar_utensilios(int num_filosofo)
{
    sem_wait(&mutex);
    // asignar estado pensando
    estado[num_filosofo] = Pensando;
    printf("El filosofo %d deja el utensilio %d y %d abajo\n", num_filosofo + 1, Izquierda + 1, num_filosofo + 1);
    printf("El filosofo %d esta pensando\n", num_filosofo + 1);
    probar(Izquierda);
    probar(Derecha);
    sem_post(&mutex);
}
 
void* filosofo(void* numero)
{
    while (1) {
        int* i = numero;
        sleep(1);
        tomar_utensilios(*i);
        sleep(0);
        dejar_utensilios(*i);
    }
}
 
int main()
{
    int i;
    pthread_t thread_id[n];
    // inicializar los semaforos
    sem_init(&mutex, 0, 1);
    for (i = 0; i < n; i++)
        sem_init(&S[i], 0, 0);
    for (i = 0; i < n; i++) {
        //crear los hilos de filosofos
        pthread_create(&thread_id[i], NULL,
                       filosofo, &filosofos[i]);
        printf("El filosofo %d esta pensando\n", i + 1);
    }
 
    for (i = 0; i < n; i++)
        pthread_join(thread_id[i], NULL);
}