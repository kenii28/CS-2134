/*
Kenneth Huynh
Data Structures and Algorithms
Hw09
*/

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <list>
#include <sstream>

using namespace std;

template< class HashedObj >
class HashTable
{
public:
	explicit HashTable(int size = 101) :currentSize(0){ array.resize(size); }
	std::hash<HashedObj> hf; // create a hash function object
	bool find(const HashedObj & x) const {
		size_t i = hf(x) % array.size();
		if (array[i].info == EMPTY) {
			return false;
		}
		else {
			for (size_t j = i; j < array.size(); j++) {
				if (array[j].info == EMPTY) {
					return false;
				}
				if (array[j].element == x) {
					return true;
				}
			}
			for (size_t j = 0; j < i; j++) {
				if (array[j].info == EMPTY) {
					return false;
				}
				if (array[j].element == x) {
					return true;
				}
			}
		}
	}
	void makeEmpty() {
		for (size_t i = 0; i < array.size(); i++) {
			array[i].info = EMPTY;
		}
	}
	bool insert(const HashedObj & x) {
		if (++currentSize >= array.size() * 0.5){
			rehash();
		}
		size_t i = hf(x) % array.size();
		if (find(x)) { return false; }
		else {
			for (size_t k = i; k < array.size(); k++) {
				if (array[k].info == EMPTY || array[k].info == DELETED) {
					array[k].element = x;
					array[k].info = ACTIVE;
					return true;
				}
			}
			for (size_t j = 0; j < i; j++) {
				if (array[j].info == EMPTY || array[j].info == DELETED) {
					array[j].element = x;
					array[j].info = ACTIVE;
					return true;
				}
			}
		}
	}
	bool remove(const HashedObj & x);
	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj & e = HashedObj(), EntryType i = EMPTY)
			: element(e), info(i) {}
	};
	vector<HashEntry> array;
	int currentSize;
	void rehash() {
		vector<HashEntry> oldArray = array;
		makeEmpty();
		for (size_t i = 0; i < oldArray.size(); i++) {
			if (oldArray[i].info == ACTIVE) {
				insert(oldArray[i].element);
			}
		}

	}
};



int main() {
	ifstream ifs("adjstops.txt"); // renamed
	if (!ifs) { // check if such a file exists
		cout << "The file doesn't exist.";
		exit(1);
	}
	else {
		unordered_map<string, list<string>> adj;
		string line;
		string crap, stop1, stop2, nextadj;
		char next, second, third;

		getline(ifs, line); // doesnt use the first line
		while (getline(ifs, line)) {
			list<string> s;
			stringstream lineString(line);
			getline(lineString, stop1, ',');
			getline(lineString, stop2, ',');
			getline(lineString, crap, ',');
			getline(lineString, crap, ',');
			if (adj.find(stop1) != adj.end()) {
				adj.insert({ stop1, s });
			}
			if (stop1 != stop2) {
				adj[stop1].push_back(stop2);
			}
			next = ifs.get();
			if (stop1[0] == next) {
				second = ifs.get();
				third = ifs.get();
				nextadj = string() + next + second + third;
				adj[stop1].push_back(nextadj);
				ifs.putback(third);
				ifs.putback(second);
				ifs.putback(next);
			}
			else { ifs.putback(next); }
		}
		ifs.close();
		/// TRIED TO CHECK EACH ELEMENT OF THE LIST IN THE MAP TO SEE IF IT HAS THE CURRENT DATA IN ITS LIST
		/*ifstream ifs("adjstops.txt");
		string stops, trash;
		getline(ifs, line);
		while (getline(ifs, line)) {
			list<string> s;
			stringstream lineString(line);
			getline(lineString, stops, ',');
			getline(lineString, trash, ',');
			getline(lineString, trash, ',');
			getline(lineString, trash, ',');
			for (auto i = adj[stops].begin(); i != adj[stops].end(); i++) {
				string j = i->data;
				for (auto k = adj[j].begin(); k != adj[j].end(); k++) {
					if (k->data == i->data) {}

				}
			}
		}*/
	}
	
	return 0;
}