/*
Kenneth Huynh
Data Structures and Algorithms
hw3b
*/

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class TrainStopData {
public:
	TrainStopData(string id, string name, double lat, double lon) : stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {} // constructor

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


int main() {

	// vector<int> A { 1, 2, 1, 4 };
	// vector<int> B { 1, 2, 1, 3, 4, 5, 1, 2, 3, 1, 2, 1, 3, 1, 2, 3, 1, 3 };
	// cout << count(B.begin(), B.end(), 1);
	// cout << equal(A.begin(), A.begin() + 3, B.begin());


	ifstream ifs("mtastopdata.txt"); // renamed
	if (!ifs) { // check if such a file exists
		cout << "The file doesn't exist.";
		exit(1);
	}
	else {
		
		 vector<TrainStopData> vecTrainData;

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

			TrainStopData oneTrainData(id, name, latd, lond);
			vecTrainData.push_back(oneTrainData);
		}

		for (int i = 0; i < vecTrainData.size(); i++) {
			cout << vecTrainData[i].get_id() << ", " << vecTrainData[i].get_stop_name() << ", "
				<< vecTrainData[i].get_latitude() << ", " << vecTrainData[i].get_longitude() << endl;
		}
	}
	return 0;
}