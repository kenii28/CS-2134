/*
Kenneth Huynh
Data Structures and Algorithms
hw04
*/

#define _USE_MATH_DEFINES
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <functional>

using namespace std;

class trainStopData {
public:
	trainStopData(string id, string name, double lat, double lon) : stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {} // constructor

	string get_id() const { return stop_id; }
	string get_stop_name() const { return stop_name; }
	double get_latitude() const { return stop_lat; }
	double get_longitude() const { return stop_lon; }

private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_lon;
};

class isStopOnRoute{
	char route;
public:
	isStopOnRoute(char route) : route(route) {}
	bool operator()(const trainStopData& train) {
		char routeID = (train.get_id()).at(0);
		return (routeID == route);
	}
};

class isSubwayStop{
	string stopId;
public:
	isSubwayStop(string id) : stopId(id) {}
	bool operator()(const trainStopData& train) {
		return (train.get_id() == stopId);
	}
};

double degrad(double d) {
	return d * M_PI / 180;
}


double haverdist(double lat1, double longit1, double lat2, double longit2)
{
	double r = 6371;
	double dlat = degrad(lat2 - lat1);
	double dlongit = degrad(longit2 - longit1);
	double a = sin(dlat / 2)*sin(dlat / 2) +
		cos(degrad(lat1))*cos(degrad(lat2))*sin(dlongit / 2)*sin(dlongit / 2);
	double c = 2 * atan2(sqrt(a), sqrt(1 - a));
	return r*c;
}

class isSubwayStopNearX{
	double longitude;
	double latitude;
	double d; // haha double d 
public:
	isSubwayStopNearX(double lon, double lat, double distance) : longitude(lon), latitude(lat), d(distance) {}
	bool operator()(const trainStopData& train) {
		double distance = haverdist(latitude, longitude, train.get_latitude(), train.get_longitude());
		return (distance <= d);
	}
};

class printTrainStopInfo{
public:
	void operator()(const trainStopData& train) {
		cout << train.get_id() << ", " << train.get_stop_name() << ", "
			<< train.get_latitude() << ", " << train.get_longitude() << endl;
	}
};

template <class itrStart, class itrEnd, class predi, class op>
int perform_if(itrStart first, itrEnd last, predi pred, op op) {
	int count = 0;
	for (; first != last; first++) {
		if (pred(*first)) {
			op(*first);
			count++;
		}
	}
	return count;

}

template <class trainVecItr>
void menu(trainVecItr first, trainVecItr last) {
	while (1) {
		cout << "Hi, welcome to this train kiosk.\nEnter 1 for information about all the train stops on a specific route.\nEnter 2 for information about a specific train stop.\nEnter 3 for all the train stops within a certain distance.\nEnter anything else to quit." << endl;
		string input;
		cin >> input;
		if (input == "1") {
			cout << "Please enter the specific route." << endl;
			char r;
			cin >> r;
			int runs = perform_if(first, last, isStopOnRoute(r), printTrainStopInfo());
			if (runs == 0) { cout << "Sorry there are no trains on that route.\n"; }
		}
		else if (input == "2") {
			cout << "Please enter the train stop's ID number." << endl;
			string trainID;
			cin >> trainID; 
			int runs = perform_if(first, last, isSubwayStop(trainID), printTrainStopInfo());
			if (runs == 0) { cout << "Sorry, no train stops were found with that ID.\n"; }
		}
		else if (input == "3") {
			double lat, lon, dis;
			cout << "Please enter your latitude." << endl;
			cin >> lat;
			cout << "Please enter your longitude." << endl;
			cin >> lon;
			cout << "Please enter the furthest distance you would like to travel." << endl;
			cin >> dis;
			int runs = perform_if(first, last, isSubwayStopNearX(lon, lat, dis), printTrainStopInfo());
			if (runs == 0) { cout << "Sorry no train stops were found near your location. Go get a cab.\n"; }
		}
		else {
			break;
		}
	}
}

////// QUESTION 2 ///////
//int GCD(int a, int b) {
//	if (b == 0) { return a; }
//	else if (a < b) { GCD(b, a); }
//	else {
//		GCD(b, a % b);
//	}
//}
///////////////////////
//
//////////////QUESTION 3//////
//typedef vector<int>::const_iterator itr;
//int actualSumVec(const vector<int>& a, itr left, itr right) {
//	if (left >= right) {
//		return *left;
//	}
//
//	itr center = ((right - left) / 2) + left;
//	int leftSum = actualSumVec(a, left, center);
//	int rightSum = actualSumVec(a, center + 1, right - 1);
//
//	return leftSum + rightSum;
//
//}
//
//int sumVector(const vector<int>& a) {
//	if (a.size() == 1) { return a[0]; }
//	return actualSumVec(a, a.begin(), a.end());
//}
////////////////////////////




int main() {

	// Question 2 TEST
	// cout << GCD(6, 15);
	/////////////////////

	// Question 3 TEST 
	// vector<int> a{ 1, 2, 3, -3, -2};
	// cout << sumVector(a) << endl;
	///////////////////

	ifstream ifs("mtastopdata.txt"); // renamed
	if (!ifs) { // check if such a file exists
		cout << "The file doesn't exist.";
		exit(1);
	}
	else {
		vector<trainStopData> vecTrainData;

		string line;
		string crap, id, name, lat, lon; // do it outside so you dont have to keep making new instances inside the loop
		double latd, lond;

		getline(ifs, line); // doesnt use the first line
		while (getline(ifs, line)) {
			stringstream lineString(line);
			getline(lineString, id, ',');
			getline(lineString, crap, ',');
			getline(lineString, name, ',');
			getline(lineString, crap, ',');
			getline(lineString, lat, ',');
			getline(lineString, lon, ',');

			latd = atof(lat.c_str());
			lond = atof(lon.c_str());

			trainStopData oneTrainData(id, name, latd, lond);
			vecTrainData.push_back(oneTrainData);
		}

		menu(vecTrainData.begin(), vecTrainData.end());
		return 0;
	}
}