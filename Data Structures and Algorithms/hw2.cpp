/* 
Kenneth Huynh
Data Structures and Algorithms
hw2.cpp 

*/

#include "stdafx.h"
#include <algorithm>

using namespace std;

class IntArray{
public:
	IntArray(int n = 0) : size(n), array(new int[n]){}
	IntArray(const IntArray& rhs);
	IntArray(IntArray&& rhs);
	IntArray& operator=(IntArray&& rhs){
		if (this != &rhs){
			swap(array, rhs.array); // create a temp array. take the resources of rhs for the new array. make rhs array = temp
			// int* temp(array);
			// array = rhs.array;
			// rhs.array = temp;
			swap(size, rhs.size);
			return *this;
		}
	}


	~IntArray();
	void put(int i, int value);
	int get(int i);
private:
	int * array;
	int size;
};

IntArray::IntArray(const IntArray& rhs) {
	size = rhs.size;
	array = new int[size];
	for (int i = 0; i < size; i++) {
		array[i] = rhs.array[i];
	}
}

IntArray::IntArray(IntArray&& rhs) : array(rhs.array), size(rhs.size) {
	rhs.array = nullptr;
}


IntArray::~IntArray() {
	delete[] array;
}



int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

