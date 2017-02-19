/*
Kenneth Huynh
Data Structures and Algorithms
Hw08
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <string>
#include <queue>
using namespace std;

template<class Comparable>
struct BinaryNode
{
	Comparable element;
	BinaryNode *left;
	BinaryNode *right;

	BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt)
		: element{ theElement }, left{ lt }, right{ rt }{ }

	BinaryNode(Comparable && theElement, BinaryNode *lt, BinaryNode *rt)
		: element{ std::move(theElement) }, left{ lt }, right{ rt } { }
};


// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// bool contains( x )     --> Return true if x is present
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************


template <typename Comparable>
class BinarySearchTree
{
public:
	typedef BinaryNode<Comparable> Node;

	BinarySearchTree() : root{ nullptr }
	{
	}

	/**
	* Copy constructor
	*/
	BinarySearchTree(const BinarySearchTree & rhs) : root{ nullptr }
	{
		root = clone(rhs.root);
	}

	/**
	* Move constructor
	*/
	BinarySearchTree(BinarySearchTree && rhs) : root{ rhs.root }
	{
		rhs.root = nullptr;
	}

	/**
	* Destructor for the tree
	*/
	~BinarySearchTree()
	{
		makeEmpty();
	}

	/**
	* Copy assignment
	*/
	BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		BinarySearchTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/**
	* Move assignment
	*/
	BinarySearchTree & operator=(BinarySearchTree && rhs)
	{
		std::swap(root, rhs.root);
		return *this;
	}


	/**
	* Returns true if x is found in the tree.
	*/
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == nullptr;
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(const Comparable & x)
	{
		insert(x, root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable && x)
	{
		insert(std::move(x), root);
	}

	void inRange(const Comparable& low, const Comparable& high) {
		inRange(low, high, root);
	}

	double average_node_depth() {
		double sum = sumDepths();
		int n = treeSize(root);
		return sum / n;
	}

	void printLevelOrder() {
		if (root == nullptr) { return; }
		queue<BinaryNode<Comparable>*> q;
		BinaryNode<Comparable>* temp = root;
		q.push(temp);
		while (!(q.empty())) {
			temp = q.front();
			q.pop();
			cout << temp->element << " ";
			if (temp->left != nullptr) {
				q.push(temp->left);
			}
			if (temp->right != nullptr) {
				q.push(temp->right);
			}
		}
	}

	void stringy() {
		stringy(root->left);
		stringy(root->right);
	}
	
private:

	BinaryNode<Comparable> *root;

	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const Comparable & x, Node * & t)
	{
		if (t == nullptr)
			t = new Node{ x, nullptr, nullptr };
		else if (x < t->element)
			insert(x, t->left);
		else if (t->element < x)
			insert(x, t->right);
		else
			;  // Duplicate; do nothing
	}

	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(Comparable && x, Node * & t)
	{
		if (t == nullptr)
			t = new Node{ std::move(x), nullptr, nullptr };
		else if (x < t->element)
			insert(std::move(x), t->left);
		else if (t->element < x)
			insert(std::move(x), t->right);
		else
			;  // Duplicate; do nothing

	}

	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(Node * & t)
	{
		if (t != nullptr)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}


	/**
	* Internal method to clone subtree.
	*/
	Node * clone(Node *t) const
	{
		if (t == nullptr)
			return nullptr;
		else
			return new Node{ t->element, clone(t->left), clone(t->right) };
	}

	bool contains(const Comparable& x, const BinaryNode<Comparable>*& root) {
		if (root != nullptr) {
			if (x < root->element) { return contains(x, root->left); }
			else if (root->element < x) { return contains(x, root->right); }
			else { return true; } // x == element
		}
		else { // not found
			return false;
		}
	}

	void inRange(const Comparable& low, const Comparable& high, BinaryNode<Comparable>*& root) {
		if (root != nullptr) {
			if (low <= root->element && root->element <= high) { 
				cout << root->element << " "; 
				inRange(low, high, root->left);
				inRange(low, high, root->right);
			}
			else if (root->element < low) {
				inRange(low, high, root->right);
			}
			else if (root->element > high) {
				inRange(low, high, root->left);
			}
			
		}
	}

	double sumDepths(double d = 0) {
		BinaryNode<Comparable>* temp = root;
		if (temp == nullptr) { return 0; }
		else {
			double left = d;
			double right = d;
			temp = temp->left;
			double leftSum = sumDepths(++left);
			temp = temp->right;
			double rightSum = sumDepths(++right);
			return d + leftSum + rightSum;
		}
	}

	int treeSize(BinaryNode<Comparable>* root) {
		BinaryNode<Comparable>* t = root;
		if (t == nullptr) {
			return 0;		
		}
		else {
			return 1 + treeSize(t->left) + treeSize(t->right);
		}
	}

	BinaryNode<Comparable>* rRotate(BinaryNode<Comparable>* root) {
		BinaryNode<Comparable>* temp;
		temp = root->right;
		root->right = temp->left;
		temp->left = root;
		return temp;
	}

	void stringy(BinaryNode<Comparable>* root) {
		/*if (root != nullptr) {
		if (root->left != nullptr) {
		stringy(root->left);
		}
		else if (root->right != nullptr) {
		stringy(root->right);
		}
		}*/
		if (root != nullptr) {
			BinaryNode<Comparable>* leftSide = root->left;
			BinaryNode<Comparable>* temp = root;
			BinaryNode<Comparable>* rightSide = root->right;
			while (rightSide->left != nullptr)  {
				rightSide = rightSide->right;
			}
			root->left = leftSide;
			rightSide->right = temp;
		}
	}
};


int main() {
	////////// PQ 1 ////////////////
	//ifstream ifs("Letter_point_value.txt");
	//if (!ifs) { // check if such a file exists
	//	cout << "The file doesn't exist.";
	//	exit(1);
	//}
	//vector<int> val(26);
	//char x;
	//int y;
	//while (ifs >> y >> x) {
	//	val[x - 65] = y;
	//}
	//// for (int x : val) {
	//// 	 cout << x << endl;
	//// }

	//ifstream ifs2("ENABLE.txt");
	//if (!ifs2) { // check if such a file exists
	//	cout << "The file doesn't exist.";
	//	exit(1);
	//}
	//map<string, int> mappy;
	//string line;
	//while (getline(ifs2, line)) {
	//	int p = 0;
	//	for (char z : line) {
	//		if (z - 97 >= 0) { //  ignore spaces
	//			p += val[z - 97];
	//		}
	//	}
	//	mappy.insert({ line, p });
	//}
	//cout << mappy.find("feh")->second << endl;
	///// END PQ 1 ////////////////////////////

	BinarySearchTree<int> a;
	a.insert(7);
	a.insert(8);
	a.insert(3);
	a.insert(5);
	a.insert(4);
	a.insert(6);

	// a.stringy(); // doesn't work
	// a.inRange(2, 3);
	// cout << a.average_node_depth(); // gives some weird error but should work
	a.printLevelOrder();


	return 0;
}