#include <iostream>
#include "includes.h"
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;
void sc_out(string name)//读文件函数
{
char buff[1024];
			string message;
			
			ifstream infile;
			infile.open(name);
			int counter = 0;
			while(infile.is_open())
				{
					system("color 8f");
					for(int i = 0;i<20;i++)
					{
						system("color 3f");
						delaycpp(100);
						cout<<"-";

					}
					system("cls");
					cout<<"reading now(1)..."<<endl;
					delaycpp_1(10000);
					if(infile.is_open())//读文件，每次1024
					{
						while(infile.good() && !infile.eof())
						{
							memset(buff,0,1024);//设置缓冲文件buff大小为1024
							infile.getline(buff,1024);//读行
							message = buff;
							delaycpp_1(100000000000);
							cout<<message<<endl;
						}
					}
					infile.close();

				}
}


int sc_out_l(char *login)//
{
	ifstream infile;
	char temp[40];
	
	for(int i=0;i<20;i++)
	{
		temp[i] = '\0';
		if(i<20&&login[i]!='+')
		temp[i]=login[i];
	//	cout<<temp[i];
	}
	char * a=HOUZHUI;
	char c[60]=ROUTE;
	strcat(temp,a);
	char *b=strcat(c,temp);

	//string t =temp;
	//cout<<temp<<endl;
	
	infile.open(b);
	//printf("%s",temp);
	if(!infile.is_open())
	{
		cout<<"login dosen't exeit"<<endl;
		return 0;
	}
	
	else{
		system("cls");
		cout<<"fine"<<endl;
		return 1;
	}

}


void sc_out_1(string name)
{
			char buff[1024];
			string message;
			ifstream infile;
			infile.open(name);
			int counter = 0;
			if(infile.is_open()!=1)
				cout<<"open false\\\\\\\\"<<endl;
			while(infile.is_open())
				{
					system("color 2f");
					for(int i = 0;i<20;i++)
					{
						system("color 3f");
						delaycpp(100);
						cout<<".";

					}
					system("cls");
					system("color 3f");
					if(infile.is_open())
					{
						while(infile.good() && !infile.eof())
						{
							memset(buff,0,1024);
							infile.getline(buff,1024);
							message = buff;
							delaycpp_1(1000000000);
							cout<<message<<endl;
						}
					}
					infile.close();

				}

}
void sc_out_2 (string name)
{

			char buff[1024];
			string message;
			ifstream infile;
			infile.open(name);
			int counter = 0;
			if(infile.is_open()!=1)
				cout<<"open false\\\\\\\\"<<endl;
			while(infile.is_open())
				{
					system("color 2f");
					for(int i = 0;i<20;i++)
					{
						system("color 3f");
						delaycpp(100);
						cout<<".";

					}
					system("cls");
					system("color 3f");
					if(infile.is_open())
					{
						while(infile.good() && !infile.eof())
						{
							memset(buff,0,1024);
							infile.getline(buff,1024);
							message = buff;
							delaycpp_1(1000000000);
							cout<<message<<endl;
						}
					}
					infile.close();

				}

}


string sc_out_p_l(char *login,int n)
{
	
	char buff[50];
	//for(int i=0;i<n;i++)
		//buff[i]='\0';
			
	char temp[40];
	//cout<<"3333333333333333333"<<endl;
	for(int i=0;i<40;i++)
	{
		temp[i] = '\0';
		if(i<10&&login[i]!='+')
		temp[i]=login[i];
		//cout<<temp[i];
	}
	char *a=HOUZHUI;
	char c[60]=ROUTE;
	strcat(temp,a);
	char *b=strcat(c,temp);
			string message_p_l;
			ifstream infile;
			infile.open(b);
			int counter = 0;
			while(infile.is_open())
				{
					system("color 2f");
					system("cls");
					//cout<<"11111111111111111111111"<<endl;
					if(infile.is_open())
					{
						//cout<<"22222222222222222222222222"<<endl;
						while(infile.good() && !infile.eof()&&counter==0)
						{
							memset(buff,0,n+1);
							infile.getline(buff,n+1);
							char buff_new[50]={'\0'};
							//cout<<buff<<endl;
							
							for(int i=0;i<n+1;i++)
							{
								char s[50];
								for(int j=i;j<n+1;j++)
									s[j]=buff[j];
								if(s!=":password")
									buff_new[i]=buff[i];
							}
							//cout<<buff_new<<endl;
							message_p_l=buff_new;
							delaycpp_1(10000000000);
							//cout<<message_p_l<<endl;
							
							counter++;
						}
					}
					infile.close();

				}
			infile.close();
			return message_p_l;
}
