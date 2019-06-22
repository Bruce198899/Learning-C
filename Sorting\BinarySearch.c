#include <iostream>
#include <cstdlib>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
struct NODE {int N;string str;};
void SiftDown(NODE**Heap,int start,int m)//最小堆的下滑调整
{
	int i=start;
	int j=2*i+1;
	string temp=Heap[i]->str;
	int tempN=Heap[i]->N;
	while(j<=m)
	{
		if(j<m&&Heap[j]->str>Heap[j+1]->str)	j++;
		if(temp<=Heap[j]->str)	break;
		else {Heap[i]->str=Heap[j]->str;Heap[i]->N=Heap[j]->N;i=j;j=2*j+1;}
	}
	Heap[i]->str=temp;
	Heap[i]->N=tempN;
}
int BinarySearch(NODE**Heap,int high,string str)
{
    int low=0,mid;
    while(low<=high)
	{
        mid=low+(high-low)/2;
		if(Heap[mid]->str==str)	return mid;
		else if(Heap[mid]->str>str)	high=mid-1;
		else low=mid+1;
    }
    return -1;
}
int HeadBinarySearch(NODE**Heap, int low, int high, string str)
{
	cout<<str.size();
    while(low<=high)
    {
        int middle=(low+high)/2;
		if(Heap[middle]->str.substr(0,str.size())<str)
			{low=middle+1;cout<<"AA";}
        else
        {
			if(Heap[middle-1]->str.substr(0,str.size())<str)	{cout<<"AAb";return  middle;}
			else {cout<<"AAc";high=middle-1;}
        }
    }
    return -1;//寻找失败，在本题中不存在这种可能。
}
int EndBinarySearch(NODE**Heap, int low,int high,string str)
{
    while(low<=high)
    {
        int middle=(low+high)/2;
		if(Heap[middle]->str.substr(0,str.size())==str)
        {
			if(Heap[middle+1]->str.substr(0,str.size())>str)	{cout<<"AAd";return middle;}
			else {cout<<"AAf";low=middle+1;}
        }
		else if(Heap[middle]->str.substr(0,str.size())>str)	{cout<<"AAe";;high=middle-1;}
    }
    return -1;
}
int main()
{
	int n,m,p=0;
	cin>>n;
	NODE**Heap=(NODE**)malloc(sizeof(NODE*)*n);//堆//存放节点的指针
	for(int i=0;i<n;i++)
	{
		Heap[i]=new NODE;
		Heap[i]->N=i+1;
		cin>>Heap[i]->str;
	}
	//for(int i=0;i<n;i++)
	//{
	///	cout<<Heap[i]->str<<"BB"<<endl;
	//}

	int CurrentSize=n;
	int CurrentPos=(CurrentSize-2)/2;
	while(CurrentPos>=0)
	{
		SiftDown(Heap,CurrentPos,CurrentSize-1);
		CurrentPos--;
	}
	NODE**HeapS=(NODE**)malloc(sizeof(NODE*)*n);//最小顺序表
	for(int i=0;i<n;i++)
	{
		//cout<<Heap[0]->str<<"AA"<<endl;
		HeapS[i]=Heap[0];
		Heap[0]=Heap[CurrentSize-1];
		CurrentSize--;
		SiftDown(Heap,0,CurrentSize-1);
	}
	for(int i=0;i<n;i++)
		cout<<HeapS[i]->N<<' ';
	for(int i=0;i<n;i++)
	{
		cout<<HeapS[i]->str<<endl;
	}
	cin>>m;
	string temp;
	for(int i=0;i<m;i++)
	{
		cin>>temp;
		cout<<BinarySearch(HeapS,n,temp)+1;
	}
	cin>>p;
	for(int i=0;i<p;i++)
	{
		cin>>temp;
		int A=HeadBinarySearch(HeapS,0,n-1,temp);
		int B=EndBinarySearch(HeapS,A,n-1,temp);
		cout<<B-A<<endl;
	}
	return 0;
}
