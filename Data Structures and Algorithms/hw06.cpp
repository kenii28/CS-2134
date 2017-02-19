/*
Kenneth Huynh
Data Structures and Algorithms
hw06
*/
  

#include <iostream>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

template <typename Object>
class List
{
private:

	struct Node
	{
		Object  data;
		Node   *next;

		Node(const Object & d = Object{}, Node * n = nullptr)
			: data( d ), next( n ) { }

		Node(Object && d, Node * n = nullptr)
			: data{ std::move(d) }, next{ n } { }
	};

public:
	class iterator
	{
	public:

		iterator() : current(nullptr)
		{ }

		Object & operator* ()
		{
			return current->data;
		}

		const Object & operator* () const
		{
			return  current->data;
		}

		iterator & operator++ ()
		{
			this->current = this->current->next;
			return *this;
		}

		iterator operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		bool operator== (const iterator & rhs) const
		{
			return current == rhs.current;
		}

		bool operator!= (const iterator & rhs) const
		{
			return !(*this == rhs);
		}

	private:
		Node * current;

		iterator(Node *p) : current{ p }
		{ }

		friend class List<Object>;
	};

public:
	List()
	{
		header = new Node;
	}

	~List()
	{
		clear();
		delete header;
	}

	List(const List & rhs) {
		header = new Node;
		Node* tmp1 = header;
		Node* tmp2 = rhs.header->next;
		while (tmp2 != nullptr){
			tmp1->next = new Node(tmp2->data);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}

	List & operator= (const List & rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	List(List && rhs) :header{ new Node }
	{
		header->next = rhs.header->next;
		rhs.header->next = nullptr;
	}

	List & operator= (List && rhs)
	{
		std::swap(header, rhs.header);
		return *this;
	}

	iterator begin() const
	{
		return iterator(header->next);
	}

	iterator end() const
	{
		return iterator(nullptr);
	}

	iterator before_begin() const
	{
		return iterator(header);
	}

	bool empty() const
	{
		return header->next == nullptr;
	}

	void clear()
	{
		while (!empty())
			pop_front();
	}

	void pop_front()
	{
		erase_after(before_begin());
	}

	iterator insert_after(iterator itr, const Object & x)
	{
		Node *p = itr.current;
		p->next = new Node{ x, p->next };

		return iterator(p->next);
	}

	void remove(const Object & x)
	{
		Node * prev = header;

		while (prev->next != nullptr)
		{
			if (prev->next->data == x)
				erase_after(iterator(prev));
			else
				prev = prev->next;
		}
	}

	iterator erase_after(iterator itr)
	{
		Node *p = itr.current;
		Node *oldNode = p->next;

		p->next = oldNode->next;
		delete oldNode;

		return iterator(p->next);
	}

	Object & front() {
		return (header->next->data);
	}

	const Object & front() const {
		return (header->next->data);
	}

	void merge(List & alist) {
		Node* tmp1 = header->next;
		Node* tmp2 = alist.header->next;
		List result;
		Node* tmp3 = result.header;
		
		while (tmp1 != nullptr && tmp2 != nullptr) {
			if ((tmp1->data <= tmp2->data)) {
				result.insert_after(iterator(tmp3), tmp1->data);
				tmp1 = tmp1->next;
				tmp3 = tmp3->next;

			}
			else { // (tmp1->data > tmp2->data)
				result.insert_after(iterator(tmp3), tmp2->data);
				tmp2 = tmp2->next;
				tmp3 = tmp3->next;
			}
		}
		// debugging stuff
		/*iterator it = result.begin();
		while (it != result.end()) {
			cout << (*it) << endl;
			it++;
		}*/
		while (tmp1 != nullptr) {
			result.insert_after(iterator(tmp3), tmp1->data);
			tmp1 = tmp1->next;
			tmp3 = tmp3->next;
		}
		while (tmp2 != nullptr) {
			result.insert_after(iterator(tmp3), tmp2->data);
			tmp2 = tmp2->next;
			tmp3 = tmp3->next;
		}
		alist.clear();
		std::swap(*this, result);

	}
	
	void remove_adjacent_duplicates() {
		Node* tmp = header->next;
		Node* tmp2 = header->next->next;
		while (tmp2 != nullptr) {
			while (tmp->data == tmp2->data) {
				erase_after(iterator(tmp));
			}
			tmp = tmp->next;
			tmp2 = tmp->next;
		}

	}

	void reverse();


	template<class Predicate>
	void remove_if(Predicate pred) {
		Node* tmp = header;
		while (tmp->next != nullptr) {
			if (pred(tmp->next->data)) {
				erase_after(iterator(tmp));
			}
			tmp = tmp->next;
		}
	}

	iterator insert_after(iterator itr, Object && x) {
		Node *p = itr.current;
		p->next = new Node( std::move(x), p->next );

		return iterator(p->next);
	}

private:
	Node *header;

};

template <typename Object>
class Queue{
private:
	
	struct Node
	{
		Object  data;
		Node   *next;

		Node(const Object & d = Object{}, Node * n = nullptr)
			: data( d ), next( n ) { }

		Node(Object && d, Node * n = nullptr)
			: data{ std::move(d) }, next{ n } { }
	};
public:
	class iterator
	{
	public:

		iterator() : current(nullptr)
		{ }

		Object & operator* ()
		{
			return current->data;
		}

		const Object & operator* () const
		{
			return  current->data;
		}

		iterator & operator++ ()
		{
			this->current = this->current->next;
			return *this;
		}

		iterator operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		bool operator== (const iterator & rhs) const
		{
			return current == rhs.current;
		}

		bool operator!= (const iterator & rhs) const
		{
			return !(*this == rhs);
		}

	private:
		Node * current;

		iterator(Node *p) : current{ p }
		{ }

		friend class Queue<Object>;
	};

public:
	Queue()
	{
		header = nullptr;
	}

	~Queue()
	{
		empty();
	}

	Queue & operator= (const Queue & rhs)
	{
		List copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	Queue & operator= (Queue && rhs)
	{
		std::swap(header, rhs.header);
		return *this;
	}

	iterator begin() const
	{
		return iterator(header);
	}

	iterator end() const
	{
		return iterator(nullptr);
	}

	bool isEmpty() const
	{
		return header == nullptr;
	}

	void empty()
	{
		while (!isEmpty())
			dequeue();
	}

	void dequeue()
	{
		if (header != nullptr) {
			Node* second = header->next;
			delete header;
			header = second;
		}
	}

	Object front() {
		return header->data;
	}

	Node* findLast() {
		Node* p = header;
		if (p != nullptr) {
			while (p->next != nullptr)
				p = p->next;
		}
		return p;
	}

	Object back() {
		Node* p = findLast();
		return p->data;
	}

	void insertHead(const Object& entry) {
		Node* temp = new Node;
		temp->data = entry;
		temp->next = header;
		header = temp;
	}

	void enqueue(const Object& x) {
		if (header == nullptr) {
			insertHead(x);
		}
		else {
			Node* p = findLast();
			insert_after(iterator(p), x);
		}
	}

	iterator insert_after(iterator itr, const Object & x)
	{
		Node *p = itr.current;
		p->next = new Node{ x, p->next };

		return iterator(p->next);
	}

	void remove(const Object & x)
	{
		Node * prev = header;

		while (prev->next != nullptr)
		{
			if (prev->next->data == x)
				erase_after(iterator(prev));
			else
				prev = prev->next;
		}
	}

	iterator erase_after(iterator itr)
	{
		Node *p = itr.current;
		Node *oldNode = p->next;

		p->next = oldNode->next;
		delete oldNode;

		return iterator(p->next);
	}

	private:
		Node* header;
};

int main() {
	List<int> first;
	// List<int> second;
	List<int>::iterator it = first.before_begin();
	// List<int>::iterator it2 = second.before_begin();
	int a = 1;
	int b = 3;
	int c = 5;
	it = first.insert_after(it, a);
	it = first.insert_after(it, b);
	it = first.insert_after(it, c);
	
	List<int> second = first;
	/*int d = 2;
	int e = 4;
	int f = 6;
	it2 = second.insert_after(it2, d);
	it2 = second.insert_after(it2, e);
	it2 = second.insert_after(it2, f);
	it2 = second.begin();*/

	first.merge(second);
	it = first.begin();
	List<int>::iterator it2 = second.before_begin();
	// cout << first.front() << endl;
	/////remove duplicats test
	/*List<char> first;
	List<char>::iterator it = first.before_begin();

	char a = 'a';
	char b = 'a';
	char c = 'b';
	char d = 'b';
	char e = 'c';
	char f = 'c';
	char g = 'd';
	it = first.insert_after(it, a);
	it = first.insert_after(it, b);
	it = first.insert_after(it, c);
	it = first.insert_after(it, d);
	it = first.insert_after(it, e);
	it = first.insert_after(it, f);
	it = first.insert_after(it, g);*/
	///////////

	/*int d = 2;
	int e = 2;
	int f = 3;
	int g = 4;
	it2 = second.insert_after(it2, d);
	it2 = second.insert_after(it2, e);
	it2 = second.insert_after(it2, f);
	it2 = second.insert_after(it2, g);*/

	// first.remove_adjacent_duplicates();
	// it = first.begin();
	// second.remove_adjacent_duplicates();

	while (it != first.end()) {
		cout << (*it) << endl;
		it++;
	}

	while (it2 != second.end()) {
		cout << (*it2) << endl;
		it2++;
	}
	//////////////////////////////////////
	///////////////////	Queue stuff /////////////
	/*Queue<string> first;
	Queue<string>::iterator it;

	string a = "angela";
	string b = "kenneth";
	string c = "celina";

	first.enqueue(a);
	first.enqueue(b);
	first.enqueue(c);
	first.dequeue();

	
	it = first.begin();*/

	/*while (it != first.end()) {
		cout << (*it) << endl;
		it++;
	}

	string d = first.front();
	string e = first.back();
	cout << "First in line is: " << d << endl;
	cout << "Last in line is: " << e << endl;

	first.empty();*/

	///////////////////////////////////////////////////
}
