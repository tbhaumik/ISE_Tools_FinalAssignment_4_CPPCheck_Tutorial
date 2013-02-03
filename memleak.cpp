/**********************************************************
* Student No: 12815482									  *	
* Student Name: Tirthankar Bhaumik                        *
* Course: MSc Computing for Financial Services            *
* Assignment: Final Assignment 4        				  *
* Objective: Demo of CPPCHECK tool - Memory leak		  *
**********************************************************/
#include <iostream>
using namespace std;

void f()
{
	int x=1;
	int y=2;
	char *a = (char *)malloc(10);
	
	if (x + y == 2) 
	{
		return;
	}
	free(a);
}

int main()
{
	f();
}
