/**********************************************************
* Student No: 12815482									  *	
* Student Name: Tirthankar Bhaumik                        *
* Course: MSc Computing for Financial Services            *
* Assignment: Final Assignment 4        				  *
* Objective: Demo of CPPCHECK tool - Buffer Overflows	  *
**********************************************************/
#include <iostream>
using namespace std;
void f()
{
	int x=5;
	int y=1;
	char a[10];
	if (x + y == 2)
	{
		a[20] = 0;
	}
}

int main()
{
	f();
}
