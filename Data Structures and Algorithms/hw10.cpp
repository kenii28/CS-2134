/*
Kenneth Huynh
Data Structures and Algorithms
Hw10 PQ 1 Only
*/

#include <iostream>
#include <queue>

using namespace std;

template<class Comparable>
void print_kth_largest(const vector<Comparable> & a, int k) {
	if (a.empty()) {
		cout << "Nope, can't be done. Vector is empty." << endl;
	}
	else if (k > a.size()) {
		cout << "Why is k greater than the size of the vector?" << endl;
	}
	else {
		priority_queue<Comparable> pq(a.begin(), a.end());
		while (k > 0) {
			cout << pq.top() << " ";
			pq.pop();
			k -= 1;
		}
	}
}

int main() {

	vector<int> p;
	p.push_back(5);
	p.push_back(4);
	p.push_back(5);
	p.push_back(3);
	p.push_back(2);
	p.push_back(1);

	print_kth_largest(p, 2);
	print_kth_largest(p, 22);
	print_kth_largest(p, 2);

	return 0;
}