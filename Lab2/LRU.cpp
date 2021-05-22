#include<stdio.h>
#include<stdlib.h>
#include<time.h> 

//Write a program that implements the FIFO and LRU page-replacement algorithms presented in this chapter.
//First, generate a random pagereference string where page numbers range from 0 to 9.
//Apply the random page-reference string to each algorithm, and record the number of page faults incurred by each algorithm.
//Implement the replacement algorithms so that the number of page frames can vary from 1 to 7.
//Assume that demand paging is used.

void printfunction(int a[], int frame_number);

int main()
{
	//先寫死 
//	int page_string[12]={4,3,2,1,4,3,5,4,3,2,1,5};
	int page_string[12];
	srand(time(NULL));
//	int random;
	int i;
	for(i=0;i<12;i++)
	{
		page_string[i]=rand()%10;	
	}
	printf("page reference string is :\n");
	printfunction(page_string, 12);

	int page_frame;
	
	printf("please enter page frame : ");
	scanf("%d", &page_frame);
	printf("\n");
	
	int frame[page_frame];
	for(i=0;i<page_frame;i++)
	{
		frame[i] = -1;
	}
	
	// FIFO
	int fifo_fault = 0;
	int fifo_order = 0;
	int turn = 0;  //number of page input
	while(turn<12)
	{
		for(i=0;i<page_frame;i++)
		{
			if(page_string[turn]==frame[i])
			{
				break;
			}
			if(i==(page_frame-1))
			{
				fifo_fault++;
				frame[fifo_order]=page_string[turn];
				fifo_order++;
			}	
		}
		printfunction(frame, page_frame);
		
//		fifo_order++;
		turn++;
		
		if(fifo_order==page_frame)
		{
			fifo_order=0;
		}
	}
	
	printf("\nFIFO page fault = %d\n\n", fifo_fault);
//==================================================================//
	// LRU
	// 標 LRU 代表 LRU參數
	
	int frame_LRU[page_frame];
	for(i=0;i<page_frame;i++)
	{
		frame_LRU[i] = -1;
	}
	
	int LRU_fault = 0;
	int turn_LRU = 0;  //number of page input
	int write_position = 0; //插入值的地方 
	
	int k;
	//   最近放進來的  會放在 index write_position 
	while(turn_LRU<12)
	{
		for(i=0;i<page_frame;i++)
		{
			if(page_string[turn_LRU]==frame_LRU[i])
			{
				write_position--;
				for(k=i;k<write_position;k++)
				{
					frame_LRU[k]=frame_LRU[k+1];
				}
				frame_LRU[write_position]=page_string[turn_LRU];
				write_position++;
				break;
			}
			
			if(i==(page_frame-1))
			{
				LRU_fault++;
				if(write_position!=page_frame)
				{
					frame_LRU[write_position]=page_string[turn_LRU];
					write_position++;
				}
				else
				{
					for(k=0;k<(page_frame-1);k++)
					{
						frame_LRU[k]=frame_LRU[k+1];
					}
					frame_LRU[page_frame-1]=page_string[turn_LRU];
				}
			}
		}
		printfunction(frame_LRU, page_frame);
		turn_LRU++;
	}
	 
	printf("\nLRU page fault = %d\n", LRU_fault);
	
	return 0;  
}

void printfunction(int a[], int frame_number)
{
	int t;
	for(t=0;t<frame_number;t++)
	{
		printf("%d ", a[t]);
	}
	printf("\n");
} 