//how to run 
//gcc -fopenmp -o 4.23 4.23.c
//./4.23 999

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <omp.h>

// declaracion de variables
int i = 0; //counter de ciclos
int count = 0; // contador de coordenadas validas
double x,y; //coordenadas
double z;
int totalpoints; //iteraciones por ciclo

void *runner(void *param){
#pragma omp parallel private(x,y,z,i) shared(count)

    {
        srandom((unsigned int)time(NULL) ^ omp_get_thread_num());
#pragma omp for
        //random para generar coordenadas x,y
        for (i=0; i< totalpoints; i++){
            x = (double)rand() / RAND_MAX; 
            y = (double)rand() / RAND_MAX; 

            z = x*x+y*y;
            if(z<=1){
                count++;
            }
        }
    }
}
int main(int argc, char *argv[]){
    pthread_t thread;

 
    if(argc !=2 ){
        fprintf(stderr,"Argumentos invalidos");
        return -1;
    }
    if (atoi(argv[1]) < 0){
        fprintf(stderr,"\n%d tiene que ser ser >= 0\n",atoi(argv[1]));
        return -1;
    }
	
	//numero de iteraciones por ciclo
    int numberIter = atoi(argv[1]); 
    totalpoints = numberIter;

    pthread_create(&thread,NULL,&runner, NULL); //crea el thread
    pthread_join(thread,NULL);//wait 
	
	//calculo de pi basado en la formula 
    double phi = 4*((double)count/(double)totalpoints); 
    printf("\nNumero de intentos: %d, valor aproximado de pi es %g \n",totalpoints,phi);
}