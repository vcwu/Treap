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

	//=====================================================
	//MAKING OUR TEST SUBJECTS
	//=====================================================

	//Making a Testing Tree, normal.
	//------------------------------------------------
	/*
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

	Student smallest(0);

	//Forcing our tree to look like the example
	int nums[15] = {8,4,12,2,6,10,14,1,3,5,7,9,11,13,15 };
	Student allStudents[15];
	Treap<Student>* other = new Treap<Student>();

	for(int x = 0; x <15; x++)
	{
		allStudents[x] = Student(nums[x]);
		other->insert(allStudents[x]);
	}

	other->insert(smallest);

	//Making a Testing Tree, with One physical obj. 
	//------------------------------------------------
	Treap<Student>* onePhysical = new Treap<Student>();
	onePhysical->insert(Student(9999));

	//Making a Testing Tree, with many physical, one logical obj. 
	//------------------------------------------------
	Treap<Student>* oneLogical = new Treap<Student>();
	oneLogical->insert(smallest);
	for(int x = 0; x< 2; x++)
	{
		oneLogical->insert(allStudents[x]);
		oneLogical->remove(allStudents[x]);
	}


	//Making a Testing Tree, empty, for TreapException
	//------------------------------------------------

	Treap<Student>* empty = new Treap<Student>();



	//=====================================================
	//TESTING STUFF 
	//=====================================================

	//Testing Size, Contains, Deleted, Empty
	//-------------------------------------------
	/*
	cout << "Size is "<<other->size() <<endl;
	cout << "Contains " << other->contains(hey) << endl;
	cout << "How many deleted? " << other->deleted() << endl;
	other->remove(hey);

	cout << "Contains " << other->contains(hey) << endl;
	
	cout << "Size is "<<other->size() <<endl;
	
	cout << "How many deleted? " << other->deleted() << endl;
	cout << "Empty?" << other->empty() << endl;
	*/

	//Testing Traversals
	//-------------------------------------------

	try
	{
	/*
	cout << endl <<endl<< "Traversing through a normal tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Preorder Traversal ";
	other->traverse_preorder(cout, ' ');
	cout  << endl << "Postorder Traversal ";
	other->traverse_postorder(cout, ' ');
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');
	cout  << endl << "Reverse order Traversal ";
	other->traverse_reverseorder(cout, ' ');

	cout << "Removing " << allStudents[4] << endl;
	other->remove(allStudents[4]);

	cout << endl << "Preorder Traversal ";
	other->traverse_preorder(cout, ' ');
	cout  << endl << "Postorder Traversal ";
	other->traverse_postorder(cout, ' ');
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');
	cout  << endl << "Reverse order Traversal ";
	other->traverse_reverseorder(cout, ' ');

	*/
	/*
	cout << endl <<endl<< "Traversing through a logical one node tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Preorder Traversal ";
	oneLogical->traverse_preorder(cout, ' ');
	cout  << endl << "Postorder Traversal ";
	oneLogical->traverse_postorder(cout, ' ');
	cout  << endl << "Inorder Traversal ";
	oneLogical->traverse_inorder(cout, ' ');
	cout  << endl << "Reverse order Traversal ";
	oneLogical->traverse_reverseorder(cout, ' ');

	cout << endl <<endl << "Traversing through empty tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Preorder Traversal ";
	empty->traverse_preorder(cout, ' ');
	cout  << endl << "Postorder Traversal ";
	empty->traverse_postorder(cout, ' ');
	cout  << endl << "Inorder Traversal ";
	empty->traverse_inorder(cout, ' ');
	cout  << endl << "Reverse order Traversal ";
	empty->traverse_reverseorder(cout, ' ');
	*/

	//Testing Find Min, find max
	//-------------------------------------------

	/*
	cout << endl <<endl<< "Finding Min of one node tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Find min ";
	cout << oneLogical->find_min() << endl;

	cout << "Removing " << smallest << endl;
	oneLogical->remove(smallest);
	
	cout << endl << "Find min ";
	cout << oneLogical->find_min() << endl;
	*/
	/*
	cout << endl <<endl<< "Finding Max of one node tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Find max ";
	cout << oneLogical->find_max() << endl;

	cout << "Removing " << smallest << endl;
	oneLogical->remove(smallest);
	
	//cout << endl << "Find max ";
	//cout << oneLogical->find_max() << endl;
	*/
	cout << endl <<endl<< "Finding Min of normal tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Find min ";
	cout << other->find_min() << endl;

	cout << "Removing " << smallest << endl;
	other->remove(smallest);
	
	cout << endl << "Find min ";
	cout << other->find_min() << endl;

	cout << "Removing " << allStudents[7] << endl;
	other->remove(allStudents[7]);

	cout << endl << "Find min ";
	cout << other->find_min() << endl;

	cout << endl <<endl<< "Finding Max of normal tree"
		<< endl << "--------------------------" << endl;
	cout << endl << "Find max ";
	cout << other->find_max() << endl;

	cout << "Removing " << allStudents[14] << endl;
	other->remove( allStudents[14]);
	
	cout << endl << "Find max ";
	cout << other->find_max() << endl;

	cout << "Removing " << allStudents[6] << endl;
	other->remove( allStudents[6]);
	
	cout << endl << "Find max ";
	cout << other->find_max() << endl;

	//Testing Removing 
	//-------------------------------------------
	//Removing a non existant node.
	
	Student hey(999999);	
	//cout << "Removing non existant node" << hey << endl;
	//other->remove(hey);	
	

	//Removing a physically present, logically del node.
	/*
	cout << "Removing " << allStudents[2] << endl;
	other->remove(allStudents[2]);
	cout << "Removing again " << allStudents[2] << endl;
	other->remove(allStudents[2]);
	*/


	//Testing Remove min, remove max
	//-------------------------------------------
	/*
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');
	cout <<endl << "Removing min.. " << other->remove_min() <<endl;
	cout <<endl << "Removing max.. " << other->remove_max() <<endl;
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');

	cout  << endl << "Inorder Traversal ";
	onePhysical->traverse_inorder(cout, ' ');
	//cout <<endl << "Removing min.. " << onePhysical->remove_min() <<endl;
	cout <<endl << "Removing max.. " << onePhysical->remove_max() <<endl;
	cout  << endl << "Inorder Traversal ";
	onePhysical->traverse_inorder(cout, ' ');
	*/

	//Testing my destructors, copy constructors, assignment

	//why am i deleting other??? 
	cout  << endl << "Inorder Traversal ";
	other->traverse_inorder(cout, ' ');	

	Treap<Student> hello( *other);
	cout  << endl << "Inorder Traversal of Hello ";
	hello.traverse_inorder(cout, ' ');	
	cout  << endl << "Inorder Traversal of Other";
	other->traverse_inorder(cout, ' ');

	//other->~Treap();
	//hello.~Treap();
	
	cout  << endl << "Inorder Traversal of onePhysical before";
	onePhysical->traverse_inorder(cout, ' ');

	onePhysical = other;
	cout  << endl << "Inorder Traversal of onePhysical after";
	onePhysical->traverse_inorder(cout, ' ');



	//Testing cleanup
	cout  << endl << "Logical Size /Physical size Before" 
		<< endl << oneLogical->logicalSize() << " / " 
		<< oneLogical->physSize() << endl;
	oneLogical->cleanup();
	cout  << endl << "Logical Size /Physical size After" 
		<< endl << oneLogical->logicalSize() << " / " 
		<< oneLogical->physSize() << endl;


	int h;
	cin >> h;
	}
	catch( TreapException )
	{
		cout << "Hey you caught a TreapException! " << endl;
	}
}