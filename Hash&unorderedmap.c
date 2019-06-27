【作业编号】
上机作业8：Hash
【问题描述】
一些家史复杂的家族会记录家谱。家谱是同一个姓的族人的一个集合，从最原始的祖先开始记录，之后每次新诞生的、与祖先有血缘关系的同姓族人都会被记录在案。
一个家庭，我们定义为一个族人和其直属同姓子女这两代人的集合。比如男性族人A，生了一个女儿B，接着生了一个儿子C，然后生了一个女儿D。那么A-BCD可以被称为一个以A为祖先的家庭。两个家庭称为相似，当且仅当两个家庭有相同的结构。比如男性族人E，生了一个女儿F，接着生了一个儿子G，然后生了一个女儿H，那么家庭E-FGH可以和家庭A-BCD称为相似。但比如男性族人I，生了两个女儿J、K，再生了一个儿子L，那么家庭I-JKL和家庭A-BCD就不能称为相似。或一个男性族人M，生了一个女儿N，接着生了一个儿子O，那家庭M-NO也不能和家庭A-BCD称为相似。或一个女性族人P，生了一个女儿Q，接着生了一个儿子R，然后生了一个女儿S，那家庭P-QRS也不能和家庭A-BCD称为相似。如果一个族人没有后代，那么他/她自己一个人也形成一个家庭。
一个子族，我们定义为一个族人和其所有直属同姓后代的集合。比如B生了一个儿子T，C生了两个女儿U、V，T生了一个女儿W，那么A-B=T~W-C=UV-D就可以称为以A为祖先的子族。同样子族判断相似的标准和家庭相同，当且仅当两个子族拥有相同的结构才能被认为相似。
现在告知一个家族的家谱，请你回答一些关于相似性的问题。
【输入格式】
第一行两个正整数N、Q，表示家谱的长度和询问的个数。
接下来N行描述家谱，每行的格式为两个只包含小写字母的字符串parent、child和一个字符'M'或'F'，表示名为parent的族人生了一个孩子叫做child，child的性别为'M'（代表男）或'F'（代表女）。家谱的描述以日期顺序，即同一家庭中，先描述的是哥哥/姐姐，后描述的是弟弟/妹妹。
接下来是Q行询问，每行有可能是：
1.一个字符'F'和一个字符串parent，表示询问有多少家庭和以parent为祖先的家庭相似（不包括parent自身）。
2.一个字符'S'和一个字符串parent，表示询问有多少子族和以parent为祖先的子族相似（不包含parent自身）。
最原始的祖先名字为字符串'root'，性别为男性。
族人的名字两两不同。
数据保证合法性，且数据默认没有族人之间结婚的情况。
【输出格式】
对于每个询问输出一行一个整数表示答案。
【样例输入】
14 6
root alice F
root bob M
alice cindy F
alice daniel M
bob ellis M
alice frank M
ellis george M
daniel helen F
daniel isaia M
isaia john M
john kevin M
isaia lisa F 
george micheal M
kevin nick M
F root
F cindy
F alice
S alice
S ellis
S nick
【样例输出】
1
2
0
0
1
2
【样例解释】
和root相同的家庭有：daniel（结构都为：M-FM）。
和cindy相同的家庭有：helen、lisa（结构都为：F）。
没有和alice相同结构的家庭（结构为：F-FM）
没有和alice相同结构的子族（结构为：F-FM=FM~M_M^M~F）
和ellis相同的子族有：john（结构都为：M-M=M）
和nick相同的子族有：frank、micheal（结构都为：M）
【数据规模和约定】
80%的数据，只含家庭询问。
100%的数据，N,Q≤50000。

#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::vector;
const int q2=388211;
int a = 2, b = 3;
struct Node{int hash;vector<string> children;};
void Generate(unordered_map<string,Node>&tree, string parent, string child,char gend) 
{
	int gender;
	if (gend=='F')gender=2;
	else gender=1;
	tree[child].hash=gender;
	tree[parent].hash= (a*tree[parent].hash+b*gender)%q2;
	tree[parent].children.push_back(child);
}
int Kazoku(unordered_map<string,Node>&t,int*r,int*p,string s) //迭代构建出家族的hash表
{ 
	int hash=t[s].hash;
	r[hash]++;
	int size=t[s].children.size();
	for(int i=0;i<size;i++)
	{
		t[s].hash+=(a*Kazoku(t,r,p,t[s].children[i])+b*hash)%q2;
	}
	t[s].hash=t[s].hash%q2;
	p[t[s].hash]++;
	return t[s].hash;
}
int main() 
{
	int N, Q;
	string parent,child,order,name;
	char gender;
	unordered_map<string,Node> tree;
	int *result =(int *)malloc(sizeof(int)*500000);
	memset(result,0,sizeof(int)*500000);
	int *resultP=(int *)malloc(sizeof(int)*500000);
	memset(resultP,0,sizeof(int)*500000);
	cin>>N>>Q;
	tree["root"].hash = 1;
	for (int i=0;i<N;i++) 
	{
		cin>>parent>>child>>gender;
		Generate(tree,parent,child,gender);
	}
	unordered_map<string,Node> treee=tree;
	Kazoku(tree,result,resultP,"root");
	for (int i=0;i<Q;i++) 
	{
		cin>>order>>name;
		if (order == "F") {
			cout << result[treee[name].hash]-1<< endl;
		}
		else{
			cout<<resultP[tree[name].hash]-1<< endl;
		}
	}
}
