【作业编号】

上机作业3：栈、队列、双端队列

【问题描述】

小M想制作一个IDE插件来帮助他检查自己代码中的括号是否都已配对。为了简化问题，小M把所有不是括号的字符都忽略掉了，现在需要检查一个字符串是否为括号序列。

一个括号序列可以用以下方式进行定义：

1、空的字符串是配对的括号序列；

2、若字符串A是括号序列，那么字符串(A)、[A]、{A}、<A>都是括号序列；

3、若字符串A和B是括号序列，那么AB也是括号序列；

4、只有上述方式产生的字符串是括号序列。

例如(){<[]>}、((()))、空串等都是括号序列，而>)(<、(()))、<(>)等就不是括号序列。

为了降低编程难度，小M对自己的IDE做了进一步的简化：只允许在文件开头和结尾增删代码。具体地讲，最开始小M的IDE中只有一个空的字符串，每次会进行如下四个操作中的一个：

1、在字符串末尾添加一个括号；

2、在字符串开头添加一个括号；

3、删除字符串末尾的一个括号；

4、删除字符串开头的一个括号。

每进行一个操作，都要判断当前的字符串是否为括号序列。

【输入描述】

第一行包含1个正整数n，表示操作的数量。

接下来n行，每行描述一个操作。其中每行首先包含一个1到4正整数，表示操作类型。

若操作为1或2，则该行接下来会有一个空格和一个字符，表示在末尾或开头增加了相应的括号。其中出现的字符只可能是8种括号“()[]{}<>”中的一种。

若操作为3或4，则该行接下来什么都没有，表示在删除末尾或开头的一个括号。当字符串为空的时候不会出现删除操作。

【输出描述】

输出n行，每行一个整数0或1，表示每个操作后形成的字符串是否为括号序列。

【子任务】

1、有10%的数据，n=300，只有操作1。

2、另外10%的数据，n=2000，只有操作1。

3、另外20%的数据，n=100000，只有操作1。

4、另外10%的数据，n=300，只有操作1和2。

5、另外10%的数据，n=2000，只有操作1和2。

6、另外20%的数据，n=100000，只有操作1和2。

7、另外10%的数据，n=2000。

8、另外10%的数据，n=100000。

【提示】

可能需要使用栈、队列或双端队列来维护还没有配对的括号。

如果每个操作难以用O(1)的时间复杂度完成，每次对整个字符串重新计算配对情况也可以得到大量分数。

当包含删除操作时，我们可能会需要使用两个双端队列。


【样例输入1】

12

1 [

1 (

1 )

1 {

1 {

1 }

1 }

1 ]

1 {

1 }

1 )

1 <

【样例输出1】

0

0

0

0

0

0

0

1

0

1

0

0

【样例输入2】

12

2 }

1 {

1 }

1 {

1 {

1 <

1 >

1 }

2 {

1 }

1 >

1 <

【样例输出2】

0

0

0

0

0

0

0

0

0

1

0

0

【样例输入3】

12

1 )

1 <

3

1 {

2 >

3

3

1 <

4

1 >

1 [

1 >

【样例输出3】

0

0

0

0

0

0

0

0

0

1

0

0

 【样例输入4】

4

1 (

1 )

1 (

4

【样例输出4】

 0

1

0

0

#include <iostream>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;
struct NODE {NODE *PARTNER/*配合元素*/;NODE *lp;char date;NODE *rp;};//用链式存储

bool judge(int front,int last){if(last-front==1||last-front==2)return 1;else return 0;}
bool judgeleft(int front){if(front=='('||front=='['||front=='{'||front=='<') return 1;else return 0;}
NODE *createnode(NODE* connect,char way,int data)//way=r\l
{
	NODE *TEMP=(NODE*)malloc(sizeof(NODE));
	TEMP->date=data;
	if(way=='r')
		connect->rp=TEMP,TEMP->lp=connect,TEMP->rp=NULL,TEMP->PARTNER=NULL;
	else 
		connect->lp=TEMP,TEMP->rp=connect,TEMP->lp=NULL,TEMP->PARTNER=NULL;
	return TEMP;
}
int main(void)
{

	NODE *TEMP;
	TEMP=(NODE*)malloc(sizeof(NODE));
	TEMP->lp=NULL,TEMP->date=0,TEMP->PARTNER=NULL,TEMP->rp=NULL;
	NODE *StoreR,*StoreL;
	StoreL=TEMP,StoreR=TEMP;//以上都是初始化存储用的双向链表的
	int n=0,ifinitial=0;
	char date;
	cin>>n;
	int choice;
	NODE *Right[100000],*Left[100000];//两个操作栈
	int Rtop=0,Rflag=-1,Ltop=0,Lflag=-1;
	for(int i=0;i<n;i++)
	{
		cin>>choice;
		switch(choice)
		{
			case 1:
				{
					if(ifinitial==0)
					{
						ifinitial=1;
						cin>>StoreR->date;
					}
					else {cin>>date;StoreR=createnode(StoreR,'r',date);}

					Right[++Rflag]=StoreR;
					if(Rflag==Rtop) //如果是栈底元素怎么办？
					{
						if(Lflag!=Ltop-1/*L栈非空*/&&judge(Left[Ltop]->date,Right[Rtop]->date))//且对应上了
						{Right[Rtop]->PARTNER=Left[Ltop],Left[Ltop]->PARTNER=Right[Rtop];Rtop++,Ltop++;}//栈收缩底部
						if(Rflag==Rtop-1&&Lflag==Ltop-1) cout<<1<<endl;
						else cout<<0<<endl;
					}
					else
					{ 
						if(judge(Right[Rflag-1]->date,Right[Rflag]->date))
						{
							Right[Rflag-1]->PARTNER=Right[Rflag],Right[Rflag]->PARTNER=Right[Rflag-1];
							Rflag=Rflag-2;
						}
						if(Rflag==Rtop-1&&Lflag==Ltop-1) cout<<1<<endl;
						else cout<<0<<endl;
					}
					break;
				}
			case 2:
				{
					if(ifinitial==0)
					{
						ifinitial=1;
						cin>>StoreL->date;
					}
					else {cin>>date;StoreL=createnode(StoreL,'l',date);}

					Left[++Lflag]=StoreL;
					if(Lflag==Ltop) //如果是栈底元素怎么办？
					{
						if(Rflag!=Rtop-1/*L栈非空*/&&judge(Left[Ltop]->date,Right[Rtop]->date))//且对应上了
						{Right[Rtop]->PARTNER=Left[Ltop],Left[Ltop]->PARTNER=Right[Rtop];Rtop++,Ltop++;}//栈收缩底部
						if(Rflag==Rtop-1&&Lflag==Ltop-1) cout<<1<<endl;
						else cout<<0<<endl;
					}
					else
					{ 
						if(judge(Left[Lflag]->date,Left[Lflag-1]->date))
						{
							Left[Lflag-1]->PARTNER=Left[Lflag],Left[Lflag]->PARTNER=Left[Lflag-1];
							Lflag=Lflag-2;
						}
						if(Rflag==Rtop-1&&Lflag==Ltop-1) cout<<1<<endl;
						else cout<<0<<endl;
					}
					break;
				}
			case 3://删除右边的节点
				{
					if(Rflag==Rtop-1&&Lflag==Ltop-1)//如果左右栈为空，，表明都是配好对的，则直接把友节点加入右栈
					{
						Right[++Rflag]=StoreR->PARTNER;
						StoreR->PARTNER->PARTNER=NULL;
						StoreR=StoreR->lp;
						cout<<0<<endl;
					}
					else//如果左右栈非全空，优先判断左栈是否为空
					{
						if(Lflag==Ltop-1)//左栈是空栈而右栈非空
						{
							if(StoreR==Right[Rflag])//若右栈元素不是被挑起来的隐藏括号
							{
								Rflag--;
								if(StoreR==StoreL) ifinitial=0;else	StoreR=StoreR->lp;
								StoreR->rp=NULL;
								Rflag==Rtop-1? cout<<1<<endl:cout<<0<<endl;
								
							}
							else
							{
								Rflag++;
								Right[Rflag]=StoreR->PARTNER;
								StoreR=StoreR->lp;
								StoreR->rp=NULL;
								cout<<0<<endl;
							}
						}
						else if(Rflag==Rtop-1)//左栈非空，右栈空，此时要看右边是否是已经配好对的，如果配好了，则考虑插入，否则考虑从左栈直接删除
						{
							if(Left[Ltop]!=StoreR)//左栈最左不是存储序列最左，表面存储序列最左有隐藏序列，所以对存储序列做操作，入栈
							{
								if(Ltop==0)//左栈左侧满了，入右栈
								{
									Right[++Rflag]=StoreR->PARTNER;
									Right[Rflag]->PARTNER=NULL;
									StoreR=StoreR->lp;
									StoreR->rp=NULL;
									cout<<0<<endl;
								}
								else
								{
									Left[--Ltop]=StoreR->PARTNER;
									Left[Ltop]->PARTNER=NULL;
									StoreR=StoreR->lp;
									StoreR->rp=NULL;
									cout<<0<<endl;
								}
							}
							else//左栈存储的是零碎元素
							{
								Ltop++;
								if(StoreR==StoreL) ifinitial=0;else	StoreR=StoreR->lp;
								StoreR->rp=NULL;
								Lflag==Ltop-1? cout<<1<<endl:cout<<0<<endl;
							}
						}
						else//左右都不是空栈
						{
							if(StoreR==Right[Rflag])//若右栈元素不是被挑起来的隐藏括号
							{
								Rflag--;
								StoreR=StoreR->lp;
								StoreR->PARTNER;
								Rflag==Rtop-1&&Lflag==Ltop-1? cout<<1<<endl:cout<<0<<endl;
							}
							else
							{
								Right[++Rflag]=StoreR->PARTNER;
								Right[Rflag]->PARTNER=NULL;
								StoreR=StoreR->lp;
								StoreR->rp=NULL;
								cout<<0<<endl;
							}
						}
					}
					break;
				}

			default:
				{
					if(Rflag==Rtop-1&&Lflag==Ltop-1)//如果左右栈为空，，表明都是配好对的，则直接把友节点加入右栈
					{
						Left[++Lflag]=StoreL->PARTNER;
						StoreL=StoreL->rp;
						cout<<0<<endl;
					}
					else//如果左右栈非全空，优先判断右栈是否为空
					{
						if(Rflag==Rtop-1)//右栈是空栈而左栈非空
						{
							if(StoreL==Left[Lflag])//若右栈元素不是被挑起来的隐藏括号
							{
								Lflag--;
								if(StoreR==StoreL) ifinitial=0;else StoreL=StoreL->rp;
								Lflag==Ltop-1? cout<<1<<endl:cout<<0<<endl;
							}
							else
							{
								Lflag++;
								Left[Lflag]=StoreL->PARTNER;
								StoreL=StoreL->rp;
								cout<<0<<endl;
							}
						}
						else if(Lflag==Ltop-1)//右栈非空，左栈空，此时要看左边是否是已经配好对的，如果配好了，则考虑插入，否则考虑从右栈直接删除
						{
							if(Right[Rtop]!=StoreL)//右栈最左元素不是存储序列最左，表面存储序列最左有隐藏序列，所以对存储序列做操作，入栈
							{
								if(Rtop==0)//右栈左侧满了满了，入左栈
								{
									Left[++Lflag]=StoreL->PARTNER;
									Left[Lflag]->PARTNER=NULL;
									StoreL=StoreL->rp;
									StoreL->lp=NULL;
									cout<<0<<endl;
								}
								else
								{
									Right[--Rtop]=StoreL->PARTNER;
									Right[Rtop]->PARTNER=NULL;
									StoreL=StoreL->rp;
									StoreL->lp=NULL;
									cout<<0<<endl;
								}
							}
							else//右栈存储的是零碎元素
							{
								Rtop++;
								if(StoreR==StoreL) ifinitial=0;else	StoreL=StoreL->rp;
								StoreL->lp=NULL;
								Rflag==Rtop-1? cout<<1<<endl:cout<<0<<endl;
							}
						}
						else//左右都不是空栈
						{
							if(StoreL==Left[Lflag])//若左栈元素不是被挑起来的隐藏括号
							{
								Lflag--;
								StoreL=StoreL->rp;
								StoreL->PARTNER;
								Lflag==Ltop-1&&Rflag==Rtop-1? cout<<1<<endl:cout<<0<<endl;
							}
							else
							{
								Left[++Lflag]=StoreL->PARTNER;
								Left[Lflag]->PARTNER=NULL;
								StoreL=StoreL->rp;
								StoreL->lp=NULL;
								cout<<0<<endl;
							}
						}
					}
					break;
				}
		}
	}
return 0;
}
