/**
Victoria Wu
CS 352

Treap

An implementation of a binary search tree that incorporates properties of a heap,
preventing an extremely imbalanced tree.


*/

asdfasdfadsfasdf
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
	Treap(Treap<T> other);
	~Treap() {}
	&Treap operator=(const &Treap t);

	/**
	insert(const &T meat)

	Inserts a node into the tree. 
	*/
	void insert(const &T meat);

	/**
	remove(const &T meat)

	Removes node with the given value.
	If no node with that value exists, does nothing.
	If called on an empty Treap, throws TreapException.
	*/
	T remove(const &T meat);
	
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

	Finds and returns the minimum value.
	Throws TreapException if called on empty Treap.
	*/
	T find_max() const; 


	bool contains(const &T meat) const;
	bool empty() const;
	int size() const;
	int deleted() const;
	void cleanup();
	void traverse_preorder(&ostream o, char delim = '\n');
	void traverse_inorder(&ostream o, char delim = '\n');
	void traverse_reverseorder(&ostream o, char delim = '\n');
	void traverse_postorder(&ostream o, char delim = '\n');
	asdfadfasdfasdf
}
/**
all_traverse()

Traverses the tree using a queue, depending on 
what function called it will return different values. 
*/
template <class T>
int Treap<T>::all_traverse()
{
	queue<Node<T>*> slimJim;		
	slimJim.push(root);
	
}








