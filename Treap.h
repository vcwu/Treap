#include <iostream>
using namespace std;


template <class T>
class Treap
{
private:
public:
	Treap() {}
	Treap(Treap t);
	~Treap() {}
	&Treap operator=(const &Treap t);

	void insert(const &T meat);

	//Removes ite, throws TreapException if called on empty treap
	T remove(const &T meat);
	T remove_min();
	T remove_max();
	T find_min() const; //throws treapexception
	T find_max() const; //throws treapexception
	bool contains(const &T meat) const;
	bool empty() const;
	int size() const;
	int deleted() const;
	void cleanup();
	void traverse_preorder(&ostream o, char delim = '\n');
	void traverse_inorder(&ostream o, char delim = '\n');
	void traverse_reverseorder(&ostream o, char delim = '\n');
	void traverse_postorder(&ostream o, char delim = '\n');



}