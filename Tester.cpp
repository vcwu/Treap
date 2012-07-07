#include "Treap.h"
#include <iostream>
using namespace std;

class Student
{
private:
	int id;
public:
	Student() {}
	Student(int i) : id(i) {}
	friend bool operator>(const Student& s1, const Student& s2)
	{
		return (s1.id>s2.id);
	}

	friend bool operator==(const Student& s1, const Student& s2)
	{
		return (s1.id == s2.id);
	}

	friend bool operator<(const Student& s1, const Student& s2)
	{
		return (s1.id<s2.id);
	}
	
	friend ostream& operator<< (ostream& out, Student& s1)
	{
		out<< "Student ID: " <<s1.id << endl;
		return out;
	}
};


int main()
{

	/*
	Treap<int>* meat = new Treap<int>();
	
	//Hmm, seens that bools just default to printing 0 and 1. T.T

	meat->insert(3);
	meat->insert(1);
	meat->insert(2);
	meat->insert(53);
	meat->insert(5);	
	

	cout << "Contains " << meat->contains(3) << endl;
	cout << "Deleting" << meat->remove(3) << endl;
	cout << "Contains " << meat->contains(3) << endl;
	cout << "Size is "<<meat->size() <<endl;

	cout << "Empty?" << meat->empty() << endl;
	*/

	//testing with student obj

	Student hey;

	Treap<Student>* other = new Treap<Student>();
	for(int x =0; x < 5; x++)
	{
		hey =  Student(x);
		other->insert(hey);
	}

	cout << "Size is "<<other->size() <<endl;
	cout << "Contains " << other->contains(hey) << endl;
	
	other->remove(hey);

	cout << "Contains " << other->contains(hey) << endl;
	
	cout << "Size is "<<other->size() <<endl;
	
	int h;
	cin >> h;
}