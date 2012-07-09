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



	Node<T>(T val, unsigned int prior=0, bool del = false, Node<T>* l = 0, Node<T>* r = 0) 
		: meat(val), deleted(del), priority(prior), right(r), left(l)
	{};

	~Node<T>()
   	{
		delete right; delete left;
		right = 0; left = 0;
		cout << "Deleting Node" << endl;
	}

	Node<T>(const Node<T>& other)
	{
		meat = other.meat; deleted = other.deleted;
		priority = other.priority;
		right = 0; left = 0;
	}
};

template <class T>
class Treap
{
	
private:
	Node<T>* root;
	int physical;
	int logical;
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
	int all_traverse(int which, const T& target = NULL) const;



public:

	Treap() {root = NULL; physical = 0; logical = 0;} 

	~Treap() {delete root;}

	Treap(const  Treap& other); 
	Treap& operator=(const Treap<T> &rhs);

	/**
	logicalSize()

	Returns logical size, used for testing.
	*/
	int logicalSize() {return logical;}

	/**
	physSize()

	Returns physical size, used for testing.
	*/
	int physSize() {return physical;}
	

	/**
	insert(const &T meat)

	Inserts a node into the tree. 
	*/
	void insert(const T& meat);

	/**
	insert(const &T meat, priority)

	Inserts a node into the tree with the given priority. 
	*/
	void insert(const T& meat, unsigned int priority);

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
	
	/**
	Random num generator, provided by instructor
	*/
	static unsigned int Treap_random() 
	{
	// This algorithm isn't nearly good enough for something needing seriously 
	// random numbers, but is good enough for our purposes here--a kinda-sorta 
	// random sequence that's not correlated with the input data we're storing in the 
	// tree. Constants taken from Visual Studio 2010 rand(). 
	static unsigned _int64 seed = 0; 

	seed = ((seed*214013) + 253011) & 0xFFFFFFFFFFF; // keep low 44 bits for computation
	return (unsigned int(seed & 0xFFFFFFFFF>>4)); // and return 32 bits of pseudorandom goodness. 
	// The last bit-shift throws out the lowest-order 4 bits, which are the least 'random'
	// produced by this sequence. (If we just grab the low order bits, for example, the 
	// numbers produced by this sequence alternate between even and odd--hardly 'random' 
	// enough for almost any purpose.) So we're taking 36 bits and returning 32 of them. 
	// This is better than the default, but again, is far from perfect. 
	}


};



template <class T>
Treap<T>::Treap(const Treap& other)
{
	//The lovely copy constructor
	root = NULL;
	physical = 0;
	logical = 0;

	queue< Node<T>* > slim;
	slim.push(other.root);

	while(!slim.empty())
	{
		Node<T>* current = slim.front();
		slim.pop();

		if(!current->deleted)
		{
			insert(current->meat);
		}
		//Push the children, if any, onto the queue
		if(current->left)
			slim.push(current->left);
		if(current->right)
			slim.push(current->right);
	}



}
template <class T>
Treap<T>& Treap<T>::operator=(const Treap<T> &rhs)
{
	//Code structure modified from Wikipeida article on
	//Assignment Operator

	if(this != &rhs)
	{
		//Alocate new mem. Copy elements
		
		queue< Node<T>* > slim;
		slim.push(rhs.root);

		while(!slim.empty())
		{
			Node<T>* current = slim.front();
			slim.pop();

			if(!current->deleted)
			{
				insert(current->meat);
			}
			//Push the children, if any, onto the queue
			if(current->left)
				slim.push(current->left);
			if(current->right)
				slim.push(current->right);
		}

	}
	return *this;
}


template <class T>
void Treap<T>::insert(const T& val)
{
	unsigned int prior = Treap_random();
	insert(val, prior);
}

template <class T>
void Treap<T>::insert(const  T& val, unsigned int priority)
{
	//Silently ignores inserting repeated values.
	Node<T>* insert = new Node<T>(val, priority);
	stack<Node <T>* > parents;	
	stack<bool> rightChild;	//keep track of inserted
							//as l or r child


	//Parents and rightChild
	//parents[x] is the parent node.
	//rightChild[x] indicates if the child of parent is R/L
	
	//If there already exists a node with the val that is 
	//deleted, no need to do any rotations. 
	bool alreadyPrior = false;			

	//Check to see if the tree is empty.
	if(root == NULL)
	{
		root = insert;
		cout << "Inserting root" << insert->meat <<  endl;
		physical ++;
		logical ++;
	}
	else
	{
		
		queue<Node <T>* > slim;
		slim.push(root);

		while(!slim.empty())
		{
			Node<T>* current = slim.front();
			parents.push(current);
			slim.pop();
		
			//First check if it should go right or left.
			//Then, if there is a R/L child, push it on stack.
			//Else, if there isn't an R/L child, set the child.
			if(val > current->meat)
			{	
				if(current->right == NULL)
				{
					current->right = insert;
					cout << "Inserting " << insert->meat << "as right child of "
						<< current->meat << endl;
					physical++;
					logical++;
				}
				else
				{
					slim.push(current->right);
					//A right child.
					rightChild.push(true);
				}
			}
			if(val < current->meat)
			{
				if(current->left == NULL)
				{
					cout << "Inserting " << insert->meat << "as left child of "
						<< current->meat << endl;
					current->left = insert;
					physical++;
					logical++;
				}
				else
				{
					slim.push(current->left);
					rightChild.push(false);	//a left child
				}
			}
			//If value is  physically present,  but logically deleted
			//mark it as non deleted again.
			//For priorities, this SHOULD be in the correct place already.
			//since it was once inserted as left/right child...
			if(val == current->meat)
			{
				if(current->deleted)
				{
					current->deleted = false;
					current->priority = priority;
					logical++;	//Physically already present. 			
					alreadyPrior = true;
				}
		
			}
		}

		//Now, using the stack of parents, we rotate as long 
		//as the child's priority is smaller than parents
		//to form a minheap of priorities.

		//don't need to worry about inserting root, there will at least be 
		//one node in parents

		if(!alreadyPrior)	//Inserted a completely new node that
							//needs to be heap-ed.
		{
			Node<T>* parent = parents.top();
			parents.pop();
			
			while(!parents.empty() && insert->priority < parent->priority)
			{
				//Priorities are out of sync, must rotate.

				//Is the child of parent node par a right or left child?
				bool right = rightChild.top();
				rightChild.pop();

				//Parent par had a right child.
				if(right)
				{
					//Left rotation.
					parent->right = insert->left;
					insert->left = parent;
				}
				//Parent par had a left child.
				else
				{
					

				}
				parent = parents.top();
				parents.pop();
			}

			//Need to check if there is only one parent node (root)
			//and rotate accordingly
			if(insert->priority < parent->priority)
			{
				bool right = rightChild.top();
				rightChild.pop();

				if(right)
				{
					//left rotation with root
					Node<T>* temp = root->right;
					root->right = temp->left;
					temp->left = root;
					root = temp;
				}
				else
				{
					//right rotation with root
					Node<T>* temp = root->left;
					root->left = temp->right;
					temp->right = root;
					root = temp;
				}

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
			//Hey, we found a node that has that value...
			//Is it deleted already?
			if(current->deleted)
				throw TreapException();	//Can't remove something 
										//that's already gone
			else
			{
				current->deleted = true;
				logical--;
			}
		}

	}

	//Automatically call cleanup
	if(physical>100 && (float)logical/physical > .75 )
		cleanup();


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

template <class T>
bool Treap<T>::contains(const T& meat) const
{
	bool ans = (all_traverse(3, meat) ==1 );
	return ans;
	
}

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

template <class T>
void Treap<T>::traverse_preorder(ostream& o, char delim = '\n')
{
	/*
	Code for preorder traversal taken from Data Structures 
	and Algorithms in C++ by Adam Drozdek, Sec 6.4.2 pg 153
	*/

	Node<T> * p = root;
	stack< Node<T> *> meat;
	if(p)  //make sure the tree isn't empty
	{
		meat.push(p);
		while(!meat.empty())
		{
			p = meat.top();
			meat.pop();
			
			//Modified to check if node is del or not.
			if(!p->deleted)
				o << p->meat << delim;
			//End mod

			if(p->right)
				meat.push(p->right);
			if(p->left)
				meat.push(p->left);
		}	
	}

}

template <class T>
void Treap<T>::traverse_postorder(ostream& o, char delim = '\n')
{
	/*
	Code modified from iterative preorder from Data Structures 
	and Algorithms in C++ by Adam Drozdek, Sec 6.4
	*/

	Node <T> *p = root;
	stack< Node<T> *> meat;
	stack< Node<T> *> backwards;

	if(p)
	{
		meat.push(p);
		while(!meat.empty())
		{
			p = meat.top();

			//Push preorder nodes in a stack, then pop out
			//backwards for postorder.
			if(!p->deleted)
				backwards.push(p);

			meat.pop();

			//Want backwards to have [Root, R, L
			//so we first push left onto meat
			//Meat [left, right
			if(p->left)
				meat.push(p->left);
			if(p->right)
				meat.push(p->right);
		}

		//Now, pop backwards out to get postorder.
		while(!backwards.empty())
		{
			o << backwards.top()->meat << delim;
			backwards.pop();
		}
	}

}


template <class T>
void Treap<T>::traverse_inorder(ostream& o, char delim = '\n')
{
	/*
	Code for inorder traversal taken from leetcode.com article 
	http://www.leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
	*/
	
	Node <T> *current = root;
	stack <Node <T>* > meat;

	/*
	Go all the way to the left until you reach a leaf node, 
	keeping track of parents in a stack. Once you reach a node
	with no left children, go to its right child and repeat. 
	*/
	while(current)
	{
		while(!meat.empty() || current)
		{
			if(current)
			{
				meat.push(current);
				current = current->left;
			}
			else
			{
				current = meat.top();
				meat.pop();
				//Modified: Check for deletion
				if(!current->deleted)
					o << current->meat << delim;
				//end mod
				current = current->right;
			}
		}
	}
}

template <class T>
void Treap<T>::traverse_reverseorder(ostream& o, char delim = '\n')
{

	/*
	Code for reverse order traversal modified from leetcode.com article 
	http://www.leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
	*/
	
	Node <T> *current = root;
	stack <Node <T>* > meat;
	//Similar to in order, just switch right and left pointers. 
	//Drive all the way to the right, keeping track of parents in stack.
	//When you get to right most node, pop to go up, go left, and repeat. 
	while(current)
	{
		while(!meat.empty() || current)
		{
			if(current)
			{
				meat.push(current);
				//Modified: Go all the way right
				current = current->right;
			}
			else
			{
				current = meat.top();
				meat.pop();
				//Modified: Check for deletion, go left one
				if(!current->deleted)
					o << current->meat << delim;
				current = current->left;
				//end mod
			}
		}
	}
	
}

template <class T>
T Treap<T>::find_min() const
{
	
	//If called on an empty tree, throws exception
	if(!root)
		throw TreapException();	//shall I assume it will be caught outside?

	/*
	Code for inorder traversal modified from leetcode.com article 
	http://www.leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
	*/

	Node <T> *current = root;
	stack <Node <T>* > meat;


	/*
	In order traversal through the nodes, until a non deleted is found
	-------------------------------------------------------------------
	Go all the way to the left until you reach a leaf node, 
	keeping track of parents in a stack. Once you reach a node
	with no left children, go to its right child and repeat. 
	*/
	while(current)
	{
		while(!meat.empty() || current)
		{
			if(current)
			{
				meat.push(current);
				current = current->left;
			}
			else
			{
				current = meat.top();
				meat.pop();
				//Modified: Check for deletion, return if not deleted
				if(!current->deleted)
					return current->meat;
				//end mod
				current = current->right;
			}
		}
	}

	//If the treap is logically empty, will never return anything.
	throw TreapException();
}


template <class T>
T Treap<T>::find_max() const
{
	
	//If called on an empty tree, throws exception
	if(!root)
		throw TreapException();	//shall I assume it will be caught outside?

	/*
	Code for reverse order traversal modified from leetcode.com article 
	http://www.leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
	*/
	
	Node <T> *current = root;
	stack <Node <T>* > meat;
	
	//Reverse order traversal, first non deleted node is max. 

	//Similar to in order, just switch right and left pointers. 
	//Drive all the way to the right, keeping track of parents in stack.
	//When you get to right most node, pop to go up, go left, and repeat. 
	while(current)
	{
		while(!meat.empty() || current)
		{
			if(current)
			{
				meat.push(current);
				//Modified: Go all the way right
				current = current->right;
			}
			else
			{
				current = meat.top();
				meat.pop();
				//Modified: Check for deletion, go left one
				if(!current->deleted)
					return current->meat;
				current = current->left;
				//end mod
			}
		}
	}
	//If the treap is logically empty, will never return anything.
	throw TreapException();
}

template <class T>
T Treap<T>::remove_min() 
{
	//In order traversal, first non deleted gets marked as deleted.

	//If called on an empty tree, throws exception
	if(!root)
		throw TreapException();	//shall I assume it will be caught outside?


	/*
	Code modified from leetcode.com article 
	http://www.leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
	*/
	
	Node <T> *current = root;
	stack <Node <T>* > meat;

	/*
	Go all the way to the left until you reach a leaf node, 
	keeping track of parents in a stack. Once you reach a node
	with no left children, go to its right child and repeat. 
	*/
	while(current)
	{
		while(!meat.empty() || current)
		{
			if(current)
			{
				meat.push(current);
				current = current->left;
			}
			else
			{
				current = meat.top();
				meat.pop();
				//Modified: If not deleted, delete!!
				if(!current->deleted)
				{
					current->deleted = true;
					logical--;
					return current->meat;
				}
				//end mod
				current = current->right;
			}
		}
	}

	//If the treap is logically empty, will never return anything.
	throw TreapException();
}


template <class T>
T Treap<T>::remove_max() 
{
	//Reverse inorder traversal, first non deleted gets marked as deleted.

	//If called on an empty tree, throws exception
	if(!root)
		throw TreapException();	


	/*
	Code modified from leetcode.com article 
	http://www.leetcode.com/2010/04/binary-search-tree-in-order-traversal.html
	*/
	
	Node <T> *current = root;
	stack <Node <T>* > meat;

	/*
	//Similar to in order, just switch right and left pointers. 
	//Drive all the way to the right, keeping track of parents in stack.
	//When you get to right most node, pop to go up, go left, and repeat. 
	*/
	while(current)
	{
		while(!meat.empty() || current)
		{
			if(current)
			{
				meat.push(current);
				current = current->right;	//modified to right pointer
			}
			else
			{
				current = meat.top();
				meat.pop();
				//Modified: If not deleted, delete!!
				if(!current->deleted)
				{
					logical--;
					current->deleted = true;
					return current->meat;
				}
			
				current = current->left;	//modified to point left
				//end mod	
			}
		}
	}

	//If the treap is logically empty, will never return anything.
	throw TreapException();
}

template <class T>
void Treap<T>::cleanup()
{
	//Traverse the tree. As you traverse, 
	//when you find non deleted nodes, insert em into a new treap.
	
	queue< Node<T>* > slim;
	slim.push(root);

	queue< Node<T>* > newNodes;

	while(!slim.empty())
	{
		Node<T>* current = slim.front();
		slim.pop();
		
		if(!current->deleted)
		{
			//Insert node with same data, and priority.
			Node<T>* shiny = new Node<T>(*current);
			newNodes.push(shiny);
		}

		//Push the children, if any, onto the queue
		if(current->left)
			slim.push(current->left);
		if(current->right)
			slim.push(current->right);
	}

	//Clear the old tree
	delete root; root = NULL;
	physical = 0;
	logical =0;
	//Insert in new nodes.
	while(!newNodes.empty())
	{
		Node<T>* shiny = newNodes.front();
		newNodes.pop();

		insert(shiny->meat, shiny->priority);
	}


}