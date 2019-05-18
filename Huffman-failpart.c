		int CurrentSizeb=Amaxlen;

	//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<' ';

		int q;
		char choice;
		int state=1;//0:上一次是最大堆；1：上一次是最小堆
		cin>>q;
		for(int round=0;round<q;round++)
		{
			cin>>choice;
			switch(choice)
			{
			case 'D'://对heapb做删除最大权重节点处理
				{
					if(state==1)//如果之前是最小堆，现在应该转换成最大堆
					{
						int CurrentPosb=(CurrentSizeb-2)/2;
						while(CurrentPosb>=0)
						{
							//siftDown(CurrentPosb as start,CurrentSizeb-1 as m)
							{
								int i=CurrentPosb,j=2*CurrentPosb+1;
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
								heapb[i]=temp;
							}
							CurrentPosb--;
						}
					}
					//现在heapb是最大堆
					state=0;

				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'A';

					heapb[0]=heapb[CurrentSizeb-1];
					CurrentSizeb--;
					//siftDown(0,currentSize-1)
					{
						int i=0,j=2*i+1;
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
						heapb[i]=temp;
					}
				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<' ';
					break;
				}
			case 'E'://对heapb做删除最小权重节点处理
				{
					if(state==0)//如果是最大堆，应该先变成最小堆
					{
						int CurrentPosb=(CurrentSizeb-2)/2;
						while(CurrentPosb>=0)
						{
							//siftDown(CurrentPos as start,CurrentSize-1 as m)
							{
								int i=CurrentPosb,j=2*CurrentPosb+1;
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
								heapb[i]=temp;
							}
							CurrentPosb--;
						}
					}
				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'A';
					state=1;

					heapb[0]=heapb[CurrentSizeb-1];
					CurrentSizeb--;
				//	cout<<CurrentSizeb<<'m';

					//siftDown(0,currentSize-1)
					{
						int i=0,j=2*i+1;
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
						heapb[i]=temp;
					}
				//	for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'B';
					break;
				}
			default://对heapb做插入节点处理
				{

					cin>>heapb[CurrentSizeb];
					if(state==1)//如果是最小堆
					{
						{
							int j=CurrentSizeb,i=(j-1)/2;
							long temp=heapb[j];
							while(j>0)
							{
								if(heapb[i]<=temp) break;
								else {heapb[j]=heapb[i];j=i;i=(i-1)/2;}
							}
							heapb[j]=temp;
						}
						CurrentSizeb++;
				//		for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'C';
					}
					else
					{
						{
							int j=CurrentSizeb,i=(j-1)/2;
							long temp=heapb[j];
							while(j>0)
							{
								if(heapb[i]>=temp) break;
								else {heapb[j]=heapb[i];j=i;i=(i-1)/2;}
							}
							heapb[j]=temp;
						}
						CurrentSizeb++;
				//		for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<'D';
					}
				}
			}
		}
		//处理完后再输出哈夫曼树的答案
		if(state=0)
		{
			int CurrentPosb=(CurrentSizeb-2)/2;
			while(CurrentPosb>=0)
			{
				//siftDown(CurrentPosb as start,CurrentSizeb-1 as m)
				{
					int i=CurrentPosb,j=2*CurrentPosb+1;
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
					heapb[i]=temp;
				}
				CurrentPosb--;
			}
		}
		//for(int i=0;i<n;i++) cout<<heapb[i];

		long totalB=0;
		int CurrentSizebb=CurrentSizeb;
		for(int k=0;k<CurrentSizebb-1;k++)
		{
			long first,second;

			first=heapb[0];
			heapb[0]=heapb[CurrentSizeb-1];
			CurrentSizeb--;

			//siftDown(0,currentSize-1)
			{
				int i=0,j=2*i+1;
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
				heapb[i]=temp;
			}

			second=heapb[0];
			heapb[0]=heapb[CurrentSizeb-1];
			CurrentSizeb--;

			{
				int i=0,j=2*i+1;
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
				heapb[i]=temp;
			}

			//cout<<first<<' '<<second<<endl;
			long x=first+second;
			totalB+=x;
			//cout<<x<<endl;
			heapb[CurrentSizeb]=x;

			//siftUp(currentSize)
			{
				int j=CurrentSizeb,i=(j-1)/2;
				long temp=heapb[j];
				while(j>0)
				{
					if(heapb[i]<=temp) break;
					else {heapb[j]=heapb[i];j=i;i=(i-1)/2;}
				}
				heapb[j]=temp;
			}

			CurrentSizeb++;
			//for(int i=0;i<CurrentSizeb;i++) cout<<heapb[i]<<' ';
			//cout<<endl;
		}
		cout<<totalA<<endl<<totalB;
