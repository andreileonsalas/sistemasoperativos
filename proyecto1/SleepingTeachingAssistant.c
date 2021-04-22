
#include <pthread.h>		
#include <time.h>			
#include <unistd.h>			
#include <semaphore.h>		
#include <stdlib.h>			
#include <stdio.h>			

pthread_t asistente;		//hilo del asistente
pthread_t *estudiantes;		//N hilos para estudiantes


int total_sillas = 0;
int index_actual = 0;

//Semaforos y mutex lock
sem_t sleep_asistente;
sem_t sem_estudiante;
sem_t sem_sillas[3];
pthread_mutex_t acceso_silla;

//Declaracion de funciones
void *actividad_asistente();
void *actividad_estudiante(void *IDHilo);

int main(int argc, char* argv[])
{
	int total_estudiantes;		//default 7
	int id;
	srand(time(NULL));

	//Semaforos y mutex lock
	sem_init(&sleep_asistente, 0, 0);
	sem_init(&sem_estudiante, 0, 0);
	for(id = 0; id < 3; ++id)			//Hay un total de 3 sillas
		sem_init(&sem_sillas[id], 0, 0);

	pthread_mutex_init(&acceso_silla, NULL);
	
	if(argc<2)
	{
		printf("No se especificó la cantidad de estudiantes (Utilizando el default: 7)\n");
		total_estudiantes = 7;
	}
	else
	{
		printf("Se especificó el total de estudiantes, creando %d hilos\n", total_estudiantes);
		total_estudiantes = atoi(argv[1]);
	}
		
	//Asignar memoria para estudiantes
	estudiantes = (pthread_t*) malloc(sizeof(pthread_t)*total_estudiantes);

	//Crear los hilos
	pthread_create(&asistente, NULL, actividad_asistente, NULL);	
	for(id = 0; id < total_estudiantes; id++)
		pthread_create(&estudiantes[id], NULL, actividad_estudiante,(void*) (long)id);

	//Waiting para los hilos
	pthread_join(asistente, NULL);
	for(id = 0; id < total_estudiantes; id++)
		pthread_join(estudiantes[id], NULL);

	//Liberar memoria
	free(estudiantes); 
	return 0;
}

void *actividad_asistente()
{
	while(1)
	{
		sem_wait(&sleep_asistente); //Asistente durmiendo
		printf("######Se despierta el asistente por un estudiante#####\n");

		while(1)
		{
			//mutex lock
			pthread_mutex_lock(&acceso_silla);
			if(total_sillas == 0) 
			{
				//salir del ciclo si no hay sillas llenas
				pthread_mutex_unlock(&acceso_silla);
				break;
			}
			//el asistente pasa al siguiente estudiante
			sem_post(&sem_sillas[index_actual]);
			total_sillas--;
			printf("El estudiante deja la silla. Sillas restantes: %d\n", 3 - total_sillas);
			index_actual = (index_actual + 1) % 3;
			pthread_mutex_unlock(&acceso_silla);
			//unlock

			printf("\t Asistente atendiendo a un estudiante\n");
			sleep(5);
			sem_post(&sem_estudiante);
			usleep(1000);
		}
	}
}

void *actividad_estudiante(void *IDHilo) 
{
	int tiempo_trabajo;

	while(1)
	{
		printf("El estudiante %ld está trabajando en la asignación\n", (long)IDHilo);
		tiempo_trabajo = rand() % 10 + 1; //random para el sleep
		sleep(tiempo_trabajo);		

		printf("El estudiante %ld necesita ayuda del asistente\n", (long)IDHilo);
		
		pthread_mutex_lock(&acceso_silla);
		int count = total_sillas;
		pthread_mutex_unlock(&acceso_silla);

		if(count < 3)		//Sentar al estudiante en una silla
		{
			if(count == 0)		//Despertar al asistente si el estudiante se sienta en la primer silla 
				sem_post(&sleep_asistente);
			else //si no se sienta en otra silla y espera
				printf("El estudiante %ld se sienta en una silla y espera al asistente \n", (long)IDHilo);

			pthread_mutex_lock(&acceso_silla);
			int index = (index_actual + total_sillas) % 3;
			total_sillas++;
			printf("El estudiante se sentó, cantidad de sillas disponibles: %d\n", 3 - total_sillas);
			pthread_mutex_unlock(&acceso_silla);
		
			sem_wait(&sem_sillas[index]); 
			printf("\t Estudiante %ld siendo ayudado por asistente \n", (long)IDHilo);
			sem_wait(&sem_estudiante);		
			printf("Estudiante %ld salió del salón\n",(long)IDHilo);
		}
		else 
			printf("El estudiante %ld regresará en otra ocasión\n", (long)IDHilo); // en caso de que no haya sillas disponibles
	}
}