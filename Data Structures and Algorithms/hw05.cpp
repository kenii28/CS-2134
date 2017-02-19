/*
Kenneth Huynh
Data Structures and Algorithms
hw05
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class student {
public:
	student(const string& who, double grade) : name(who), gpa(grade) {}
	string getName() const { return name; }
	double getGPA() const { return gpa; }
	
private:
	string name;
	double gpa;
};

std::ostream& operator<<(std::ostream& os, const student& student) { // overloading the output operator for the student
	os << student.getName() << endl;
	return os;
}

class meFirst {
	string me;
public:
	meFirst(string name) : me(name) {}

	bool operator()(const student& first, const student& second) {
		if (first.getName() == me) { return true; }
		else if (second.getName() == me) { return false; }
		return (first.getName() < second.getName()) ? true : false;
	}
};

template<class Comparable>
void printVec(vector<Comparable>& a) {
	for (int i = 0; i < a.size(); i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}


template <class comp>
void sortBool(vector<comp>& a) {
	int i, j;
	int pivot = 1;
	for (i = 0, j = a.size() - 1;;)
	{
		while (a[i] < pivot) ++i;
		while (j > i && pivot <= a[j]) --j;
		if (i < j)
			swap(a[i++], a[j--]);
		else
			break;
	}
}

template <class itr>
void mergeSort(itr tmpArray, itr left, itr right)
{
	if (left == right - 1) { return; }
	else {
		itr center =  ((right - left)/ 2) + left;
		mergeSort(tmpArray, left, center);
		mergeSort(tmpArray, center, right);
		merge(left, center, center, right, tmpArray);
	}
	
	for (; left != right; left++) {
		*left = *tmpArray;
		tmpArray++;
	}
}

template <class RandItr>
void mergeSort(RandItr start, RandItr end)
{
	int sz = end - start; // or use auto sz = end-start;
	typedef typename iterator_traits< RandItr >::value_type Object; //Xcode
	// typedef iterator_traits< RandItr >::value_type Object; //Other compilers
	// Don’t worry about this line of code
	vector<Object> tmp(sz);
	mergeSort(tmp.begin(), start, end);
}

void myRecFunc1(int n)
{
	if (n < 1) return;
	cout << n << ", ";
	myRecFunc1(n / 2);
	cout << n << ", ";
}

void myRecFunc2(int n)
{
	if (n < 1) return;
	cout << n << ", ";
	myRecFunc2(n / 2);
	cout << n << ", ";
	myRecFunc2(n / 2);
}

void quickSort(vector<int> & a, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2; // select pivot to be element in middle position
		int pivot = a[mid];
		swap(a[high], a[mid]); // put pivot in a[high]
		// Begin partitioning
		int i, j;
		for (i = low, j = high - 1;;)
		{
			while (a[i] < pivot) ++i;
			while (j > i && pivot < a[j]) --j;
			if (i < j)
				swap(a[i++], a[j--]);
			else
				break;
		}
		swap(a[i], a[high]); // Restore pivot
		printVec(a); // prints the contents of the vector in order
		quickSort(a, low, i - 1); // Sort small elements
		quickSort(a, i + 1, high); // Sort large elements
	}
}



int main(){
	////////////Question 1 Test/////////
	vector<int> a = { 11, 10, 1, 3, 2, 5 };
	printVec(a);
	vector<int> tmp(a.size());
	//// insertionSort(a);
	mergeSort(a.begin(), a.end());
	printVec(a);
	// quickSort(a, 0, a.size() - 1); test for written part
	////////////////////////
	///////Question 2 Test/////////
	/*vector<student> stud;
	student a("a", 0);
	student b("b", 0);
	student c("c", 0);
	student z("z", 0);
	stud.push_back(c);
	stud.push_back(b);
	stud.push_back(a);
	stud.push_back(z);
	printVec(stud);
	sort(stud.begin(), stud.end(), meFirst("c"));
	printVec(stud);*/
	///////////////////////////
	///////Question 3 Test/////////////
	/*vector<bool> boo = { false, true, false, false, true, true, false, false, true };
	printVec(boo);
	sortBool(boo);
	printVec(boo);

	vector<bool> boo1 = { false, false, true, false, true, true, false, false, true, false };
	printVec(boo1);
	sortBool(boo1);
	printVec(boo1);

	vector<bool> boo2 = { true, true, true, true, false, false, false };
	printVec(boo2);
	sortBool(boo2);
	printVec(boo2);*/

	// vector<int> tmp(a.size());
	// mergeSort(a, tmp, 0, a.size() - 1);

	// myRecFunc2(4);
}