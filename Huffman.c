#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
int main(void)
{
	int n=0;
	cin>>n;
	int CurrentSize=0;//=maxsize
	long heap[10000];
	long heapb[20000];
	for(int i=0;i<n;i++)
		cin>>heap[CurrentSize++];

	int CurrentPos=(CurrentSize-2)/2;
	while(CurrentPos>=0)
	{
		//siftDown(CurrentPos as start,CurrentSize-1 as m)
		{int i=CurrentPos,j=2*CurrentPos+1;
		long temp=heap[i];
		while(j<=CurrentSize-1)
		{
			if(j<CurrentSize-1&&heap[j]>heap[j+1]) j++;
			if(temp<=heap[j]) break;
			else
			{
				heap[i]=heap[j];i=j;j=2*j+1;
			}
		}
		heap[i]=temp;}
		CurrentPos--;
	}
	//for(int i=0;i<n;i++) cout<<heap[i];

	for(int i=0;i<CurrentSize;i++)	heapb[i]=heap[i];//把heap的东西复制到heapb里

	long totalA=0;
	for(int k=0;k<n-1;k++)
	{
		long  first,second;

		first=heap[0];
		heap[0]=heap[CurrentSize-1];
		CurrentSize--;

		//siftDown(0,currentSize-1)
		{int i=0,j=2*i+1;
		long temp=heap[i];
		while(j<=CurrentSize-1)
		{
			if(j<CurrentSize-1&&heap[j]>heap[j+1]) j++;
			if(temp<=heap[j]) break;
			else
			{
				heap[i]=heap[j];i=j;j=2*j+1;
			}
		}
		heap[i]=temp;}

		second=heap[0];
		heap[0]=heap[CurrentSize-1];
		CurrentSize--;

		{int i=0,j=2*i+1;
		long temp=heap[i];
		while(j<=CurrentSize-1)
		{
			if(j<CurrentSize-1&&heap[j]>heap[j+1]) j++;
			if(temp<=heap[j]) break;
			else
			{
				heap[i]=heap[j];i=j;j=2*j+1;
			}
		}
		heap[i]=temp;}

		//cout<<first<<' '<<second<<endl;
		long x=first+second;
		totalA+=x;
		//cout<<x<<endl;
		heap[CurrentSize]=x;

		//siftUp(currentSize)
		{int j=CurrentSize,i=(j-1)/2;
		long temp=heap[j];
		while(j>0)
		{
			if(heap[i]<=temp) break;
			else {heap[j]=heap[i];j=i;i=(i-1)/2;}
		}
		heap[j]=temp;}

		CurrentSize++;
		//for(int i=0;i<CurrentSize;i++) cout<<heap[i]<<' ';
		//cout<<endl;
	}
	char choice[4];
	cin>>choice;
	if(strcmp("BAD",choice)==0) cout<<totalA;
	else
	{
		int CurrentSizeb=CurrentSize;
		int q;
		char choice;
		int state=1;//0:上一次是最大堆；1：上一次是最小堆
		cin>>q>>choice;
		for(int i=0;i<q;i++)
		{
			switch(choice)
			{
			case 'D'://对heapb做删除最大权重节点处理
				{
					if(state=1)
					{
					int CurrentPosb=(CurrentSizeb-2)/2;
					while(CurrentPosb>=0)
					{
					//siftDown(CurrentPos as start,CurrentSize-1 as m)
					{int i=CurrentPosb,j=2*CurrentPosb+1;
					long temp=heapb[i];
					while(j<=CurrentSizeb-1)
					{
						if(j<CurrentSizeb-1&&heapb[j]<heapb[j+1]) j++;
						if(temp>=heapb[j]) break;
						else
						{
							heapb[i]=heapb[j];i=j;j=2*j+1;
						}
					}
					heapb[i]=temp;}
					CurrentPosb--;
					}
					}

					heapb[0]=heapb[CurrentSizeb-1];
					CurrentSizeb--;

					//siftDown(0,currentSize-1)
					{int i=0,j=2*i+1;
					long temp=heapb[i];
					while(j<=CurrentSizeb-1)
					{
						if(j<CurrentSizeb-1&&heapb[j]<heapb[j+1]) j++;
						if(temp>=heapb[j]) break;
						else
						{
							heapb[i]=heapb[j];i=j;j=2*j+1;
						}
					}
					heapb[i]=temp;}


				}
			case 'E'://对heapb做删除最小权重节点处理
				{
					int CurrentPosb=(CurrentSizeb-2)/2;
					while(CurrentPosb>=0)
					{
						//siftDown(CurrentPos as start,CurrentSize-1 as m)
						{int i=CurrentPosb,j=2*CurrentPosb+1;
						long temp=heapb[i];
						while(j<=CurrentSizeb-1)
						{
							if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
							if(temp<=heapb[j]) break;
							else
							{
								heapb[i]=heapb[j];i=j;j=2*j+1;
							}
						}
						heapb[i]=temp;}
						CurrentPosb--;
					}

						heapb[0]=heapb[CurrentSizeb-1];
						CurrentSizeb--;

						//siftDown(0,currentSize-1)
						{int i=0,j=2*i+1;
						long temp=heapb[i];
						while(j<=CurrentSizeb-1)
						{
							if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
							if(temp<=heapb[j]) break;
							else
							{
								heapb[i]=heapb[j];i=j;j=2*j+1;
							}
						}
						heapb[i]=temp;}
				}
			default://对heapb做插入节点处理
				{
					
					cin>>heapb[CurrentSizeb];



				}
			}
		}
		//处理完后再输出哈夫曼树的答案
	}
return 0;
}
