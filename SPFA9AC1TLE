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
int GetWeightNeighbor(Vertex**NodeTable,int i,int j)
{
	//cout<<NodeTable[i]->data<<NodeTable[j]->data;
	if(NodeTable[i]->data==-1||NodeTable[j]->data==-1) {//cout<<"方式GW1";
	return -1;}
	else 
	{
		if(NodeTable[i]->data>=NodeTable[j]->data) {//cout<<"方式GW2";
		return 1;}
		else{//cout<<"方式GW3"; 
		return (NodeTable[j]->data-NodeTable[i]->data+1);}
	}
}
void InitialConnect(Vertex**NodeTable,int i,int m,int totalnum)
{
	//cout<<"数字为"<<NodeTable[i]->data<<endl;
			Edge* Temp;
			Edge** Cursor=&(NodeTable[i]->adj);//Cursor是“下个一”这个指针的指针
			if(i-m>=0)//如果上部存在元素
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
				//cout<<"下";
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
				//cout<<"前";
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
				//cout<<"后";
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
				//cout<<"前后";
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
		//	cout<<endl;

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
	}//读取的复杂度应该是o(totalnum)
	
	//这是打印输出NodeTable图表的部分
	//k=0;//用来建立地图NodeTable的辅助变量
	//for(int i=0;i<n;i++){for(int j=0;j<m;j++){//cout<<NodeTable[k]->data<<' ';
	//k++;}//cout<<endl;
	//}
	//这是打印输出NodeTable图表的部分
	for(int i=0;i<totalnum;i++)
	{
		if(NodeTable[i]->data!=-1) InitialConnect(NodeTable,i,m,totalnum);
	}//建立了初始的连通性的表，复杂度o(totalnum)
	//for(int i=0;i<totalnum;i++)
	//{	
		//cout<<"第"<<i+1<<endl;
	//	Edge*Cursor=NodeTable[i]->adj;
	//	while(Cursor!=NULL)
	///		{
	//			//cout<<"花费"<<Cursor->cost<<"移动到"<<Cursor->dest+1<<endl;
	//			Cursor=Cursor->next;
	//	}
	////	cout<<endl;
//	}

	//以下开启dj算法
	int x,y,p;//v点的初始坐标x，y,初始位置p
	cin>>x>>y;
	p=(x-1)*m+y-1;
//	cout<<"p == "<<p<<endl;
	//bool *S=new bool[totalnum];
	//for(int i=0;i<totalnum;i++) S[i]=false;
	int *dist=new int[totalnum];//dist是存储顶点v到任意j的最短路径长度的
	for(int i=0;i<totalnum;i++) dist[i]=-1;
	int *path=new int[totalnum];//path存储需要经过的倒数第一个节点，即表明最短路径
	for(int i=0;i<totalnum;i++) path[i]=-1;
	//InitialDist(NodeTable,p,dist);
	dist[p]=0;
	//int w,min;
	//S[p]=true;
	int *ven=(int*)malloc(sizeof(int)*totalnum); 
	for(int i=0;i<totalnum;i++) ven[i]=0;
	ven[p]=1;
	struct myCmp{
		bool operator ()(const Edge &p1,const Edge &p2){
			return p1.cost>p2.cost;
		}
	};
	priority_queue <Edge,vector<Edge>,myCmp> Q;
	Q.push(p);
	while(!Q.empty())
	{
		int front=Q.front();//front是队列中尚未被遍历的那个点在NodeTable的坐标
	//	cout<<"Front="<<front+1<<endl;
		Q.pop();
		ven[front]=0;
		//if(NodeTable[front]->data!=-1)//如果这个点是水域，那么不考虑其发出情况。
			for(Edge*Cursor=NodeTable[front]->adj;Cursor!=NULL;Cursor=Cursor->next)
			{
				int dest=Cursor->dest;
		//		cout<<"dest="<<dest+1<<endl;
				if(dest!=front&&(dist[dest]==-1||dist[dest]>dist[front]+Cursor->cost))
				{
			//		cout<<"DistChanged"<<endl;
					dist[dest]=dist[front]+Cursor->cost;
					if(!ven[dest])
					{
				//		cout<<"Queue pushed"<<endl;
						Q.push(dest);
						ven[dest]=1;
					}
				}
			}
	}

	/*DJ算法


	for(int i=0;i<totalnum-1;i++)
	{
		//cout<<"i第"<<i+1<<"轮"<<endl;
		min=totalnum;
		int u=p;
		for(int j=0;j<totalnum;j++)
		{
		//	cout<<"  j第"<<j+1<<"轮"<<endl;
			if(!S[j]&&dist[j]!=-1)
			{
				if(dist[j]<min)
				{
					u=j;
					min=dist[j];
				}
			}
		}
	//	cout<<"  j找到第"<<u+1<<"个元素"<<endl;
		S[u]=true;
		for(int k=0;k<totalnum;k++)
		{
			//cout<<"  k第"<<k+1<<"轮"<<endl;
			w=GetWeight(NodeTable,u,k);//找出可以和u连接的所有点
			//cout<<"    Cost with "<<k+1<<"is"<<w;
			if(!S[k]&&w!=-1)
			{//cout<<"    No"<<k+1<<"wating..";
				if(dist[u]+w<dist[k]||dist[k]==-1)
				{//cout<<"    v-u-k Find shortestway";
					dist[k]=dist[u]+w;
					//cout<<"    dist changed to"<<dist[k];
					path[k]=u;
					//cout<<"    path changed to"<<u;
				}
			}
		}
	}

	*/


	//输出结果用代码
	int sfs=0;
	for(int i=0;i<n;i++)
	{	
		for(int j=0;j<m;j++)
			printf("%d ",dist[sfs++]);
		cout<<endl;
	}
	return 0;
}
