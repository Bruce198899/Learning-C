#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
#define MAXLENTH 100000
int main(void)
{
	int n=0;
	cin>>n;
	int CurrentSize=0;//=maxsize
	long long heap[MAXLENTH];
	long long heapb[2*MAXLENTH];
	long long heapbR[2*MAXLENTH];
	for(int i=0;i<n;i++)
		cin>>heap[CurrentSize++];

	int CurrentPos=(CurrentSize-2)/2;
	while(CurrentPos>=0)
	{
		//siftDown(CurrentPos as start,CurrentSize-1 as m)
		{int i=CurrentPos,j=2*CurrentPos+1;
		long long temp=heap[i];
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

	for(int i=0;i<CurrentSize;i++)	heapb[i]=heap[i],heapbR[i]=heap[i];//把heap的东西复制到heapb里

	long long totalA=0;
	for(int k=0;k<n-1;k++)
	{
		long long  first,second;

		first=heap[0];
		heap[0]=heap[CurrentSize-1];
		CurrentSize--;

		//siftDown(0,currentSize-1)
		{
			int i=0,j=2*i+1;
			long long temp=heap[i];
			while(j<=CurrentSize-1)
			{
				if(j<CurrentSize-1&&heap[j]>heap[j+1]) j++;
				if(temp<=heap[j]) break;
				else
				{
					heap[i]=heap[j];i=j;j=2*j+1;
				}
			}
			heap[i]=temp;
		}

		second=heap[0];
		heap[0]=heap[CurrentSize-1];
		CurrentSize--;

		{
			int i=0,j=2*i+1;
			long long temp=heap[i];
			while(j<=CurrentSize-1)
			{
				if(j<CurrentSize-1&&heap[j]>heap[j+1]) j++;
				if(temp<=heap[j]) break;
				else
				{
					heap[i]=heap[j];i=j;j=2*j+1;
				}
			}
			heap[i]=temp;
		}

		//cout<<first<<' '<<second<<endl;
		long long x=first+second;
		totalA+=x;
		//cout<<x<<endl;
		heap[CurrentSize]=x;

		//siftUp(currentSize)
		{
			int j=CurrentSize,i=(j-1)/2;
			long long temp=heap[j];
			while(j>0)
			{
				if(heap[i]<=temp) break;
				else {heap[j]=heap[i];j=i;i=(i-1)/2;}
			}
			heap[j]=temp;
		}

		CurrentSize++;
		//for(int i=0;i<CurrentSize;i++) cout<<heap[i]<<' ';
		//cout<<endl;
	}
	char choice[5];
	cin>>choice;
	if(strcmp("BAD",choice)==0) cout<<totalA;
	else
	{
		long long totalB=0;
		int CurrentSizeb=n,CurrentSizebR=n;
		//heapb[currentsizeb]是小根堆,heapbR[CurrentSizeb]是大根堆

		int CurrentPosbR=(CurrentSizebR-2)/2;
		while(CurrentPosbR>=0)
		{
			//siftDown(CurrentPos as start,CurrentSize-1 as m)
			{
				int i=CurrentPosbR,j=2*CurrentPosbR+1;
				long long temp=heapbR[i];
				while(j<=CurrentSizebR-1)
				{
					if(j<CurrentSizebR-1&&heapbR[j]<heapbR[j+1]) j++;
					if(temp>=heapbR[j]) break;
					else
					{
						heapbR[i]=heapbR[j];i=j;j=2*j+1;
					}
				}
				heapbR[i]=temp;
			}
			CurrentPosbR--;
		}

		//for(int i=0;i<CurrentSizebR;i++) cout<<heapbR[i]<<'R';cout<<endl;//验证大根堆是否正常

		long long heapdet[2*MAXLENTH];//大根堆删掉，而小根堆没有删掉的那些东西
		int CurrentSizedet=0;
		int q;
		char choice;
		cin>>q;
		for(int round=0;round<q;round++)
		{
			cin>>choice;
			switch(choice)
			{
			case 'D':
				{
					//把heapbR的最大元素加入heapdet
					heapdet[CurrentSizedet]=heapbR[0];
					//siftUp(CurrentSizedet)
					{
						int j=CurrentSizedet,i=(j-1)/2;
						long long temp=heapdet[j];
						while(j>0)
						{
							if(heapdet[i]<=temp) break;
							else {heapdet[j]=heapdet[i];j=i;i=(i-1)/2;}
						}
						heapdet[j]=temp;
					}
					CurrentSizedet++;
			//		for(int i=0;i<CurrentSizedet;i++) cout<<heapdet[i]<<'D';cout<<endl;

					//对heapbR出堆，然后加入到heapdet里面
					heapbR[0]=heapbR[CurrentSizebR-1];
					CurrentSizebR--;
					//siftDown(0,currentSizebR-1)
					{
						int i=0,j=2*i+1;
						long long temp=heapbR[i];
						while(j<=CurrentSizebR-1)
						{
							if(j<CurrentSizebR-1&&heapbR[j]<heapbR[j+1]) j++;
							if(temp>=heapbR[j]) break;
							else
							{
								heapbR[i]=heapbR[j];i=j;j=2*j+1;
							}
						}
						heapbR[i]=temp;
					}

				//	for(int i=0;i<CurrentSizebR;i++) cout<<heapbR[i]<<'R';cout<<endl;
					break;
				}
			case 'E':
				{
					while(CurrentSizedet!=0&&heapdet[0]==heapb[0])
					{
						//heapb退
						heapb[0]=heapb[CurrentSizeb-1];
						CurrentSizeb--;

						{
							int i=0,j=2*i+1;
							long long temp=heapb[i];
							while(j<=CurrentSizeb-1)
							{
								if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
								if(temp<=heapb[j]) break;
								else
								{
									heapb[i]=heapb[j];i=j;j=2*j+1;
								}
							}
							heapb[i]=temp;
						}

						//heapdet退
						heapdet[0]=heapdet[CurrentSizedet-1];
						CurrentSizedet--;

						{int i=0,j=2*i+1;
						long long temp=heapdet[i];
						while(j<=CurrentSizedet-1)
						{
							if(j<CurrentSizedet-1&&heapdet[j]>heapdet[j+1]) j++;
							if(temp<=heapdet[j]) break;
							else
							{
								heapdet[i]=heapdet[j];i=j;j=2*j+1;
							}
						}
						heapdet[i]=temp;}
					}
				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';cout<<endl;
					//for(int i=0;i<CurrentSizedet;i++) cout<<heapdet[i]<<'D';cout<<endl;
					//如果heapdet不为空，而且heapb的最小元素是heapdet的最小元素，则二者均直接退出而不执行操作，同时再次试图删除heapb
					//的最小元素。
					//如果以上条件没有达成，则退出heapr的最小元素
					heapb[0]=heapb[CurrentSizeb-1];
					CurrentSizeb--;
					{
						int i=0,j=2*i+1;
						long long temp=heapb[i];
						while(j<=CurrentSizeb-1)
						{
							if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
							if(temp<=heapb[j]) break;
							else
							{
								heapb[i]=heapb[j];i=j;j=2*j+1;
							}
						}
						heapb[i]=temp;
					}
				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';cout<<endl;
					break;
				}
			default:
				{
					int datatemp;
					cin>>datatemp;
					heapb[CurrentSizeb]=datatemp;

					//siftUp(currentSizeb)
					{
						int j=CurrentSizeb,i=(j-1)/2;
						long long temp=heapb[j];
						while(j>0)
						{
							if(heapb[i]<=temp) break;
							else {heapb[j]=heapb[i];j=i;i=(i-1)/2;}
						}
						heapb[j]=temp;
					}
					CurrentSizeb++;
				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';cout<<endl;
					//直接同时维护到heapb和heapbR里面
					heapbR[CurrentSizebR]=datatemp;
					{
						int j=CurrentSizebR,i=(j-1)/2;
						long long temp=heapbR[j];
						while(j>0)
						{
							if(heapbR[i]>=temp) break;
							else {heapbR[j]=heapbR[i];j=i;i=(i-1)/2;}
						}
						heapbR[j]=temp;
					}
					CurrentSizebR++;
			//		for(int i=0;i<CurrentSizebR;i++) cout<<heapbR[i]<<'R';cout<<endl;
					break;
				}
			}
		}
		int CurrentSizebT=CurrentSizeb,CurrentSizedetT=CurrentSizedet;
		for(int k=0;k<CurrentSizebT-CurrentSizedetT-1;k++)//里面这个数字是真实的可以用于做Huffman的堆中元素数量
		{
			long long first,second;

			while(CurrentSizedet!=0&&heapdet[0]==heapb[0])
			{
				//heapb退
				heapb[0]=heapb[CurrentSizeb-1];
				CurrentSizeb--;

				{
					int i=0,j=2*i+1;
					long long temp=heapb[i];
					while(j<=CurrentSizeb-1)
					{
						if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
						if(temp<=heapb[j]) break;
						else
						{
							heapb[i]=heapb[j];i=j;j=2*j+1;
						}
					}
					heapb[i]=temp;
				}

				//heapdet退
				heapdet[0]=heapdet[CurrentSizedet-1];
				CurrentSizedet--;

				{int i=0,j=2*i+1;
				long long temp=heapdet[i];
				while(j<=CurrentSizedet-1)
				{
					if(j<CurrentSizedet-1&&heapdet[j]>heapdet[j+1]) j++;
					if(temp<=heapdet[j]) break;
					else
					{
						heapdet[i]=heapdet[j];i=j;j=2*j+1;
					}
				}
				heapdet[i]=temp;}
			}
//
		//	for(int i=0;i<CurrentSizedet;i++) cout<<heapdet[i]<<'D';cout<<endl;

			first=heapb[0];
			heapb[0]=heapb[CurrentSizeb-1];
			CurrentSizeb--;

			//siftDown(0,currentSizeb-1)
			{
				int i=0,j=2*i+1;
				long long temp=heapb[i];
				while(j<=CurrentSizeb-1)
				{
					if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
					if(temp<=heapb[j]) break;
					else
					{
						heapb[i]=heapb[j];i=j;j=2*j+1;
					}
				}
				heapb[i]=temp;
			}

		//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';cout<<endl;

			while(CurrentSizedet!=0&&heapdet[0]==heapb[0])
			{
				//heapb退
				heapb[0]=heapb[CurrentSizeb-1];
				CurrentSizeb--;

				{
					int i=0,j=2*i+1;
					long long temp=heapb[i];
					while(j<=CurrentSizeb-1)
					{
						if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
						if(temp<=heapb[j]) break;
						else
						{
							heapb[i]=heapb[j];i=j;j=2*j+1;
						}
					}
					heapb[i]=temp;
				}

				//heapdet退
				heapdet[0]=heapdet[CurrentSizedet-1];
				CurrentSizedet--;

				{int i=0,j=2*i+1;
				long long temp=heapdet[i];
				while(j<=CurrentSizedet-1)
				{
					if(j<CurrentSizedet-1&&heapdet[j]>heapdet[j+1]) j++;
					if(temp<=heapdet[j]) break;
					else
					{
						heapdet[i]=heapdet[j];i=j;j=2*j+1;
					}
				}
				heapdet[i]=temp;}
			}

			//for(int i=0;i<CurrentSizedet;i++) cout<<heapdet[i]<<'D';cout<<endl;

			second=heapb[0];
			heapb[0]=heapb[CurrentSizeb-1];
			CurrentSizeb--;
		//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';cout<<endl;
			{
				int i=0,j=2*i+1;
				long long temp=heapb[i];
				while(j<=CurrentSizeb-1)
				{
					if(j<CurrentSizeb-1&&heapb[j]>heapb[j+1]) j++;
					if(temp<=heapb[j]) break;
					else
					{
						heapb[i]=heapb[j];i=j;j=2*j+1;
					}
				}
				heapb[i]=temp;
			}
			//for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';cout<<endl;

		//	cout<<first<<' '<<second<<endl;
			long long x=first+second;
			totalB+=x;
		//cout<<x<<endl;
			heapb[CurrentSizeb]=x;

			//siftUp(currentSizeb)
			{
				int j=CurrentSizeb,i=(j-1)/2;
				long long temp=heapb[j];
				while(j>0)
				{
					if(heapb[i]<=temp) break;
					else {heapb[j]=heapb[i];j=i;i=(i-1)/2;}
				}
				heapb[j]=temp;
			}

			CurrentSizeb++;
			//for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<' ';
		//	cout<<endl;
		}
		cout<<totalA<<endl<<totalB<<endl;;
	}

	//在用huffman数heapb做计数的时候，如果遇到的数字在heapdet里面是最小元素（而且currentsizedet不是0），那么要直接跳过这个再次进行出堆，直到之前的条件不满足。
	return 0;
}
