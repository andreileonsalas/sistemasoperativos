//https://gist.github.com/Jabiribn/e58bf13c678953891900e5f982b48037

//how to run 
//gcc -pthread -std=c99 -o 4.21 4.21.c
//./4.21

#include<stdio.h>
#include<pthread.h>
int arr[50],n,i;

void *th()
{
	int sum=0;
	float average;
	printf("Ingrese cuantos elementos va a ingresar: ");
	//%d es para decirle que lea un integer
	scanf("%d",&n);
	printf("Ahora ingrese cada valor, separado por un espacio: ");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
		printf("\n Revisando numero %d ",arr[i]);
	}
	for(i=0;i<n;i++)
		{
			//printf("\n TH0 recorriendo %d de %d",i,n);
			sum=sum+arr[i];
		}
	average=sum/n;
	printf("The average value is %f",average);
}
void *th1()
{


	int temp=arr[0];
	for(int i=1;i<n;i++)
		{
			//printf("\n TH1 recorriendo %d de %d",i,n);
			if(temp>arr[i])
			{
			temp=arr[i];
			}
		}
	printf("\nThe Minimum  value is %d",temp);

}
void *th2()
{

	int temp=arr[0];
	for(int i=1;i<n;i++)
		{
			//printf("\n TH2 recorriendo %d de %d",i,n);
			if(temp<arr[i])
			{
			temp=arr[i];
			}
		}
	printf("\nThe Maximum  value is %d",temp);
	}
int main()
{
int n,i;
pthread_t t1;
pthread_t t2;
pthread_t t3;
	n=pthread_create(&t1,NULL,&th,NULL);
	pthread_join(t1,NULL);
	//printf("\n t1 termino y el valor es %d",n);
	n=pthread_create(&t2,NULL,&th1,NULL);
    pthread_join(t2,NULL);
	//printf("\n t2 termino y el valor es %d",n);
	n=pthread_create(&t3,NULL,&th2,NULL);
    pthread_join(t3,NULL);
	//printf("\n t3 termino y el valor es %d",n);

}