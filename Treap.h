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


template <class T>
struct Node
{
	//should this be a pointer to meat??
	T meat;					//value of node
	bool deleted;			
	unsigned int priority;	//Random priority, for heaping
	Node<T> * right;
	Node<T> * left;

	Node<T>(T val, unsigned int prior=0) : meat(val), priority(prior)
	{};
	//WILL THE MEAT have a copy constructor?? should i make
	//it a pointer instead??
	
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
	Treap();

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


template <class T>
Treap<T>::Treap()
{

}

template <class T>
void Treap<T>::insert(const  T& val)
{
	//Not dealing with priorities yet
	
	Node<T>* insert = new Node<T>(val);
	
	//Check to see if the tree is empty.
	if(!root)
		root = insert;
	else
	{
		queue<Node <T>* > slim;
		slim.push(root);
		Node<T>* current = slim.front();

		while(!slim.empty())
		{
			current = slim.front();
			slim.pop();
		
			//do i need to check for equality??
			//First check if it should go right or left.
			//Then, if there is a R/L child, push it on stack.
			//Else, if there isn't an R/L child, set the child.
			if(val > current->meat)
			{	
				if(current->right)
					slim.push(current->right);
				else
					current->right = insert;
			}
			if(val < current->meat)
			{
				if(current->right)
					slim.push(current->left);
				else
					current->left = insert;
			}
		}
	}
}


template <class T>
int Treap<T>::size() const
{
	return all_traverse(0);
}


template <class T>
int Treap<T>::all_traverse(int which, const T& target = NULL) const
{
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
		//empty() -returns true if any node is not deleted
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

