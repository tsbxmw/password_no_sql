#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include"includes.h"
using namespace std;
void display(int n)
{
	string name;
	if(n == 1)
	{
		name = "test_1.txt";
	}
	if(n == 2)
	{
		name = "test_2.txt";
	}
	if(n == 3)
	{
		name = "test_3.txt";
	}
	if(n == 4)
	{
		name = "test_4.txt";
	}
	if(n == 5)
	{
		name = "test_5.txt";
	}

	sc_out(name);
}