/*
Kenneth Huynh
Data Structures and Algorithms
Homework 10 PQ 2
There's stuff from the hw 9 solution
*/

#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

const string DEFAULT_STRING = "cheese";      // must be less than cheese
const int DEFAULT_VAL = -1;
class trainStopData {
public:
	trainStopData(const string& id, const string& name, double lat, double lon)
		: stop_id(id), stop_name(name), stop_lat(lat), stop_lon(lon) {}
	string get_id()         const { return stop_id; }
	string get_stop_name()  const { return stop_name; }
	double get_latitude()   const { return stop_lat; }
	double get_longitude()  const { return stop_lon; }
private:
	string stop_id;
	string stop_name;
	double stop_lat;
	double stop_lon;
};

// Fill up all the keys with the stop_ids from MTA_train_stop_data
void initializeMap(unordered_map < string, list<string> >& adjList) {
	// Open the MTA_train_stop_data.txt file
	ifstream stopFile("MTA_train_stop_data.txt");
	if (!stopFile) {
		cerr << "The file for train stop data cannot be found.\n";
		exit(1);
	}
	// Read the file line-by-line
	string line;
	getline(stopFile, line);

	// Note: I'm going to fill up a vector first, so that I can add adjacencies for stops on the same line
	// You don't have to do it this way, and this may not be the best approach
	vector<string> stops;

	while (getline(stopFile, line)) {
		// Get the stop_id, which is the first element on each line
		stringstream eachLine(line);
		string element;

		// We use comma-delimiting to get the stop_id, which is before the first comma
		// This will store the stop_id into element
		getline(eachLine, element, ',');

		// Get rid of the stops that have 'N' or 'S' after them
		// If you don't do this, it's totally fine, since it won't break the rest of our code

		// Note: I'm going to fill up a vector first, so that I can add adjacencies for stops on the same route
		// You don't have to do it this way, and this may not be the best approach
		if (element[element.size() - 1] != 'N' && element[element.size() - 1] != 'S')
			stops.push_back(element);
	}

	// Sort the vector of stops, so you ensure that all the stops on the same route are listed in order
	sort(stops.begin(), stops.end());

	// At this point, I have a vector that's sorted in order, so the stops on the same line that are one stop away 
	// from each other are listed together, in order.
	for (int i = 0; i < stops.size(); i++) {
		// Create the adjacency list for this stop
		list<string> adj;

		// For the first element, we can't check the element before us, so this is an edge case
		if (i == 0) {
			// Make sure that there's actually a next stop, and that the first character of that stop
			// is the same as the first character of this stop. If so, it's on the same route and we add
			// it to our adjacency list.
			if (stops.size() > 0 && stops[i][0] == stops[i + 1][0]) adj.push_back(stops[i + 1]);

			// For the last element, we can't check the element after us, so this is an edge case
		}
		else if (i == stops.size() - 1) {
			// Make sure that there's more than just one stop, and that the first character of the
			// last stop is the same as the first character of this stop (that means they're on the same route)
			if (stops.size() > 0 && stops[i - 1][0] == stops[i][0]) adj.push_back(stops[i - 1]);

			// Otherwise, check the element both before and after
		}
		else {
			// Add the previous stop if it's on the same route
			if (stops[i - 1][0] == stops[i][0]) adj.push_back(stops[i - 1]);

			// Add the following stop if it's on the same route
			if (stops[i][0] == stops[i + 1][0]) adj.push_back(stops[i + 1]);
		}

		// Insert this stop into the map
		adjList.insert({ stops[i], adj });
	}
	stopFile.close();
}

// Add the transfers to each adjacency list 
void addTransfers(unordered_map < string, list<string> >& adjList) {
	// Open the transfers.txt file
	ifstream transfersFile("transfers.txt");
	if (!transfersFile) {
		cerr << "The file for train stop data cannot be found.\n";
		exit(1);
	}
	// Read the file line-by-line
	string line;
	getline(transfersFile, line);
	while (getline(transfersFile, line)) {
		// Get the first two elements in each line
		stringstream eachLine(line);
		string fromStop;
		string toStop;
		// Get the from_stop_id
		getline(eachLine, fromStop, ',');
		// Get the to_stop_id
		getline(eachLine, toStop, ',');
		// Add the toStop to the adjacency list of the fromStop
		// Make sure that the two are different stops
		if (fromStop != toStop) adjList[fromStop].push_back(toStop);
	}
	transfersFile.close();
}

// This is for testing purposes, to print the adjacency list
void printList(const list<string>& ls) {
	for (list<string>::const_iterator a = ls.begin(); a != ls.end(); a++)
		cout << *a << " ";
	cout << endl;
}

typedef unordered_map< string, list<string> > Graph;  // The graph is given in an adjacency list.
// Vertices are indexed from 0 to V-1
// The indices of the vertices adjacent to vertex i
// are in the list Graph[i].
// Graph can be directed or undirected.

struct vertexInf                    // Stores information for a vertex
{
	int dist;  // distance to vertex from the source
	string prev;  // previous node in BFS tree
};

void printpath(string j, const unordered_map< string, vertexInf > & vinfo)
{
	stack<string> t;

	string current = j;
	while (current != DEFAULT_STRING)
	{
		t.push(current);
		current = vinfo.find(current)->second.prev;
	}
	while (!t.empty())
	{
		cout << t.top() << " ";
		t.pop();
	}
}



// Breadth First Search
// The unweighted shortest path algorithm on the graph g, with vertex i as the source
// Prints the length (number of edges) of the shortest path from the source to every vertex
// in the graph

void shortestpaths(const Graph & g, string s)
{
	queue<string> q;             // q is the queue of vertex numbers

	if (g.find(s) == g.end())
	{
		cout << "Bad index" << endl;
		return;
	}

	unordered_map< string, vertexInf > vertices(g.size());               // stores BFS info for the vertices
	// info for vertex j is in position j

	for (unordered_map<string, list<string>>::const_iterator j = g.begin(); j != g.end(); ++j)                 // Initialize distances and prev values
	{
		vertexInf info;
		info.dist = DEFAULT_VAL;
		info.prev = DEFAULT_STRING;
		vertices.insert({ j->first, info });
	}


	vertices.find(s)->second.dist = 0;

	q.push(s);
	while (!q.empty())
	{
		string v = q.front();
		q.pop();
		for (list<string>::const_iterator w = g.find(v)->second.begin(); w != g.find(v)->second.end(); w++)
		{

			if (vertices[*w].dist == DEFAULT_VAL)          // distance of *w from source not determined yet
			{
				vertices[*w].dist = vertices.find(v)->second.dist + 1;
				vertices[*w].prev = v;
				q.push(*w);
			}
		}
	}
	for (unordered_map<string, vertexInf>::const_iterator j = vertices.begin(); j != vertices.end(); j++)        // print distances from source and paths
	{
		cout << "vertex " << j->first << endl;
		cout << "distance: " << j->second.dist << endl;
		cout << "shortest path: ";
		printpath(j->first, vertices);
		cout << endl;
	}
}

int main() {
	unordered_map < string, list<string> > adjList;
	initializeMap(adjList);
	addTransfers(adjList);

	// Some extra stuff to test that our code works
	/*cout << "125: ";
	printList(adjList.find("125")->second);

	cout << "D19: ";
	printList(adjList.find("D19")->second);

	cout << "635: ";
	printList(adjList.find("635")->second);*/

	shortestpaths(adjList, "125");
}