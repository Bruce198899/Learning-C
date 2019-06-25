【作业编号】
上机作业10：深度优先搜索（回溯），广度优先搜索遍历，最短路，最短路的优化
【问题描述】
寻路是很多带有地图、棋盘的游戏中非常重要和基础的概念。当我们对一个单位执行最简单的“移动”、“攻击”操作等时，单位肯定不能沿直线向目的地移动，此时就需要启动一次寻路算法。
例如在“星际争霸1”中，可以做到玩家12个单位一起寻路不卡，并且单位会沿着一条较短的路线移动。但由于算法和计算资源的限制，当时的游戏存在当一个单位在移动途中被卡会绕远、被堵路时仍然会傻傻地尝试错误路线的问题。而在“星际争霸2”中则不存在这样的问题，而且还在寻路过程中加入了排阵型、快速部队等慢速部队、躲塔等功能。
在这里，我们要解决这样一个寻路问题：玩家在一个n×m的方格地图中，每一步可以向上下左右移动一格。地图的每个格子可能是水域，或是有一个海拔高度的地面。水域和地图之外不可到达。
设玩家所在格子的海拔高度为g，希望移动到的邻格海拔高度为h；若g≥h，那么玩家可以花费1单位的时间移动过去；若g<h，那么玩家需要花费h-g+1单位的时间才能移动过去。
现在要求出玩家到达地图中每个格子所需要的最少时间。
【输入描述】
输入第一行包含两个空格隔开的正整数n,m，表示地图的大小。
接下来n行，每行m个字符（之间没有空格隔开），表示整个方格地图。约定x坐标是上下方向，从1开始计数，从上到下依次增加；y坐标是左右方向，从1开始计数，从左到右依次增加。（相当于常见的平面直角坐标系顺时针旋转90°）对于某个位置的字符，若为#，表示这里是水域；若为0~9，表示地面，具体的数值为海拔高度。
输入最后一行包含两个空格隔开的正整数x,y，表示玩家的初始位置。保证玩家的初始位置不会是水域。
【输出描述】
输出n行，每行包含m个空格隔开的整数，分别对应玩家到达每个格子的最少时间。如果玩家无法到达某个格子，对应的位置输出-1（注意不可到达不止一种情况）。
【样例输入1】
5 5
000#0
0#0#0
000#0
##0#0
0#000
1 1
【样例输出1】
0 1 2 -1 12
1 -1 3 -1 11
2 3 4 -1 10
-1 -1 5 -1 9
-1 -1 6 7 8
【样例输入2】
7 5
01234
56789
0#0#0
32323
00000
99990
00000
1 1
【样例输出2】
0 2 4 6 8
6 8 10 12 14
7 -1 11 -1 15
11 12 14 15 17
12 13 14 15 16
22 23 24 25 17
22 21 20 19 18
【提示】
深度优先搜索（回溯）：尝试枚举所有的路线，经过每个格子时更新到达这里的最短路径。
广度优先搜索遍历：如果地图全是平地，那么每个格子被广搜遍历到的路线就是最短的路线。更进一步，如果图中权值全为1，最短路问题可以用广搜遍历解决。
最短路算法（Dijkstra或SPFA）：两个相邻格子的单向消耗时间可以作为单向边的权值，可以把模型转化为最短路。
最短路算法的优化：要进一步利用图中边数较少的性质。


#include <iostream>
#include <cstdlib>
#include <queue>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::priority_queue;
using std::vector;
struct Edge{int dest;int cost;Edge*next;};
struct Vertex{int data;Edge*adj;};
struct node{int p,w;node(int a, int b):p(a), w(b){};bool operator < (const node& b) const {return w>b.w;};};
int GetWeightNeighbor(Vertex**NodeTable,int i,int j)
{
	if(NodeTable[i]->data==-1||NodeTable[j]->data==-1) return -1;
	else 
	{
		if(NodeTable[i]->data>=NodeTable[j]->data) return 1;
		else return (NodeTable[j]->data-NodeTable[i]->data+1);
	}
}
void InitialConnect(Vertex**NodeTable,int i,int m,int totalnum)
{
			Edge* Temp;
			Edge** Cursor=&(NodeTable[i]->adj);
			if(i-m>=0)
			{
				//cout<<"上";
				Temp=new Edge;
				Temp->cost=GetWeightNeighbor(NodeTable,i,i-m);
				if(Temp->cost!=-1)
				{
				Temp->dest=i-m;
				Temp->next=NULL;
				*Cursor=Temp;
				Cursor=&(Temp->next);
				}
			}
			if(i+m<totalnum)//如果下部存在元素
			{
				Temp=(Edge*)malloc(sizeof(Edge));
				Temp->cost=GetWeightNeighbor(NodeTable,i,i+m);
				if(Temp->cost!=-1)
				{Temp->dest=i+m;
				Temp->next=NULL;
				*Cursor=Temp;
				Cursor=&(Temp->next);}
			}
			if((i+1)%m==1)//是第一个元素
			{
				Temp=new Edge;
				Temp->cost=GetWeightNeighbor(NodeTable,i,i+1);
				if(Temp->cost!=-1)
				{Temp->dest=i+1;
				Temp->next=NULL;
				*Cursor=Temp;
				Cursor=&(Temp->next);
				}
			}
			else if((i+1)%m==0)
			{
				Temp=new Edge;
				Temp->cost=GetWeightNeighbor(NodeTable,i,i-1);
				if(Temp->cost!=-1){
				Temp->dest=i-1;
				Temp->next=NULL;
				*Cursor=Temp;
				Cursor=&(Temp->next);}
			}
			else
			{
				Temp=new Edge;
				Temp->cost=GetWeightNeighbor(NodeTable,i,i+1);
				if(Temp->cost!=-1){
				Temp->dest=i+1;
				Temp->next=NULL;
				*Cursor=Temp;
				Cursor=&(Temp->next);}
				Temp=new Edge;
				Temp->cost=GetWeightNeighbor(NodeTable,i,i-1);
				if(Temp->cost!=-1){
				Temp->dest=i-1;
				Temp->next=NULL;
				*Cursor=Temp;
				Cursor=&(Temp->next);}
			}
}
int main()
{
	int n,m=0;
	scanf("%d%d",&n,&m);//n行m列的图
	int totalnum=n*m;
	Vertex**NodeTable=(Vertex**)malloc(sizeof(Vertex*)*totalnum);//记录地图节点的数组
	int k=0;//用来建立地图NodeTable的辅助变量
	for(int i=0;i<totalnum;i++)
	{	
		k=getchar();
		if(k==35) 
		{
			Vertex* TEMP=new Vertex;
			TEMP->data=-1;
			TEMP->adj=NULL;
			NodeTable[i]=TEMP;
		}
		else if(k>47&&k<58)
		{
			Vertex* TEMP=new Vertex;
			TEMP->data=k-48;
			TEMP->adj=NULL;
			NodeTable[i]=TEMP;
		}
		else i--;
	}

	for(int i=0;i<totalnum;i++)
	{
		if(NodeTable[i]->data!=-1) InitialConnect(NodeTable,i,m,totalnum);
	}
	int x,y,p;
	cin>>x>>y;
	p=(x-1)*m+y-1;
	bool *S=new bool[totalnum];
	for(int i=0;i<totalnum;i++) S[i]=false;
	int *dist=new int[totalnum];
	for(int i=0;i<totalnum;i++) dist[i]=-1;
	int *path=new int[totalnum];
	for(int i=0;i<totalnum;i++) path[i]=-1;
	dist[p]=0;
	path[p]=p;
	priority_queue<node> Queue;
	Queue.push(node(p,0));
	while(!Queue.empty())
	{
		node Front=Queue.top();
		Queue.pop();
		int tempv=Front.p;
		if(S[tempv]) continue;
		S[tempv]=true;
		for(Edge *Cursor=NodeTable[tempv]->adj;Cursor!=NULL;Cursor=Cursor->next)
		{
			int point=Cursor->dest;
			if(!S[point]&&(dist[point]==-1||dist[tempv]+Cursor->cost<dist[point]))
			{
				dist[point]=dist[tempv]+Cursor->cost;
				path[point]=tempv;
				Queue.push(node(point,dist[point]));
			}
		}
	}
	int sfs=0;
	for(int i=0;i<n;i++)
	{	
		for(int j=0;j<m;j++)
			printf("%d ",dist[sfs++]);
		cout<<endl;
	}
	return 0;
}
