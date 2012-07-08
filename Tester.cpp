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
		out <<s1.id ;
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



	/*Making a Testing Tree
	------------------------------------------------
	-before priority, should look like this:

	           8
			/	  \
		 /          \
	    4            12
	  /   \        /   \
	 2     6     10     14
	 /\    /\    /\     /\
	1  3  5  7  9  11  13  15

	Inorder: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
	Preorder: 8 4 2 1 3 6 5 7 12 10 9 11 14 13 15
	Postorder: 1 3 2 5 7 6 4 9 11 10 13 15 14 12 8 
	Reverseorder: 15 14 13 ... and so on
	*/

	Student hey;
	//Forcing our tree to look like the example
	int nums[15] = {8,4,12,2,6,10,14,1,3,5,7,9,11,13,15 };
	
	Treap<Student>* other = new Treap<Student>();
	
	for(int x =0; x < 15; x	++)
	{
		hey =  Student(nums[x]);
		other->insert(hey);
	}

	/*
	cout << "Size is "<<other->size() <<endl;
	cout << "Contains " << other->contains(hey) << endl;
	cout << "How many deleted? " << other->deleted() << endl;
	other->remove(hey);

	cout << "Contains " << other->contains(hey) << endl;
	
	cout << "Size is "<<other->size() <<endl;
	
	cout << "How many deleted? " << other->deleted() << endl;
	*/

	cout << endl << "Preorder Traversal ";
	other->traverse_preorder(cout, ' ');
	cout  << endl << "Postorder Traversal ";
	other->traverse_postorder(cout, ' ');
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');


	cout << "Removing " << hey << endl;
	other->remove(hey);

	cout << endl << "Preorder Traversal ";
	other->traverse_preorder(cout, ' ');
	cout  << endl << "Postorder Traversal ";
	other->traverse_postorder(cout, ' ');
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');
	
	int h;
	cin >> h;
}