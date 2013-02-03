/**********************************************************
* Student No: 12815482									  *	
* Student Name: Tirthankar Bhaumik                        *
* Course: MSc Computing for Financial Services            *
* Assignment: Final Assignment 4        				  *
* Objective: Demo of CPPCHECK tool - Portability Issue	  *
**********************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <iomanip>

using namespace std;

class Student
{ public:
	Student(string nm, int m1, int m2, int m3);
	string	getname() const { return name; }
	void	display() const;
  private:
	string name;
	int	math, comp, stat;
};

Student::Student(string nm, int m1, int m2, int m3) :
		name(nm), math(m1), comp(m2), stat(m3) { }

void Student::display() const
{	cout << setw(20) << name << setw(5) << math
		<< setw(5) << comp << setw(5) << stat << endl;
}

class Cohort
{
	public:
		Cohort() : treeRoot(NULL) {}
		void insert(const Student);
		Student find(const string) const;
		~Cohort();
	private:
		class Binode;
		Binode* treeRoot;
		void recInsert (const Student &, Binode*&);
		const Binode* Cohort::recSearch(const string &, const Binode*) const;
};

class Cohort::Binode
{
	public:	
		Binode(Student cstud) : left(NULL),right(NULL),astud(cstud) {} 
		Student astud;
		Binode* left, *right;
};

Cohort::~Cohort() 
{
	delete treeRoot;
}

void Cohort::recInsert(const Student &bstud, Binode* &root)
/* Recursively inserts values in a binary search tree */
{
	if (root==NULL) 
	{
		root = new Binode(bstud); 
	}
		else if (bstud.getname()<root->astud.getname())
		    {
				recInsert(bstud,root->left);
			}
			else
			{
				recInsert(bstud,root->right);
			}
}

void Cohort::insert(const Student stud) {recInsert (stud, treeRoot);}

Binode* Cohort::recSearch(const string &sname, const Binode* rptr) const
{
	if (rptr!=NULL)
	{
		if (rptr->astud.getname()==sname) return &rptr;
		if (rptr->astud.getname()>sname) 
			return recSearch(sname,rptr->left);
		else
			return recSearch(sname,rptr->right);	
	}
	else 
	{
		Student NoStudent("",-1,-1,-1);
		Binode* rptr = new Binode(NoStudent); //create a null student 
		return &rptr;
	}
}

Student Cohort::find(const string student_name) const
/* simply calls a recursive search function */
{
	Binode* rtnstu = recSearch(student_name,treeRoot);	
	return rtnstu->astud;
}
//#endif
int main()
{	Cohort	cohort;
	ifstream	infile;
	infile.open("a5.txt");	// student names and marks
	assert (! infile.fail());
	int	m, c, s;
	string	nm;
	while(infile >> m >> c >> s)
	{	getline(infile, nm);	// Names have embedded spaces
		nm = nm.substr(3);	// Skip leading spaces
		Student	st(nm, m, c, s);
		cohort.insert(st);
	}
	ifstream queryfile;
	queryfile.open("queries.txt");	// names to look for
	assert (! queryfile.fail());
	string query;
	while(getline(queryfile, query))
	{	Student	st = cohort.find(query);
		if (st.getname().length() > 0)
			st.display();
		else	cout << query << " not there" << endl;
	}
}
