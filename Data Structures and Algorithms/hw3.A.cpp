/*
Kenneth Huynh
data structures and algorithms
hw3a
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <typename Object>
class Vector
{
public:
	explicit Vector(int initSize = 0)
		: theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY }
	{
		objects = new Object[theCapacity];
	}

	Vector(const Vector & rhs)
		: theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
	{
		objects = new Object[theCapacity];
		for (int k = 0; k < theSize; ++k)
			objects[k] = rhs.objects[k];
	}

	Vector & operator= (const Vector & rhs)
	{
		Vector copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	~Vector()
	{
		delete[] objects;
	}

	Vector(Vector && rhs)
		: theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
	{
		rhs.objects = nullptr;
		rhs.theSize = 0;
		rhs.theCapacity = 0;
	}

	Vector & operator= (Vector && rhs)
	{
		std::swap(theSize, rhs.theSize);
		std::swap(theCapacity, rhs.theCapacity);
		std::swap(objects, rhs.objects);

		return *this;
	}

	bool empty() const
	{
		return size() == 0;
	}
	int size() const
	{
		return theSize;
	}
	int capacity() const
	{
		return theCapacity;
	}

	Object & operator[](int index)
	{
		return objects[index];
	}

	const Object & operator[](int index) const
	{
		return objects[index];
	}

	void resize(int newSize)
	{
		if (newSize > theCapacity)
			reserve(newSize * 2);
		theSize = newSize;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity < theSize)
			return;

		Object *newArray = new Object[newCapacity];
		for (int k = 0; k < theSize; ++k)
			newArray[k] = std::move(objects[k]);

		theCapacity = newCapacity;
		std::swap(objects, newArray);
		delete[] newArray;
	}

	// Stacky stuff
	void push_back(const Object & x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = x;
	}
	// Stacky stuff
	void push_back(Object && x)
	{
		if (theSize == theCapacity)
			reserve(2 * theCapacity + 1);
		objects[theSize++] = std::move(x);
	}


	// Iterator stuff: not bounds checked
	typedef Object * iterator;
	typedef const Object * const_iterator;

	iterator begin()
	{
		return &objects[0];
	}
	const_iterator begin() const
	{
		return &objects[0];
	}
	iterator end()
	{
		return &objects[size()];
	}
	const_iterator end() const
	{
		return &objects[size()];
	}

	static const int SPARE_CAPACITY = 2;

	// I PUT THE ERASE METHOD IN THE CLASS BECAUSE MY CODE DOESNT WORK WHEN IT'S OUTSIDE OF THE CLASS
	iterator erase(iterator vItr) {
		for (; vItr != end() - 1; vItr++) {
			Object* temp = vItr + 1;
			vItr* = *temp;
		}
		theSize -= 1;
		return vItr;
	}

private:
	int theSize;
	int theCapacity;
	Object * objects;
};


template <class Itr, class UnaryPred>
void print_if(Itr start, Itr end, UnaryPred pred) {
	for (; start != end; start++) { // increment
		if (pred(*start)) {			// check. pred is a functor
			cout << *start;
		}
	}
}

class Student {
public:
	Student(const string& who, double grade) : name(who), gpa(grade) {}
	Student(){}
	string getName() const { return name; }
	double getGPA() const { return gpa; }
private:
	string name;
	double gpa;
};

class GPA_in_range{
public:
	GPA_in_range(double low = 3.0, double high = 4.0) : low(low), high(high) {}

	bool operator()(const Student& student) { // operator() overload
		if (low <= student.getGPA() && student.getGPA() <= high) {
			return true;
		}
		else { return false; }
	}
private:
	double low;
	double high;
};

std::ostream& operator<<(std::ostream& os, const Student& student) { // overloading the output operator for the student
	os << student.getName() << endl;
	return os;
}

int main() {
	
	// creating instances of students
	Student student1("cheese", 2.6);
	Student student2("smartcheese", 3.6);
	Student student3("evensmartercheese", 3.9);
	Student student4("milk", 3.0);
	Student student5("cow", 3.5);

	// adding students to the vector
	Vector<Student> studentVec;
	studentVec.push_back(student1);
	studentVec.push_back(student2);
	studentVec.push_back(student3);
	studentVec.push_back(student4);
	studentVec.push_back(student5);

	// creating instance of GPA_in_range
	GPA_in_range gpa;
	// print if student satisfies the functor GPA_in_range
	print_if(studentVec.begin(), studentVec.end(), gpa);

	return 0;
}