#include<iostream>
#include"includes.h"
using namespace std;
char f_new[100]={'\0'};
void print(int n)
{
	if(n == 1)
	{
		cout<<""<<endl;
	}
	delaycpp(10);
	pc_out(n);
}

char *a_to_c(char *login)//登录名-变成文件名
{
	char a[100]=ROUTE;
	char *c=login;
	//cout<<login<<endl;
	char *d=HOUZHUI;
	strcat(a,c);
	strcat(a,d);
	for(int i=0;i<100;i++)
	{
		f_new[i]=a[i];
	}
	return f_new;
}
char * ab_to_c(char *login)
{
	char a[100]="cd ";
	
	//char e[60]="cd. ";
	char *b=" > ";
	char *c=login;
	char *d=HOUZHUI; 
	strcat(a,ROUTE);
	strcat(a,b);
	strcat(a,c);
	strcat(a,d);
	for(int i=0;i<100;i++)
	{
		f_new[i]=a[i];
	}
	return f_new;
}
void creat_new(char *login_new,char *password)
{

	char *c=login_new;
	char *d=HOUZHUI;	
	char *f=ab_to_c(login_new);
	//char *f=ab_to_c(login_new);
	//cout<<f<<endl;	
	//while(1);
	system(f_new);
	//while(1);
	char g[30]={'\0'};
	strcat(g,c);
	char *h=strcat(g,d);
	//cout<<h<<endl;
	//while(1);
	string x=write_p_l_new(h,1,password);
	//delaycpp_1(100000);
	if(x==login_new)
		cout<<"write successful!"<<endl;

}
