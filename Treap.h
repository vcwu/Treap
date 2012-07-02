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
	T meat;
	bool deleted;
	unsigned int priority;
	Node* right, left;
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
	int all_traverse();


public:


	Treap() {}

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
all_traverse()

Traverses the tree using a queue, depending on 
what function called it will return different values. 
*/









