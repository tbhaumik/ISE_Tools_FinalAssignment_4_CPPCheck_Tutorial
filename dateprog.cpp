/* Definition and member functions for Date class */
/* "and" and "or" have been replaced with && and || for compatibility with Borland and g++ compilers */

#include <iostream>
#include <string>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <sstream>
using namespace std;

void f(int x)
{
	int i;
	if (x == 0)
	{
		i = 0;
	}
}

class Month
{ public:
	char name[4];	// Can't do initialization if this is string
	int days;
};

class Date
{	friend istream& operator>>(istream& is, Date& d);
  public:
	Date();
	Date(int d, int m);
	void add_day();
	void print() const;
	bool precedes(const Date&) const;
	bool operator<(const Date&) const;
	bool operator==(const Date&) const;
	int operator-(const Date&) const;
	void operator<<(ostream&) const;
	bool operator>(const Date&) const;
	void daysplus(int);
	Date operator += (int);
	
  private:
	static const int NMTHS = 12;	// can also use globals
	static const int YEARDAYS = 365;
	static const Month months[];
	int daynum() const;
	Date numday(int);
	int day;
	int month;
};

class CurrentDate
{
	int DD;
	int MM;
	int YY;
	
};

const Month Date::months[NMTHS+1] = {{"", 0}, {"Jan", 31}, {"Feb", 28}, {"Mar", 31}, {"Apr", 30}, {"May", 31}, {"Jun", 30}, {"Jul", 31}, {"Aug", 31}, {"Sep", 30}, {"Oct", 31}, {"Nov", 30}, {"Dec", 31}};

Date::Date()
{	//day = 1;
	//month = 1;
	time_t hold_time = time(NULL);
	istringstream is(ctime(&hold_time));

}

Date::Date(int d, int m)
{	if (m < 1 || m > NMTHS)
	{	cerr << "Invalid month value" << endl;
		exit(1);
	}
	//cout<<d<<endl;
	if (d < 1 || d > months[m].days)
	{	cerr << "Invalid day value" << endl;
		exit(2);
	}
	// or you could use an assert:
	assert (m >= 1 && m <= NMTHS && d >= 1 && d <= months[m].days);
	day = d;
	month = m;
}

void Date::print() const
{	cout << day;
	cout << " " << months[month].name << endl;
}

bool Date::precedes(const Date& d) const
{	return month < d.month || (month == d.month && day < d.day);
}

bool Date::operator<(const Date& d) const	// same as preceding, with op overload
{	return month < d.month || (month == d.month && day < d.day);
}

bool Date::operator==(const Date& d) const
{	return month == d.month && day == d.day;
}

int Date::daynum() const
{	int	dnum = 0;
	for (int i = 1; i < month; i++)
		dnum += months[i].days;
	dnum += day;
	return dnum;
}

Date Date::numday(int n) 
{
	int	dnum = 0;
	int i;
	for (int i=1; i<=NMTHS; i++)
	{
		dnum += months[i].days;
		//cout<<endl<<dnum<<endl;
		if (dnum>n)
		{
			//cout<<"dnum : "<<dnum<<endl;
			//cout<<"n : "<<n<<endl;
			//cout<<"i : "<<i<<endl;
			
			month=i;
			day =  (months[i].days)-(dnum-n);
			break;
			
		}else if (dnum==n)
		{
			month=i;
			day = months[i].days;
			break;
		}
	}
	return Date(day,month);
}

void Date::add_day()
{	if (day == months[month].days)
	{	day = 1;
		month = month % NMTHS + 1;
	}
	else day++;
}

void Date::daysplus(int d)
{
	int nofdays1= daynum();
	//cout<<"noofdays: "<<nofdays1<<endl;
	//cout<<"d: "<<d<<endl;
	//cout<<"d+noofday"<<d+nofdays1<<endl;
	if ((d+nofdays1)>365)
	{
		//cout<<"this one"<<endl;
		numday(d+nofdays1-YEARDAYS);
	}
	else //less than or equal to
	{
		//cout<<"that one"<<endl;
		numday(d+nofdays1);
	}	
}

Date Date::operator += (const int n)
{
	int nofdays1= daynum();
	if ((n+nofdays1)>365)
	{
		return numday(n+nofdays1-YEARDAYS);
	}
	else //less than or equal to
	{
		return numday(n+nofdays1);
	}
}
int Date::operator-(const Date& d) const
{	return daynum() - d.daynum();
}

void Date::operator<<(ostream& os) const	// member function called by non-member function of same name
{	os << day << " " << months[month].name;
}

ostream& operator<<(ostream& os, const Date& d)	// non-member function
{	d.operator<<(os);
	return os;
}

istream& operator>>(istream& is, Date& dt)	// non-member friend function
{	cout << "Give me a day: ";
	int d;
	is >> d;
	if (is.fail())
		return is;
	cout << "and a month: ";
	int m;
	is >> m;
	assert (m >= 1 && m <= dt.NMTHS && d >= 1 && d <= dt.months[m].days);
	dt.day = d;
	dt.month = m;
	return is;
}

bool Date::operator>(const Date& dt) const
{
	return month > dt.month || (month == dt.month && day > dt.day); 
}

int main()
{
	Date d1(12,06);
	Date d2;
	
	//cin>>(cin,d2); WRONG
	cin>>d2;
	
	d1.print();
	
	//d2.operator<<(cout); WRONG
	cout<<d2;
	
	cout<<endl;
	if (d1.precedes(d2))
	{
		cout<<"d1 preceeds d2 "<<endl;
	}
	
	if (d1<d2)
	{
		cout<<"d2 is not < dl"<<endl;
	}

    if (!(d1==d2))
	{
		cout<<"d1 and d2 are not the same date"<<endl;
	}
	
	d2.add_day();
	d2.print();
	
	d1=d2;
	if (d1==d2)
	{
		cout<<"d1 and d2 are the same date"<<endl;
	}
    
 	if (d2>d1)
	{
		cout<<"d2 is greater"<<endl;
	}
	else
	{
		cout<<"d2 is not greater than d1"<<endl;
	}
	
	Date d3(31,12);
	d3.print();
	d3.daysplus(18);
	d3.print();
	
	Date d4(30,12);
	d4.print();
	d4+=18;
	d4.print();
	
	Date d5;
	cout<<endl;
	d5.print();
	
}
