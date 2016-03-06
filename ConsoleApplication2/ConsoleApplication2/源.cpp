//#include<stdio.h>
//
//int main()
//{
//	char input;
//	int allnum=0,rem=0;
//	do
//	{
//		input=getchar();
//		switch(input)
//		{
//		case ' ':case 'a':case 'd':case 'g':case 'j':case 'm':case 'p':case 't':case 'w':
//			allnum=allnum+1;
//			break;
//		case 'b':case 'e':case 'h':case 'k':case 'n':case 'q':case 'u':case 'x':
//			allnum=allnum+2;
//			break;
//		case 'c':case 'f':case 'i':case 'l':case 'o':case 'r': case 'v':case 'y':
//			allnum=allnum+3;
//			break;
//		case 's':case 'z':
//			allnum=allnum+4;
//			break;
//
//		
//		}
//		
//		rem++;
//	}while(input != '\n'&&rem<200);
//	printf("%d",allnum);
//	return 0;
//}
//#include<iostream>
//using namespace std;
//int main()
//{
//	char keys[4][11]={{'1','2','3','4','5','6','7','8','9','0','-'},
//					  {' ','Q','W','E','R','T','Y','U','I','O','P'},
//	                  {' ',' ','A','S','D','F','G','H','J','K','L'},
//	                  {' ',' ',' ','Z','X','C','V','B','N','M',','}};
//	char key;
//	cin>>key;
//	for(int i=0;i<4;i++)
//	{
//		for(int j=0;j<11;j++)
//		{
//			if(key==keys[i][j])
//			{
//				cout<<keys[i-1][j-1]<<" "<<keys[i-1][j];
//			}
//
//		}
//	}
//
//	return 0;
//}
//#include<iostream>
//using namespace std;
//int main()
//{
//	int x,up,i=1,j=1;
//	cin>>x;
//	up=2*x;
//	int *n= new int[up];
//	while(i<=x)
//	{
//		n[i]=i;
//		i++;
//	}
//	i=1;
//	while(x-j>=0)
//	{
//		cout<<n[i]<<" ";
//		n[x+j]=n[++i];
//		i++;
//		j++;
//	}
//	return 0;
//}
//#include<iostream>
//using namespace std;
//int main()
//{
//	int n;
//    cin>>n;
//    if(n>=90)
//		cout<<"A";
//	else if(n>=80)
//		cout<<"B";
//	else if(n>=70)
//		cout<<"C";
//	else if(n>=60)
//		cout<<"D";
//	else 
//		cout<<"E";
//	return 0;
//}
//#include <iostream>
//using namespace std;
//int main()
//{
//	int k,m,a=0,b=0,c=0,i=1;
//	cin>>k;
//	while(i<=k)
//	{
//		cin>>m;
//		switch(m)
//		{
//		case 1:
//			a++;
//			break;
//		case 5:
//			b++;
//			break;
//		case 10:
//			c++;
//			break;
//		}
//		i++;
//	}
//	cout<<a<<endl<<b<<endl<<c;
//
//	return 0;
//}
//#include <stdio.h>
//int main()
//{
//	float a;
//	scanf("%f",&a);
//	if(a>100)
//		printf("false");
//	else if(a>90&&a<=100)
//		printf("ok");
//}
	/*printf("商品名称\t 购买数量\t 商品单价\t 金额\t\n");
	printf("iPhone  \t 1       \t 5000    \t 5000\t\n");
}*/
#include <stdio.h>
void main()
{
	int a[100];
	printf("hello world!\n");
	printf("%d",sizeof (a));
}