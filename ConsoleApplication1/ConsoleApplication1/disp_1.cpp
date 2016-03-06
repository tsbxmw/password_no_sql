#include<iostream>
#include"includes.h"
using namespace std;
void pc_out(int n)
{
int j = 0;
	for(int i = 1 ; i<10000000000000000; i++)   
	{
		delaycpp(100);
		j = rand()%10;
		if(i%100 == 99)
		{
					for(int i = 0;i<81;i++)
					{
						delaycpp(200);
						cout<<char(j);
						if(i==80)
							cout<<endl;
					}
					display(n);
			
		}
		cout<<(char)(j+i);
		while(j>=0){
			int x=rand()%100;
		cout<<char(x);
		j--;
		}
	}
}