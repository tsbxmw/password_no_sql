#include "includes.h"
void panduan_p(char *password)
{
	system("cls");
	if(password[0] == '1' &&password[1] == '2' &&password[2] == '3' &&password[3] == '4' &&password[4] == '5' &&password[5] == '6' &&password[6] == '7'  )
		{
			cout<<"				it is the right number - - !!!(the one !)\n"<<endl;
			print(1);
			while(1);
		}
		else if(password[0] == '1'&&password[1] == '2' &&password[2] == '3' &&password[3] == '4' &&password[4] == '5' &&password[5] == '6')
		{
			cout<<"				it is the right number - - !!!(the TWO！)\n"<<endl;
			print(2);
			while(1);
		}
		else if(password[0] == '1'&&password[1] == '2' &&password[2] == '3' &&password[3] == '4' &&password[4] == '5')
		{
			cout<<"				it is the right number - - !!!(the THREE！)\n"<<endl;
			print(3);
			while(1);
		}
		else if(password[0] == '1'&&password[1] == '2' &&password[2] == '3' &&password[3] == '4')
		{
			cout<<"				it is the right number - - !!!(the FOUR！)\n"<<endl;
			print(4);
			while(1);
		}
		else if(password[0] == '1'&&password[1] == '2' &&password[2] == '3' )
		{
			cout<<"				it is the right number - - !!!(the FIVE！)\n"<<endl;
			print(5);
			while(1);
		}
		else if(password[0] == '1'&&password[1] == '2' )
		{
			cout<<"				it is the right number - - !!!(the Six！)\n"<<endl;
			print(6);
			while(1);
		}
		else if(password[0] == '1' )
		{
			cout<<"				it is the right number - - !!!(the Seven！)\n"<<endl;
			print(7);
			while(1);
		}


}

int panduan_l(char *login)
{
	system("cls");
	system("color 2f");
	int n=sc_out_l(login);
	//cout<<"99191919919191919199"<<endl;

	return n;
}

int panduan_p_l(char *login,string password)//判断是否用户和密码符合
{
	//sc_out_p_l(login);
	int n=password.length();
	string message_p_l;
	message_p_l=sc_out_p_l(login,n);
//	cout<<message_p_l<<"nimabi"<<endl;
//	cout<<password<<endl;
	/*char p_new[10];
	for(int i=0;i<10;i++)
	{
		p_new[i]=password[i];
	}*/
	
	if(message_p_l==password){
		//cout<<"nihao"<<endl;
		return 1;
	}
	else
	{
		return 0;
	}
	

}
int huatu_panduan(int b)//判断所画图形形状
{
	if(b==1)//san jiao
	{
		cout<<"hua san jiao xing"<<endl;
		draw(b);
	}
	if(b==2)
	{
		cout<<"hua zheng fang xing"<<endl;
		draw(b);
	}
	return 1;
}