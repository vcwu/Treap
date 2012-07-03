/**
Victoria Wu
CS 352

Treap

An implementation of a binary search tree that incorporates properties of a heap,
preventing an overly imbalanced tree.
*/

#include <queue>
#include <stack>
#include <iostream>
using namespace std;

/**
TreapException is thrown when
Called on empty treap/Removing non existent value
	remove() 
	remove_min, remove_max
	find_min, find_max

*/
class TreapException
{
};

template <class T>
struct Node
{
	//should this be a pointer to meat??
	T meat;					//value of node
	bool deleted;			
	unsigned int priority;	//Random priority, for heaping
	Node<T> * right;
	Node<T> * left;

	Node<T>(T val, bool del = false, unsigned int prior=0, Node<T>* l = 0, Node<T>* r = 0) 
		: meat(val), deleted(del), priority(prior), right(r), left(l)
	{};
	//WILL THE MEAT have a copy constructor?? should i make
	//it a pointer instead??

	//Can I assume that meat will have output operator overloading?
	friend ostream& operator<< (ostream &out, Node &p)
	{
		out << p.meat << endl;
		return out;
	}

	
};

template <class T>
class Treap
{
	
private:
	Node<T>* root;

	/**
	all_traverse()

	Traverses all nodes in the tree breadth first, disregarding 
	deleted or not. Helper method for size(), deleted(), empty(), contains().

	Depending on which method calls..
	size()		returns how many un deleted
	delted()	returns how many deleted
	empty()		returns if empty (bool - 0,1)
	contains()	returns if found (bool - 0,1)

	*/
//	int all_traverse();


public:

	int all_traverse(int which, const T& target = NULL) const; //put in public for testing purposes
	Treap() {root = NULL;} 

	~Treap() {}
	Treap(const Treap& other); 
	Treap& operator=(const Treap<T> &rhs);

	/**
	insert(const &T meat)

	Inserts a node into the tree. 
	*/
	void insert(const T& meat);

	/**
	remove(const T& meat)

	Removes node with the given value.
	If no node with that value exists, does nothing.
	If called on an empty Treap, throws TreapException.
	*/
	T remove(const T& meat);
	
	/**
	remove_min()

	Removes the node with the minumum value from the tree
	and returns the removed value.
	Throws TreapException if called on empty Treap.
	*/
	T remove_min();

	
	/**
	remove_max();

	Removes the node with the max value from the tree
	and returns the removed value.
	Throws TreapException if called on empty Treap.
	*/
	T remove_max();

	/**
	find_min()

	Finds and returns the minimum value.
	Throws TreapException if called on empty Treap.
	*/
	T find_min() const; 

	/**
	find_max()

	Finds and returns the maximum value.
	Throws TreapException if called on empty Treap.
	*/
	T find_max() const; 

	/**
	contains(const T& meat) const

	Returns whether or not the given value is 
	located in the treap. Does not change the Treap.
	*/
	bool contains(const T& meat) const;
	/**
	empty()

	Returns whether or not the Treap is logically empty.
	Does not change the Treap.
	*/
	bool empty() const;

	/**
	int size()
	
	Returns the logial size of the treap.
	Does not change the Treap. 
	*/
	int size() const;

	/**
	int deleted()

	Returns the number of logically deleted nodes.
	Does not change the treap.
	*/
	int deleted() const;
	
	/**
	void cleanup()

	Rebuilds Treap by physically removing logically 
	deleted nodes. Automatically called if Treap has >
	100 items and has more than 3/4 deleted nodes. 
	*/
	void cleanup();

	/**
	traverse_preorder

	Returns the values of the nodes traveled in 
	preorder as an ostream. 
	*/
	void traverse_preorder(ostream& o, char delim = '\n');
	
	/**
	traverse_ineorder

	Returns the values of the nodes traveled in 
	inorder (R-root-L) as an ostream. 
	*/
	void traverse_inorder(ostream& o, char delim = '\n');
	
	/**
	traverse_reverseorder

	Returns the values of the nodes traveled in 
	reverse order (L-root-R) as an ostream. 
	*/
	void traverse_reverseorder(ostream& o, char delim = '\n');
	
	/**
	traverse_postorder

	Returns the values of the nodes traveled in 
	post order (L-R-Root) as an ostream. 
	*/
	void traverse_postorder(ostream& o, char delim = '\n');
	
};
 
/**
Silently ignores inserting repeated values. 
*/
template <class T>
void Treap<T>::insert(const  T& val)
{
	//Not dealing with priorities yet
	
	Node<T>* insert = new Node<T>(val);
	
	//Check to see if the tree is empty.
	if(!root)
	{
		root = insert;
		cout << "Inserting root" << *insert <<  endl;
	}
	else
	{
		
		queue<Node <T>* > slim;
		slim.push(root);
		
		while(!slim.empty())
		{
			Node<T>* current = slim.front();
			slim.pop();
		
			//First check if it should go right or left.
			//Then, if there is a R/L child, push it on stack.
			//Else, if there isn't an R/L child, set the child.
			if(val > current->meat)
			{	
				if(current->right == NULL)
				{
					current->right = insert;
					cout << "Inserting " << *insert << "as right child of "
						<< *current << endl;
				}
				else
					slim.push(current->right);
			}
			if(val < current->meat)
			{
				if(current->left == NULL)
				{
					cout << "Inserting " << *insert << "as left child of "
						<< *current << endl;
					current->left = insert;
				}
				else
					slim.push(current->left);
			}
		}
	}
}

template <class T>
T Treap<T>::remove(const T& val)
{
	//If called on an empty tree, throws exception
	if(!root)
		throw TreapException();	//shall I assume it will be caught outside?

	
	queue< Node<T>* > slim;
	slim.push(root);
	Node<T>* current = slim.front();

	while(!slim.empty())
	{
		current = slim.front();
		slim.pop();
		
		if(val > current->meat)
		{	
			//Can't find value! 
			if(current->right == NULL)
			{
				throw TreapException();
			}
			else
				slim.push(current->right);
		}
		else if(val < current->meat)
		{
			//Can't find value! 
			if(current->left == NULL)
			{
				throw TreapException();
			}
			else
				slim.push(current->left);
		}
		else
		{
			//Hey, we found it!!
			current->deleted = true;
		}
	}
	return current->meat;
}


template <class T>
int Treap<T>::size() const
{
	return all_traverse(0);
	
}

template <class T>
int Treap<T>::deleted() const
{
	return all_traverse(1);
}

template <class T>
bool Treap<T>::empty() const
{
	//Note- all_traverse(2) is the equivalent of 
	//NOTempty(). Thus returning the negation.
	bool ans  = (all_traverse(2) == 1);
	return !ans;
}
/*
template <class T>
bool contains(const T& meat) const
{
	return all_traverse(3);
	
}
*/
//all traverse check for NULL works
template <class T>
int Treap<T>::all_traverse(int which, const T& target = NULL) const
{
	//First, check if the treap is physically empty.
	if(!root)
		return 0;
	
	int meat = 0;	//default to false as well
	queue< Node<T>* > slim;
	slim.push(root);

	while(!slim.empty())
	{
		Node<T>* current = slim.front();
		slim.pop();
		
		//Depending on what method calls, 
		//meat is counted differently.
		switch(which)
		{
		//size() -counts non deleted nodes
		case 0:
			if(!(current->deleted))
				meat++;
			break;
		//deleted - counts deleted nodes
		case 1:
			if(current->deleted)
				meat++;
			break;
		//notEmpty() -returns true if any node is not deleted
		case 2:
			if(!(current->deleted))
				return 1;
			break;
		//contains() - returns if treap has the target
		/////need to test this bit! T.T
		case 3:
			if(!(current->deleted)
				&& current->meat == target)
				return 1;
			break;
		}

		//Push the children, if any, onto the queue
		if(current->left)
			slim.push(current->left);
		if(current->right)
			slim.push(current->right);
	}
	return meat;
}

