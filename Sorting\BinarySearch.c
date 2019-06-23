/*【作业编号】a
上机作业11：排序 二分
【问题描述】
有3个问题：
1、给你n个互不相同的字符串，按照读入顺序编号为1到n的整数，输出它们按照字典序从小到大排序后的结果。具体为按照排序后的顺序输出各个字符串的编号。
2、给你m个在问题1中出现过的字符串，输出它们在问题1中排序后的排名（排名从小到大从1编号到n）。
3、给你p个字符串，问每个字符串是多少个在问题1中的字符串的前缀。
【输入描述】
输入第一行包含一个正整数n。接下来n行，每行描述一个问题1中的字符串。
接下来一行包含一个正整数m。接下来m行，每行描述一个问题2中的字符串。
接下来一行包含一个正整数p。接下来p行，每行描述一个问题3中的字符串。
保证字符串仅由小写字母构成，且不包含空串。
【输出描述】
输出3行。
第一行包含n个空格隔开的整数，表示问题1中的字符串排序后的编号。
第二行包含m个空格隔开的整数，表示问题2的每个字符串在问题1中排序后的排名。
第三行包含p个空格隔开的整数，表示问题1的字符串中以问题3的每个字符串为前缀的个数。
【子任务】
不同的测试点分为5个子任务，每个子任务占20%，其区别为每个问题的字符串总长（每个字符串的长度之和）不同：
编号
每个问题字符总个数
1
500
2
2000
3
5000
4
100000
5
300000
【样例输入】
5
caaaa
aaa
baaaa
caaaai
aaaaa
5
caaaai
baaaa
aaaaa
caaaa
aaa
9
aa
ba
ca
baaaa
baaaa
b
c
caaaai
caaaai
【样例输出】
2 5 3 1 4
5 3 2 4 1
2 1 2 1 1 1 2 1 1

【提示】

这道题目只用排序是可以解决的，排序后使用二分也是能够解决的。*/

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
		//cout<<str.size();
		int middle;
		while(low<=high)
		{
			middle=(low+high)/2;
			//cout<<"ACD";
			//cout<<Heap[middle]->str.substr(0,str.size());
			if(Heap[middle]->str.substr(0,str.size())<str)
				{
					low=middle+1;
					//cout<<"AA";
			}
			else if(Heap[middle]->str.substr(0,str.size())==str)
			{
				if(middle==0||Heap[middle-1]->str.substr(0,str.size())<str)	
				{
					//cout<<"AAb";
					return  middle;
				}
				else 
				{
				//	cout<<"AAc";
					high=middle-1;
				}
			}
			else 
			{
				//cout<<"AAc";
				high=middle-1;}
		}
		return -1;
	}
	int EndBinarySearch(NODE**Heap, int low,int high,string str)
	{
		while(low<=high)
		{
			int middle=(low+high)/2;
			if(Heap[middle]->str.substr(0,str.size())==str)
			{
				if(middle==high||Heap[middle+1]->str.substr(0,str.size())>str)	
				{
					//cout<<"AAd";
					return middle;
				}
				else 
				{
					//cout<<"AAf";
					low=middle+1;
				}
			}
			else if(Heap[middle]->str.substr(0,str.size())>str)	
			{
				//cout<<"AAe";
				high=middle-1;
			}
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
		
		//for(int i=0;i<n;i++)
		//{
		//	cout<<HeapS[i]->str<<endl;
		//}
		cin>>m;
		int*mn=(int*)malloc(sizeof(int)*m);
		string temp;
		for(int i=0;i<m;i++)
		{
			cin>>temp;
			mn[i]=BinarySearch(HeapS,n,temp)+1;
		}

		cin>>p;
		int*pn=(int*)malloc(sizeof(int)*p);
		for(int i=0;i<p;i++)
		{
			cin>>temp;
			int A=HeadBinarySearch(HeapS,0,n-1,temp);
			//cout<<"A_A="<<A<<endl;
			if(A==-1){pn[i]=0;}
			else {
				int B=EndBinarySearch(HeapS,A,n-1,temp);
			//	cout<<"B_B="<<B<<endl;
				pn[i]=B-A+1;
			}
		}
		for(int i=0;i<n;i++)
			cout<<HeapS[i]->N<<' ';
		cout<<endl;
		for(int i=0;i<m;i++)
		{
			cout<<mn[i]<<' ';
		}
		cout<<endl;
		for(int i=0;i<p;i++)
		{
			cout<<pn[i]<<' ';
		}
		cout<<endl;
		return 0;
	}
