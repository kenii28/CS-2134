// hw1.cpp : Defines the entry point for the console application.
// Kenneth Huynh
// kh1983
// N18178828
// Data Structures and Algorithms
// Homework 1

#include "stdafx.h"
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;


class timer {
public:
	timer() : start(clock()) {}
	double elapsed() { return (clock() - start) / CLOCKS_PER_SEC; }
	void reset() { start = clock(); }
private:
	double start;
};

void fillVec(vector<int>& intVec, int n){
	for (int i = 0; i < n; i++) {
		int randNum = (rand() % 2001) - 1000;
		intVec.push_back(randNum);
	}
}

int maxSubSum1(const vector<int> & a)
{
	int maxSum = 0;

	for (int i = 0; i < a.size(); ++i)
		for (int j = i; j < a.size(); ++j)
		{
			int thisSum = 0;

			for (int k = i; k <= j; ++k)
				thisSum += a[k];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}

	return maxSum;
}
int maxSubSum2(const vector<int> & a)
{
	int maxSum = 0;

	for (int i = 0; i < a.size(); ++i)
	{
		int thisSum = 0;
		for (int j = i; j < a.size(); ++j)
		{
			thisSum += a[j];

			if (thisSum > maxSum)
				maxSum = thisSum;
		}
	}

	return maxSum;
}
int maxSubSum4(const vector<int> & a)
{
	int maxSum = 0, thisSum = 0;

	for (int j = 0; j < a.size(); ++j)
	{
		thisSum += a[j];

		if (thisSum > maxSum)
			maxSum = thisSum;
		else if (thisSum < 0)
			thisSum = 0;
	}

	return maxSum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	timer t;
	double numClicks;
	double numClicks2;
	double numClicks3;
	vector<int> intVec;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(12);
	
	fillVec(intVec, 256);

	/*t.reset();
	maxSubSum1(intVec);
	numClicks = t.elapsed();
	cout << numClicks << endl;
	
	t.reset();
	maxSubSum2(intVec);
	numClicks2 = t.elapsed();
	cout << numClicks2 << endl;*/

	/*t.reset();
	for (int i = 0; i < 30; i++) {
		maxSubSum4(intVec);
	}
	numClicks3 = t.elapsed();
	cout << numClicks3 << endl;*/

	/*fillVec(intVec, 512);
	t.reset();
	maxSubSum1(intVec);
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	maxSubSum2(intVec);
	numClicks2 = t.elapsed();
	cout << numClicks2 << endl;

	t.reset();
	maxSubSum4(intVec);
	numClicks3 = t.elapsed();
	cout << numClicks3 << endl;*/

	/*fillVec(intVec, 1024);
	t.reset();
	maxSubSum1(intVec);
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	maxSubSum2(intVec);
	numClicks2 = t.elapsed();
	cout << numClicks2 << endl;

	t.reset();
	maxSubSum4(intVec);
	numClicks3 = t.elapsed();
	cout << numClicks3 << endl;*/

	/*fillVec(intVec, 2048);
	t.reset();
	maxSubSum1(intVec);
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	maxSubSum2(intVec);
	numClicks2 = t.elapsed();
	cout << numClicks2 << endl;

	t.reset();
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	numClicks3 = t.elapsed();
	cout << numClicks3 << endl;*/

	/*fillVec(intVec, 4096);
	t.reset();
	maxSubSum1(intVec);
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	maxSubSum2(intVec);
	numClicks2 = t.elapsed();
	cout << numClicks2 << endl;

	t.reset();
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	maxSubSum4(intVec);
	numClicks3 = t.elapsed();
	cout << numClicks3 << endl;*/

	// PART TWO ///////////////////

	/*t.reset();
	int sum = 0;
	for (int i = 0; i < 256; i++)
		++sum;
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 512; i++)
		++sum;
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 1024; i++)
		++sum;
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 2048; i++)
		++sum;
	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 4096; i++)
		++sum;
	numClicks = t.elapsed();
	cout << numClicks << endl;*/


	/*t.reset();
	int sum = 0;
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;	t.reset();
	sum = 0;
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;	t.reset();
	sum = 0;
	for (int i = 0; i < 1024; i++)
		for (int j = 0; j < 1024; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;	t.reset();
	sum = 0;
	for (int i = 0; i < 2048; i++)
		for (int j = 0; j < 2048; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;*/	/*t.reset();
	sum = 0;
	for (int i = 0; i < 4096; i++)
		for (int j = 0; j < 4096; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;*/
	/*t.reset();
	int sum = 0;
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < i; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;	t.reset();
	sum = 0;
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < i; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;	t.reset();
	sum = 0;
	for (int i = 0; i < 1024; i++)
		for (int j = 0; j < i; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;	t.reset();
	sum = 0;
	for (int i = 0; i < 2048; i++)
		for (int j = 0; j < i; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;*/	/*t.reset();
	sum = 0;
	for (int i = 0; i < 4096; i++)
		for (int j = 0; j < i; ++j)
			++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;*/
	t.reset();
	int sum = 0;
	for (int i = 0; i < 256; i++)
		for (int j = 0; j < 256; ++j)
			for (int k = 0; k < 256; ++k)
				++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 512; i++)
		for (int j = 0; j < 512; ++j)
			for (int k = 0; k < 512; ++k)
				++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 1024; i++)
		for (int j = 0; j < 1024; ++j)
			for (int k = 0; k < 1024; ++k)
				++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;

	t.reset();
	sum = 0;
	for (int i = 0; i < 2048; i++)
		for (int j = 0; j < 2048; ++j)
			for (int k = 0; k < 2048; ++k)
				++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;

	/*t.reset();
	int sum = 0;
	for (int i = 0; i < 4096; i++)
		for (int j = 0; j < 4096; ++j)
			for (int k = 0; k < 4096; ++k)
				++sum;	numClicks = t.elapsed();
	cout << numClicks << endl;*/



	return 0;
}

