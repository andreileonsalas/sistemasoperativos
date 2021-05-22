#include <stdio.h>
#include <time.h>
#include <stdlib.h>


// los numeros de pagina y los frames que solo se puede de 1 a 7
int n, fr[7];
//int pageRandomNumbers[10] = { 0, 3, 5, 4, 3, 1, 2, 8, 2, 2};
int pageRandomNumbers[10] = { 1, 2, 3, 4, 5, 1, 1, 1, 1, 1};
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
    int n = 10;
    scanf("%d", &n);
    //page sequences size enter like 1 2 3 4 5 1 1 1 1 1
    printf("\nEnter sequence numbers:");
    for (i = 0; i < n; i++)  //accepting sequence
        //scanf("%d", &pageRandomNumbers[i]); //take input of each page into pg array
    do
    { //Choose any of the option below
        printf("\n\tMENU\n");
        printf("\n1)FIFO");
        printf("\n2)OPTIMAL");
        printf("\n3)LRU");
        printf("\n4)Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            fifo();
            break;

        case 2:
            optimal();
            break;

        case 3:
            lru();
            break;
        }
    } while (ch != 4);
    getchar();
}

void fifo()
{
    /*
            * This part will do the the fifo algorithm according to the book
            */
    int i, f, r, s, count, flag, num, psize;
    f = 0;
    r = 0;
    s = 0;
    flag = 0;
    count = 0;
    printf("\nEnter size of the frame:");
    scanf("%d", &psize);        //frame size up to 7
    for (i = 0; i < psize; i++) //loop repeat itself
    {
        fr[i] = -1; // all frame is equal Null
    }
    while (s < n)
    {
        flag = 0;    // flag is 0
        num = pageRandomNumbers[s]; //all page is assinge to num variable
        //loop start repeat itself according to framesize (psize)
        for (i = 0; i < psize; i++)
        {

            if (num == fr[i]) //checking page size if equal put it and no then error occur
            {
                s++;
                flag = 1;
                break;
            }
        }
        if (flag == 0) //checking the framesize
        {
            if (r < psize)
            {
                fr[r] = pageRandomNumbers[s]; //assign fr frame size to page size
                r++;
                s++;
                count++; //the default
            }
            else
            {
                if (f < psize)
                {
                    fr[f] = pageRandomNumbers[s];
                    s++;
                    f++;
                    count++; //Default
                }
                else
                    f = 0;
            }
        }
        printf("\n");
        for (i = 0; i < psize; i++)
        {
            printf("%d\t", fr[i]);
        }
    }
    printf("\nTotal number of page count %d", count); //print the final result
    getchar();

    return;
}

void optimal()
{
    /*
            * The optimal drive algorithm that will do the calculation
            */
    int count[10], i, j, k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x;
    fault = 0; //fault count in variable store
    dist = 0;
    k = 0;
    printf("\nEnter the frame size:");
    scanf("%d", &f);
    //initializing distance and frame size in array
    for (i = 0; i < f; i++)
    {
        count[i] = 0;
        fr[i] = -1;
    }
    for (i = 0; i < n; i++) //first step of the loop
    {
        flag = 0;               // flag to  0
        temp = pageRandomNumbers[i];           //same as above
        for (j = 0; j < f; j++) //second step of the loop
        {
            if (temp == fr[j])
            {
                flag = 1;
                break;
            }
        }

        if ((flag == 0) && (k < f)) //flag is zero
        {
            fault++;      //default occur
            fr[k] = temp; // Put this into temp
            k++;
        }
        // The searching part
        else if ((flag == 0) && (k == f))
        {
            fault++;
            for (cnt = 0; cnt < f; cnt++) //third part of the  loop
            {
                current = fr[cnt];
                for (c = i; c < n; c++) //fourth step of the
                {
                    if (current != pageRandomNumbers[c]) // set current frame size
                        count[cnt]++;
                    else
                        break;
                }
            }
            max = 0; // max equal to zero

            for (m = 0; m < f; m++) //fifth  step of the start
            {
                if (count[m] > max)
                {
                    max = count[m];
                    p = m;
                }
            }
            fr[p] = temp; // Put this in the temp
        }
        printf("\n");
        for (x = 0; x < f; x++) // sixth  and final loop
        {
            printf("%d\t", fr[x]); //print each numbers
        }                          //sixth loop end
    }
    printf("\nTotal number of page count %d", fault); // show the total step depending on the frame size and page size
    getchar();
    return;
}

void lru()
{
    /*
            * The lru algorithm in default
            */
    int count[10], i, j, k, fault, f, flag, temp, current, c, dist, max, m, cnt, p, x;
    fault = 0;
    dist = 0;
    k = 0;
    printf("\nEnter the frame size:");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
    {
        count[i] = 0;
        fr[i] = -1;
    }
    for (i = 0; i < n; i++)
    {
        flag = 0;
        temp = pageRandomNumbers[i];           // If temp have empty we put some value in pg
        for (j = 0; j < f; j++) //second loop start
        {
            if (temp == fr[j]) //compare both value
            {
                flag = 1;
                break;
            }
        }                           //second loop end
        if ((flag == 0) && (k < f)) //decide if  this condition is exceute
        {
            fault++;      //count the fault that occurs in frame
            fr[k] = temp; //frame store in temp
            k++;          //counting the frame replaced.
        }
        else if ((flag == 0) && (k == f))
        {
            fault++; //count the default
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
                    max = count[m]; // is max  equal count
                    p = m;          //then p store the loop times
                }
            }
            fr[p] = temp;
        }
        printf("\n");
        for (x = 0; x < f; x++)
        {
            printf("%d\t", fr[x]); //print all the page one by one
        }
    }
    printf("\nTotal number of page count %d", fault); //print the total number count in paging size
    getchar();
    return;
}