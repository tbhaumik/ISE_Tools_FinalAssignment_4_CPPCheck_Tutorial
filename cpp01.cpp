/**********************************************************
* Student No: 12815482									  *	
* Student Name: Tirthankar Bhaumik                        *
* Course: MSc Computing for Financial Services            *
* Assignment: Final Assignment 4        				  *
* Objective: Demo of CPPCHECK tool - Various bugs		  *
**********************************************************/
#include <iostream>
#include <string>
using namespace std;
bool f(int x)
{
  int i;
  if (x == 0)
  {
    i = 0;
    return false;
  }
  return true;
}

char* createT()
  { return new char[100]; }

void destroyT(void* p)
  { free(p); }

void s(int x)
{
    char* f = createT();
    if (x == 1)
        return;
    destroyT(f);
}

int main()
{
  char a[10];
  char b[20];
  a[10] = 0;
  strcpy(a, b, 25);
  for (int i=0; i<20; i++)
    b[i] = a[i];
  return 0;
}