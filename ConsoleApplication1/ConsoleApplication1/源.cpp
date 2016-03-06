#include"includes.h"
void print(int n);
void main()
{
	//creat_new("login_new","000000000");
	//while(1);
	//write_p_l_in("C:\\Users\\孟伟\\Desktop\\abc_new\\y.txt","11111");
	//while(1);
	//write_p_l("yuan.txt",1);
	//system("mkdir C;\\Users\\孟伟\\Desktop\\abc_new");
	system("cls");
	sc_out_1("x.txt");//读文件
	system("color 1f");
	delaycpp_1(1000);//延时
	cout<<"welcom to use the system; "<<endl;
	delaycpp_1(10000);
	system("cls");
	cout<<"choose  1 or 2 sys"<<endl;
	int A;
	cin>>A;
	if(A==1)
	{
	cout<<"you are the new user,chose 1,else chose 2"<<endl;
	delaycpp_1(100);
	int x;
	cin>>x;
	if(x==1)
	{
		system("cls");
		cout<<"now start ;"<<endl;
		delaycpp_1(1000);
		char login_new[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',};//login_new中是新user
		cout<<"input your name(a-z＆＆0-9&&number<=10)"<<endl;
		getchar();
		for(int i=0;i<20;i++)//处理的是0-9和a-z
		{
			login_new[i]=getchar();
			if((login_new[i]>='0'&&login_new[i]<='9')||(login_new[i]>='A'&&login_new[i]<='z'))
			{
				cout<<" ";
			}
			else
			{
				if(login_new[i]!='\n')
				cout<<"wrong input"<<endl;
			}
			if(login_new[i]=='\n')
			{
				login_new[i]='\0';
				i=20;
			}
		}
		system("cd.");
		system("chdir");
		cout<<"input your password:"<<endl;
		char password[20]={'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0',};
		for(int i = 0;i<20;i++)
		{
			
			password[i]=getchar();
			delaycpp_1(1000);
			//system("echo TIME");
			system("cls");
			//shuaping(i);
			//cout<<"\b"<<"*";
			if(password[i]=='\n')//捕捉到回车键，结束输入。并将最后一位放置\0
			{
				password[i]='\0';
				i=20;
			}
		

		}
		/*
		cout<<endl<<"input password again:"<<endl;
			for(int i = 0;i<10;i++)
		{
			
			cin>>password[1][i];
			delaycpp_1(1000);
			//system("echo TIME");
			system("cls");
			//shuaping(i);
			//cout<<"\b"<<"*";
		
		}*/
			
			//delaycpp_1(1000000);
			//if(password[0]==password[1])
		cout<<login_new<<endl;
		creat_new(login_new,password);

		delaycpp_1(100000);

	}
	if(x==2)
	{
	system("color 2f");
	cout<<"====================================================================="<<endl;
	cout<<"====================================================================="<<endl;
	cout<<"====================================================================="<<endl;
	cout<<"==========		now into the system ???		y/n==========\n"<<endl;
	cout<<"==========			    Y/N：";
	char j;
	cin>>j;
	//int k ;
	//k = rand()/10;
	//cout <<k<<endl;
	system("cls");
	if (j=='y' || j=='Y')
	{
		cout<<"====================================================================="<<endl;		
		cout<<"====================================================================="<<endl;
		cout<<"====================================================================="<<endl;
		cout<<"Login:";
		char login[20];
		char lo[20];
		for(int i = 0;i<20;i++)
		{
			lo[i]='\0';
			login[i]='\0';
		}
		getchar();
		for(int i = 0;i<20;i++)
		{
			
			lo[i]=getchar();
			if(lo[i]!='\n')
			{
				login[i]=lo[i];
			}
			else
				goto here;//goto跳转
			system("color 1f");
			shuaping_l(i);
			//cout<<"\b"<<"*";
		
		}
here:
		system("cls");
		if(panduan_l(login))
		{
			cout<<"====================================================================="<<endl;
			cout<<"==========		Please input the Password:"<<endl;
	
			string password;
			cin>>password;
			/*	char password[10];
			//password[0] = 1;
			for(int i = 0;i<10;i++)
			{
			
				cin>>password[i];
				delaycpp_1(1000);
				system("echo TIME");
				system("cls");
				//shuaping(i);
				//cout<<"\b"<<"*";
		
			}
			*/
			int ans=panduan_p_l(login,password);
			cout<<ans<<endl;
			//while(1);
			if(ans==1)
			{
				cout<<"Loading...."<<endl;
				delaycpp_1(10000);
				cout<<"contine to write:"<<endl;
				cout<<"Y\\\\N"<<endl;
				char ans;
				cin>>ans;
				char *login__=a_to_c(login);
				//cout<<login__<<endl;
				while(ans=='y')
				{
					cout<<"input you want input"<<endl;
					char pass[100]={'\0',};
					getchar();
					for(int i=0;i<100;i++)
					{
						pass[i]=getchar();
						if(pass[i]=='\n')
						{
							pass[i]='\0';
						goto it;
						}
					}
				it:
					cout<<pass<<endl;
					write_p_l_in(login__,pass);
					cout<<"contine to write:"<<endl;
					cout<<"Y  \\\\\  N"<<endl;
					cin>>ans;
				}

					while(ans=='n')
				{
					cout<<"you out now ."<<endl;
					break;
				}

				char *answer=login__;
				cout<<answer<<endl;
				//while(1);
				sc_out_2(answer);
				delaycpp_1(1000000000000000000);
		
			}
		}
	}
		if(j=='n'||j=='N')
		{
			huatu();
		//	print(6);
		}
		else
		{
			cout<<"Wrong input!!!\n"<<endl;
		}
	}
		else
		{
			cout<<"wrong input:"<<endl;
		}
	}
	else
	{
		system("color 2f");
		cout<<"====================================================================="<<endl;
		cout<<"====================================================================="<<endl;
		cout<<"====================================================================="<<endl;
		cout<<"==========		now into the system ???		y/n==========\n"<<endl;
		cout<<"==========			Y/N：";
		char j;
		cin>>j;
		if (j=='y' || j=='Y')
		{
			cout<<"====================================================================="<<endl;
			cout<<"PASS:";
		
			//string password;
			//cin>>password;
				char password[10];
			password[0] = 1;
			for(int i = 0;i<10;i++)
			{
			
				cin>>password[i];
				delaycpp_1(1000);
				system("echo TIME");
				system("cls");
				shuaping(i);
				//cout<<"\b"<<"*";
		
			}
			panduan_p(password);
	}
	else if(j=='n'||j=='N')
	{

	}
	else
	{
		cout<<"wrong input!!"<<endl;
	}

	}
}