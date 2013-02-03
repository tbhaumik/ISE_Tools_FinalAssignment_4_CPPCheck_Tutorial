/**********************************************************
* Student No: 12815482									  *	
* Student Name: Tirthankar Bhaumik                        *
* Course: MSc Computing for Financial Services            *
* Assignment: Final Assignment 4        				  *
* Objective: Demo of CPPCHECK tool - Exception Safety	  *
**********************************************************/
#include <iostream>
using namespace std;

int *p;
int a(int sz)
{
	delete [] p;
	if (sz <= 0)
		throw std::runtime_error("size <= 0");
	p = new int[sz];
}

int main()
{}
