【作业编号】
上机作业7：二叉搜索树、平衡树
【问题描述】
公司的人口总是不断在流动的，有人今天入职了，有人明天离职了。
作为公司的人力资源，有可能需要询问当前公司员工中的编号情况。
【输入格式】
第一行一个数字N，表示有N个事件依次发生。接下来N行，每行有可能是：
1.一个字符'I'和一个整数X，表示一个编号为A的员工入职了；
2.一个字符'D'和一个整数X，表示一个编号为A的员工离职了；
3.一个字符'Q'和一个整数K，表示人力资源询问目前公司里编号第K小的员工的编号。
4.一个字符'S'和一个整数X，表示人力资源询问目前公司里编号为X的员工的编号是第几小。
保证所有出现过的员工编号两两不同，且保证所有数据的合法性。
【输出格式】
对于每个询问，输出一行一个整数，表示对应询问的答案。
【样例输入】
10
I 3
I 7
I 1
I 9
I 8
Q 2
S 8
D 3
Q 2
S 8
【样例输出】
3
4
7
3
【数据规模和约定】
20%的数据，只含I、D、Q事件。
20%的数据，只含I、D、S事件。
20%的数据，只含I、Q、S事件。
80%的数据，N≤200000，数据没有经过特殊构造。
100%的数据，N≤200000。
【相关资料】
https://en.wikipedia.org/wiki/AVL_tree
https://en.wikipedia.org/wiki/Splay
https://en.wikipedia.org/wiki/Red%E2%80%93black_tree
https://en.wikipedia.org/wiki/Treap
https://en.wikipedia.org/wiki/Weight-balanced_tree
如果遇到特殊构造的数据，二叉查找树会退化成一条链，导致效率低下。因此保证二叉查找树良好性能需要对其进行平衡化。二叉查找树的平衡化有很多种，课上的AVL是其中的一种实现。
AVL是左右子树的高度差超过阈值就进行一系列复杂的旋转。借鉴Weight-balanced-tree，一个简单的平衡化思想是：如果对于一个节点，左（右）子树的大小减右（左）子树的大小超过一定阈值，则将这个节点为根的子树进行右（左）旋操作，使得旋转后新的子树，其左右子树的大小比旋转前更平衡。

#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;
using std::string;
typedef struct AvlNode{int data;AvlNode* m_pLeft;AvlNode* m_pRight;int height;int weight;}*AvlTree,*Position,AvlNode;
int Max(int a,int b)
{return a>b?a:b;}
int Height( AvlTree T)
{
	if(NULL == T)return -1;
	else return T->height;
}
int Weight(AvlTree T)
{
	if(T==NULL) return 0;
	else return T->weight;
}
AvlNode* avltree_maximum(AvlTree tree)
{
	if (tree == NULL) return NULL;
	while(tree->m_pRight!= NULL)
		tree = tree->m_pRight;
	return tree;
}
AvlNode* avltree_minimum(AvlTree tree)
{
	if (tree == NULL)	return NULL;
	while(tree->m_pLeft!= NULL)
		tree = tree->m_pLeft;
	return tree;
}
AvlTree singleRotateWithRight(AvlTree T)
{
	AvlTree L=T->m_pLeft;
	L->weight=Weight(T);
	T->weight=Weight(L)-Weight(L->m_pLeft)-1;
	T->m_pLeft=L->m_pRight;
	L->m_pRight=T;
	T->height=Max( Height(T->m_pLeft),Height(T->m_pRight) ) + 1;
	L->height=Max( Height(L->m_pLeft),Height(L->m_pRight) ) + 1;
	return L;
}
AvlTree singleRotateWithLeft(AvlTree T)
{
	AvlTree R=T->m_pRight;
	R->weight=Weight(T);
	T->weight=Weight(R)-Weight(R->m_pRight)-1;
	T->m_pRight=R->m_pLeft;
	R->m_pLeft=T;
	T->height=Max( Height(T->m_pLeft),Height(T->m_pRight) ) + 1;
	R->height=Max( Height(R->m_pLeft),Height(R->m_pRight) ) + 1;
	return R;
}
AvlTree doubleRotateWithLeft(AvlTree T)
{
	T->m_pLeft=singleRotateWithLeft(T->m_pLeft);
	return singleRotateWithRight(T);
}
AvlTree doubleRotateWithRight(AvlTree T)
{
	T->m_pRight=singleRotateWithRight(T->m_pRight);
	return singleRotateWithLeft(T);
}
AvlTree AvlTreeInsert(AvlTree T, int x)
{
	if(T == NULL)
	{
		AvlNode *NT=(AvlNode*)malloc(sizeof(AvlNode));
		NT->weight=1;NT->data=x;NT->m_pLeft=NULL;NT->m_pRight=NULL;NT->height=0;
		return NT;
	}
	else if(x<T->data)        //如果插入到T结点的左子树上//左边永远更小
	{
		T->weight++;//在知道这个节点要连在这个根之后，这个根所附带的重量就要增加；
		T->m_pLeft=AvlTreeInsert(T->m_pLeft,x);//递归插入左节点中	//先插入，后旋转
		if(Height(T->m_pLeft)-Height(T->m_pRight)==2) //只有可能是这个
		{
			if(x<T->m_pLeft->data) T=singleRotateWithRight(T);//左左情况，只需要右旋转
			else T=doubleRotateWithLeft(T);//左右情况，双旋转,先左
		}
	}
	else if(x>T->data)
	{
		T->weight++;
		T->m_pRight=AvlTreeInsert(T->m_pRight,x);
		if(Height(T->m_pRight)-Height(T->m_pLeft)==2)
		{
			if(x > T->m_pRight->data) T=singleRotateWithLeft( T );//右右情况，进行左旋
			else T=doubleRotateWithRight( T );//左右情况，双旋转,先右
		}
	}
	T->height=Max(Height(T->m_pLeft),Height(T->m_pRight))+1;
	return T;
}
AvlTree AvlTreeDelete(AvlTree T, int x)
{
	if (T==NULL)return NULL;
	if (x<T->data)
	{
		T->weight--;
		T->m_pLeft=AvlTreeDelete(T->m_pLeft,x);
		if(T->m_pLeft==NULL&&T->m_pRight==NULL) T->height--;
		if (Height(T->m_pRight)-Height(T->m_pLeft)==2)
		{
			AvlTree r=T->m_pRight;
			if (Height(r->m_pLeft)>Height(r->m_pRight))
				T=doubleRotateWithRight(T);
			else
				T=singleRotateWithLeft(T);
		}
	}
	else if (x>T->data)// 待删除的节点在"tree的右子树"中
	{
		T->weight--;
		T->m_pRight=AvlTreeDelete(T->m_pRight,x);
		if(T->m_pLeft==NULL&&T->m_pRight==NULL) T->height--;
		if (Height(T->m_pLeft)-Height(T->m_pRight)==2)
		{
			AvlTree l=T->m_pLeft;
			if (Height(l->m_pRight)>Height(l->m_pLeft))
				T=doubleRotateWithLeft(T);
			else
				T=singleRotateWithRight(T);
		}
	}
	else    // tree是对应要删除的节点。
	{
		if ((T->m_pLeft)&&(T->m_pRight))
		{
			if (Height(T->m_pLeft)>Height(T->m_pRight))
			{
				AvlNode* max=avltree_maximum(T->m_pLeft);
				T->data=max->data;
				T->weight--;
				T->m_pLeft=AvlTreeDelete(T->m_pLeft,max->data);
			}
			else
			{
				AvlNode* min = avltree_minimum(T->m_pRight);
				T->data=min->data;
				T->weight--;
				T->m_pRight=AvlTreeDelete(T->m_pRight,min->data);
			}
		}
		else
		{
			AvlNode *tmp = T;
			T = (T->m_pLeft)? T->m_pLeft:T->m_pRight;
		}
	}
	return T;
}
void inOrderVisitUseRecur(const AvlTree pCurrent)
{
	if(pCurrent)
	{
		inOrderVisitUseRecur(pCurrent->m_pLeft);
		cout << pCurrent->data << " ";
		if(pCurrent->m_pLeft)
			cout << " leftChild: "<<pCurrent->m_pLeft->data;
		else
			cout << " leftChild: "<<"NULL" ;
		if(pCurrent->m_pRight)
			cout << " rightChild: "<<pCurrent->m_pRight->data;
		else
			cout << " rightChild: "<< "NULL";
		cout<<' '<<pCurrent->weight<<' '<<pCurrent->height;
		cout << endl;
		inOrderVisitUseRecur(pCurrent->m_pRight);
	}
}
int main()
{
	AvlTree root=NULL;
	int n=0;
	cin>>n;
	char choice;
	for(int i=0;i<n;i++)
	{
		int x;
		cin>>choice>>x;
		switch(choice)
		{
		case 'I'://x员工入职
			{
				root=AvlTreeInsert(root,x);
				//inOrderVisitUseRecur(root);
				break;
			}
		case 'D'://x员工离职
			{
				root=AvlTreeDelete(root,x);
			//	inOrderVisitUseRecur(root);
				break;	
			}
		case 'Q'://编号第x小的员工的编号
			{
				AvlTree cursor=root;
				int state=0;
				while(Weight(cursor)>x)
				{
					if(x==Weight(cursor->m_pLeft)+1) {cout<<cursor->data<<endl;state=1;break;}
					else if(Weight(cursor->m_pLeft)>x) cursor=cursor->m_pLeft;
					else 
					{
						x-=Weight(cursor->m_pLeft)+1;
						cursor=cursor->m_pRight;
					};
				}
				cursor=avltree_maximum(cursor);
				if(state==0) cout<<cursor->data<<endl;
				break;	
			}
		default://编号第x的员工是第几小
			{
				int number=1;
				AvlTree cursor=root;
				while(cursor->data!=x)
				{
					if(cursor->data>x) {cursor=cursor->m_pLeft;}
					else{number+=cursor->m_pLeft->weight+1;cursor=cursor->m_pRight;}
				}
				number+=Weight(cursor->m_pLeft);
				cout<<number<<endl;
				break;
			}
		}
	}
	return 0;
}
