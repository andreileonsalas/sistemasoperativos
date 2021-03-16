#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


//how to compile
//gcc 3.21.c -o 3.21;./3.21

//how to run
// ./3.21

int main()
{
	int j=0;
	pid_t pid;
		do
		{
			printf("Ingrese un numero positivo \n"); 
  			scanf("%d", &j);	
		}while (j <= 0);

		pid = fork();

		if (pid == 0)
		{
			printf("Entro al pid: \n");
			printf("%d\n",j);
			while (j!=1)
			{
				if (j%2 == 0)
				{
					j = j/2;
				}
				else if (j%2 == 1)
				{
					j = 3 * (j) + 1;
				}	
			
				printf("%d\n",j);
			}
		
			printf("Termino el pid hijo\n");
		}
		else
		{
			printf("Esperando por el hijo\n");
			wait();
			printf("Termino padre e hijo \n");
		}
	return 0; 
}