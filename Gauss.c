#include <iostream>
#include <math.h>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;

int main(void)
{
	int n=0;
	cin>>n;
	char choice;
	for(int round=0;round<n;round++)
	{
		cin>>choice;
		switch(choice)
		{
			case 'R':
				{
					int solveable=1;
					int deg;
					cin>>deg;
					double **y=(double**)malloc(sizeof(double*)*deg);//y是不同的行,指向一个行的首指针
					double **DATA=(double**)malloc(sizeof(double*)*deg);
					for(int i=0;i<deg;i++)
					{
						y[i]=(double*)malloc(sizeof(double)*(deg+2));//分别存储A\B\X
						DATA[i]=y[i];
						for(int j=0;j<deg;j++)
						{
							cin>>y[i][j];
						}
					}//按照i行j列录入数
					for(int i=0;i<deg;i++)
						cin>>y[i][deg];//录入右端项
					for(int i=0;i<deg;i++)//对第i列i行执行操作
					{
						int maxsite=i;
						for(int j=i;j<deg;j++)
						{
							if(fabs(y[j][i])>=fabs(y[maxsite][i]))
								maxsite=j;
						}//找出最大的所在的行数maxsite
						if(fabs(y[maxsite][i])<=10E-8) solveable=0;//这一行都是0，判定0的方法就取一个范围来判断因为会有误差
						double *temp;temp=y[i];y[i]=y[maxsite];y[maxsite]=temp;//把最大首个元素的放到第一行去
						for(int j=i+1;j<deg;j++)
						{
							double RATE=y[j][i]/y[i][i];
							for(int k=i;k<deg+1;k++)//j行，k列
								y[j][k]=y[j][k]-y[i][k]*RATE;
						}
					}
					if(solveable==0) {cout<<0<<endl;break;}//如果不可解，直接输出0
					y[deg-1][deg+1]=y[deg-1][deg]/y[deg-1][deg-1];//求出最底下的x的值，然后进入迭代求解
					for(int i=deg-2;i>=0;i--)//对于第i行
						{
							for(int j=deg-1;j>i;j--)//从deg-1个元素开始，要往前算扣除掉那些多余的b中的量
								y[i][deg]-=y[j][deg+1]*y[i][j];
							y[i][deg+1]=y[i][deg]/y[i][i];
					}
					for(int i=0;i<deg;i++)
						cout<<y[i][deg+1]<<' ';
					break;
				}
			default:
				{
					int deg,k;
					cin>>deg>>k;

					double*x=(double*)malloc(sizeof(double)*deg);//上一次迭代解
					for(int i=0;i<deg;i++) x[i]=0;//迭代初值为0
					double*xx=(double*)malloc(sizeof(double)*deg);//本次迭代解
					for(int i=0;i<deg;i++) xx[i]=1;//迭代初值为1
					double*diag=(double*)malloc(sizeof(double)*deg);//主对角的系数
					double*A=(double*)malloc(sizeof(double)*k);//date
					int *xp=(int*)malloc(sizeof(double)*k);//x
					int *yp=(int*)malloc(sizeof(double)*k);//y

					for(int i=0;i<k;i++)
					{
						cin>>xp[i]>>yp[i]>>A[i];
						if(xp[i]==yp[i])
							diag[xp[i]-1]=A[i];
					}
					double* b=(double*)malloc(sizeof(double)*deg);
					for(int i=0;i<deg;i++)
						cin>>b[i];//录入右端项

					int OUT=0;
					while(OUT==0)//这是一次迭代循环，如果差值过大就继续迭代
					{
						for(int i=0;i<deg;i++)//这个矩阵的特性决定了必然会是一行求一行所对应的,求xi
						{
							double temp=0;
							for(int j=0;j<k;j++)
							{
								if(xp[j]==i+1)//表示第j个元素这个元素在i行，那么这个元素要参与xi的迭代运算
									if(yp[j]>i+1)//如果列数比行数大，则选取k次迭代结果
										temp-=x[yp[j]-1]/*第j个元素对应的初次迭代值*/*A[j]/diag[i];
									else if(yp[j]<i+1)
										temp-=xx[yp[j]-1]*A[j]/diag[i];
							}
							xx[i]=temp+b[i]/diag[i];
						}
						for(int i=0;i<deg;i++)
						{
							double temp=0;
							for(int j=0;j<k;j++)
							{
								if(xp[j]==i+1)//表示第j个元素这个元素在i行，那么这个元素要参与xi的迭代运算
									if(yp[j]>i+1)//如果列数比行数大，则选取k次迭代结果
										temp-=xx[yp[j]-1]/*第j个元素对应的初次迭代值*/*A[j]/diag[i];
									else if(yp[j]<i+1)
										temp-=x[yp[j]-1]*A[j]/diag[i];
							}
							x[i]=temp+b[i]/diag[i];
						}
						/*double*swaptemp=xx;
						xx=x;
						x=swaptemp;
						OUT=1;
						for(int i=0;i<deg;i++)
							cout<<x[i]<<' ';

						cout<<endl;
						for(int i=0;i<deg;i++)
							cout<<xx[i]<<' ';

						cout<<endl;*/
						OUT=1;
						for(int i=0;i<deg;i++)
							if(fabs(x[i]-xx[i])>=1e-4)
							{OUT=0;break;}
					}
					for(int i=0;i<deg;i++)
						cout<<x[i]<<' ';
					break;
				}
		}
	}
return 0;
}
