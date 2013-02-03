/**********************************************************
* Student No: 12815482									  *	
* Student Name: Tirthankar Bhaumik                        *
* Course: MSc Computing for Financial Services            *
* Assignment: Final Assignment 4        				  *
* Objective: Demo of CPPCHECK tool - Performance Issue	  *
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

void	Student::display() const
{	cout << setw(20) << name << setw(5) << math
		<< setw(5) << comp << setw(5) << stat << endl;
}

// Include the next line to test the vector version; delete it to test the
// binary tree version
#define FIRST
#ifdef FIRST

//Vector version
class Cohort
{
	public:
		void insert(const Student);
		Student find(const string) const;
	private:
		vector<Student> student_vec; 
		Student binaryVecSearch(const vector<Student> &,const int, const int, const string &) const;
};

void Cohort::insert (const Student stud)
/* Inserts student objects in a sorted vector */
{
	if (student_vec.size()==0)
		{
			student_vec.push_back(stud); // the first insert	
		}
	else
		{	/* Loop through the vector to find right alphabetical position */
			for (int i=0; i<=static_cast<int>(student_vec.size())-1;i++)
			{
				if (stud.getname()<student_vec[i].getname()) //right position found 
				{
					Student tempStudent("Temp", -1,-1,-1); //create temporary object
					student_vec.push_back(tempStudent); // pushback temporary cell at end
					/* move all remaining values behind by one cell */
					for (int j=student_vec.size()-1;j>i;j--){student_vec[j] = student_vec[j-1];}
					student_vec[i]=stud; // insert student at the correct position
					return;
				}
				else
				{	/* check if reached the last vector cell - then add at end */
					if (i==static_cast<int>((student_vec.size())-1)) 
					{
						student_vec.push_back(stud);
						return;
					}	
				}
			}
		}	
}

Student Cohort::binaryVecSearch(const vector<Student> &stud_vec,const int low, const int high, const string &s) const
/* Recursively performs binary search on a sorted vector */
{
	if (low>high)
		{
			Student emptyStudent("",-1,-1,-1);
			return emptyStudent;
		}	
	int mid = (low+high)/2; //calculate the middle cell position
	if (stud_vec[mid].getname()==s)
	{
		return stud_vec[mid];
	}
	else
	{
		if (stud_vec[mid].getname()>s)
		{   
			return binaryVecSearch(stud_vec,low,mid-1,s); 
		}
		else
		{	
			return binaryVecSearch(stud_vec,mid+1,high,s);
		}
	}
}

Student Cohort::find(const string student_name) const
/* Simply calls a recursive search function */
{
	return binaryVecSearch(student_vec,0,student_vec.size()-1,student_name); 
}


#else

//Binary Tree version
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
		Student recSearch(const string &, const Binode*) const;
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

Student Cohort::recSearch(const string &sname, const Binode* rptr) const
/* Recursively performs binary search on a binary search tree */
{
	if (rptr!=NULL)
	{
		if (rptr->astud.getname()==sname) return rptr->astud;
		if (rptr->astud.getname()>sname) 
			return recSearch(sname,rptr->left);
		else
			return recSearch(sname,rptr->right);	
	}
	else 
	{
		Student NoStudent("",-1,-1,-1); //create a null student 
		return NoStudent;
	}
}

Student Cohort::find(const string student_name) const
/* simply calls a recursive search function */
{
	return recSearch(student_name,treeRoot);	
}


#endif

int main()
{	Cohort	cohort;
	ifstream	infile;
	infile.open("n:\\C++\\a5.txt");	// student names and marks
	assert (! infile.fail());
	int	m, c, s;
	string	nm;
	while(infile >> m >> c >> s)
	{	getline(infile, nm);	// Names have embedded spaces
		nm = nm.substr(3);	// Skip leading spaces
		Student	st(nm, m, c, s);
		cohort.insert(st);
	}
	ifstream	queryfile;
	queryfile.open("n:\\C++\\queries.txt");	// names to look for
	assert (! queryfile.fail());
	string query;
	while(getline(queryfile, query))
	{	Student	st = cohort.find(query);
		if (st.getname().length() > 0)
			st.display();
		else	cout << query << " not there" << endl;
	}
}
