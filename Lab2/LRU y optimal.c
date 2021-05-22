#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// los numeros de pagina y los frames que solo se puede de 1 a 7
int n, pageRandomNumbers[10], fr[7];
//los 3 algoritmos
void fifo();
void optimal();
void lru();

int main()
{
    // menu para poner los 3 algoritmos en 1 solo
    srand(time(NULL));
    int i, ch;
    printf("\nIngrese las paginas, del 0 al 9: ");
    n = 0;
    //hasta 10
    scanf("%d", &n);
    //page sequences size enter like 1 2 3 4 5 1 1 1 1 1
    printf("\nIngrese la secuencia de numeros (por ejemplo 1 2 3 4 5 1 1 1 1 1):");
    for (i = 0; i < n; i++)                 
        scanf("%d", &pageRandomNumbers[i]); // leer los numeros
    do
    { //Choose any of the option below
        printf("\nmenu\n");
        printf("\n1)usar optimal");
        printf("\n2)usar LRU");
        printf("\n3)salir");
        printf("\nIngrese su seleccion:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            optimal();
            break;

        case 2:
            lru();
            break;
        }
    } while (ch != 3);
    getchar();
}

void optimal()
{
    int count[10], i, j, k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x;
    fault = 0; 
    dist = 0;
    k = 0;
    printf("\nIngrese el tamano del frame hasta 7 maximo:");
    scanf("%d", &f);
    for (i = 0; i < f; i++)
    {
        count[i] = 0;
        fr[i] = -1;
    }
    for (i = 0; i < n; i++) 
    {
        flag = 0;                    
        temp = pageRandomNumbers[i]; 
        for (j = 0; j < f; j++)      
        {
            if (temp == fr[j])
            {
                flag = 1;
                break;
            }
        }

        if ((flag == 0) && (k < f)) 
        {
            fault++;      
            fr[k] = temp; 
            k++;
        }

        else if ((flag == 0) && (k == f))
        {
            fault++;
            for (cnt = 0; cnt < f; cnt++) 
            {
                current = fr[cnt];
                for (c = i; c < n; c++) 
                {
                    if (current != pageRandomNumbers[c]) 
                        count[cnt]++;
                    else
                        break;
                }
            }
            max = 0;

            for (m = 0; m < f; m++) 
            {
                if (count[m] > max)
                {
                    max = count[m];
                    p = m;
                }
            }
            fr[p] = temp; 
        }
        printf("\n");
        for (x = 0; x < f; x++) 
        {
            printf("%d\t", fr[x]); 
        }                          
    }
    printf("\nNumero total de faltas: %d", fault); 
    getchar();
    return;
}

void lru()
{

    int count[10], i, j, k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x;
    fault = 0;
    dist = 0;
    k = 0;
    printf("\nIngrese el tamano del frame hasta 7 maximo:");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
    {
        count[i] = 0;
        fr[i] = -1;
    }
    for (i = 0; i < n; i++)
    {
        flag = 0;
        temp = pageRandomNumbers[i]; 
        for (j = 0; j < f; j++)      
        {
            if (temp == fr[j]) 
            {
                flag = 1;
                break;
            }
        }                      
        if ((flag == 0) && (k < f))
        {
            fault++;      
            fr[k] = temp; 
            k++;          
        }
        else if ((flag == 0) && (k == f))
        {
            fault++; 
            for (cnt = 0; cnt < f; cnt++)
            {
                current = fr[cnt];
                for (c = i; c > 0; c--)
                {
                    if (current != pageRandomNumbers[c])
                        count[cnt]++;
                    else
                        break;
                }
            }
            max = 0;
            for (m = 0; m < f; m++)
            {
                if (count[m] > max)
                {
                    max = count[m]; 
                    p = m;          
                }
            }
            fr[p] = temp;
        }
        printf("\n");
        for (x = 0; x < f; x++)
        {
            printf("%d\t", fr[x]); 
        }
    }
    printf("\nNumero total de faltas: %d", fault); 
    getchar();
    return;
}