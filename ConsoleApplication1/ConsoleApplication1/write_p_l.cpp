#include "includes.h"
char *str(char *s,char *t)
{
         char *p;
         p = s;
		 int co=0;
         for(int i=0;i<100;)
		 {
			 if(p[i]!=NULL)
			 {
				 i++;
				 co++;
			 }
			 else
			 {
				 co++;
				 i=100;
			 }
		 }

		cout<<p<<endl;
		for(int i=co;i<100;){
			if(t[i]!=NULL){
			p[i]=t[i];
			i++;
			}
			else
				i=100;
		
		}
         return s;
}
char * write_p_l(char *login,int n)
{
	ifstream infile;
	char buff[10];
	char * message;
	char temp[40];
	for(int i=0;i<40;i++)
	{
		temp[i] = '\0';
		if(i<10&&login[i]!='+')
		temp[i]=login[i];
		cout<<temp[i];
	}
	infile.open(temp);
	if(infile.is_open())
	{
		cout<<"open successful;"<<endl;
		delaycpp_1(100000);
		system("cls");
		int j=0;
		while(infile.is_open())
				{
					system("color 2f");
					system("cls");
					if(infile.is_open())
					{
						while(infile.good() && !infile.eof())
						{
							memset(buff,0,10);
							infile.getline(buff,10);
							if(j==n)
							{
								message = buff;
								system("cd.  >a.txt");
								char a[100]="echo ";
								char *b=login;
								char *d=message;
								strcat(a,d);
								char *f=strcat(a,b);
								//cout<<f<<endl;
								system(f);

								//cout<<message<<endl;
								delaycpp_1(10000);
							}
								j++;
						}
					}
					infile.close();

				}
	}
	infile.close();
	return login;
}

char * write_p_l_new(char *login,int n,char *password)
{
	ifstream infile;
	char buff[10];
	char *message;
	char temp[40];
	for(int i=0;i<40;i++)
	{
		temp[i] = '\0';
		//cout<<login<<endl;
		if(i<40&&login[i]!=NULL)
		temp[i]=login[i];
		//cout<<temp[i];
	}
	infile.open(temp);
	if(infile.is_open())
	{
		cout<<"open successful;"<<endl;
		delaycpp_1(100000);
		system("cls");
		int j=0;
		while(infile.is_open())
				{
					system("color 2f");
					system("cls");
					if(infile.is_open())
					{
						cout<<j<<endl;
							if(j==n)
							{
								message = buff;
								//system("cd.  >a.txt");
								char a[100]="echo ";
								char *b=temp;
								char *c=" >";
								char *m=":password";
								char n[30]={'\0'};
								strcat(n,password);
								char *d=strcat(n,m);
								strcat(a,d);
								strcat(a,c);
								strcat(a,ROUTE);
								char *f=strcat(a,b);
								char g[100]=ROUTE;

								char *login_new=strcat(g,b);

								//cout<<f<<endl;
								
								system(f);
								cout<<"writing now(>) ..."<<endl;
								//cout<<message<<endl;
								delaycpp_1(10000);
								cout<<"contine to write:"<<endl;
								cout<<"Y\\\\N"<<endl;
								char ans;
								cin>>ans;
								
								while(ans=='y'||ans=='Y')
								{
									cout<<"input you want input"<<endl;
									char pass[100]={'\0'};
									for(int i=0;i<10;i++)
									{
										cin>>pass[i];
									}
									write_p_l_in(login_new,pass);
									cout<<"Contine to write:"<<endl;
									cout<<"Y\\\\\N"<<endl;
									cin>>ans;
								}
								if(ans=='n'||ans=='N')
								{
									cout<<"end the input"<<endl;
									goto here;
								}
							}
								j++;
						

					}
				
				}
	}
		here:
					infile.close();
	return login;
}


inline char * write_p_l_in(char *login,char *password)
{
	ifstream infile;
	char buff[10];
	char *message;
	char temp[80];
	for(int i=0;i<80;i++)
	{
		temp[i] = '\0';
	}
	for(int i=0;i<80;i++)
	{
		//cout<<login<<endl;
		if(i<40&&login[i]!=NULL)
		temp[i]=login[i];
		cout<<temp[i];
	}
	cout<<temp<<endl;

	infile.open(temp);
	if(infile.is_open())
	{
		system("cls");
		cout<<"open successful;"<<endl;
		delaycpp_1(100000000000);
		system("cls");
		int j=0;
		while(infile.is_open())
				{
					system("color 2f");
					system("cls");
					if(infile.is_open())
					{

						
/*							memset(buff,0,10);
							infile.getline(buff,10);
								char a[100]="echo ";
								char *b=temp;
								char *c=" >>";
								char *d=buff;
								strcat(a,d);
								strcat(a,c);
								char *f=strcat(a,b);
								cout<<f<<endl;
								system(f);*/
						        // 	cout<<11111111<<endl;
							
								message = buff;
								//system("cd.  >a.txt");
								char a[200]="echo ";
								char *b=temp;
								char *c=" >>";
								char *m=":other";
								char n[50]={'\0',};
								strcat(n,password);
								char *d=strcat(n,m);
								strcat(a,d);
								strcat(a,c);
								char *f=strcat(a,b);
								//cout<<f<<endl;
								
								system(f);
								cout<<"writing now(>>) ..."<<endl;
								//cout<<message<<endl;
								delaycpp_1(10000);

								goto here;
					
						

					}
				
				}
	}
		here:
					infile.close();
	return login;
}
