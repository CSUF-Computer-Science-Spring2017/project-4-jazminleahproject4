#include <fstream>
#include <iostream>
#include <sstream>  // for std::istringstream
#include "Graph.h"

// TO DO
// initialize an undirected graph that can store at most n vertices
Graph::Graph(int n) {
	this->n = n;
	adjacencyMatrix = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		adjacencyMatrix[i] = new bool[n];
		intToLabels[i] = "needs Label"; // isn't labeled
		for (int j = 0; j < n; j++)
			adjacencyMatrix[i][j] = false;
	}

	//need to initialize maps!!!!! and use in addLabel

}

// TO DO
// return the maximum number of vertices
int Graph::size() {
	return n;
}
Graph::~Graph()
{
	for (int i = 0; i < n; i++)
		delete[]adjacencyMatrix[i];
	delete[] adjacencyMatrix;
	
}

// TO DO
// give a string label to vertex
void Graph::addLabel(Vertex i, string s) {

	intToLabels[i] = s;

	//populate labels to int map
	labelsToInt[s] = i;

}

// TO DO
// add an edge between vertices i and j
void Graph::addEdge(Vertex i, Vertex j) {
	if (i >= 0 && i < n && j >= 0 && j < n)
	{
		adjacencyMatrix[i][j] = true;
		adjacencyMatrix[j][i] = true;
	}

}

// TO DO
// return a vector of vertices adjacent to vertex n
vector<Vertex> Graph::getAdjacentVertices(Vertex n) {
vector<Vertex>adjVertices;


for (Vertex i = 0; i <= size(); i++)
{
	if (adjacencyMatrix[n][i] == true)

	{
		adjVertices.push_back(i);
	}

}


 //for debugging 
for (auto it = adjVertices.begin(); it != adjVertices.end(); it++) {
	cout << getLabel(*it) << endl;
}

return adjVertices;
}

//I'm not really sure if we need it but i feel like we might 
bool Graph::isEdge(Vertex i, Vertex j)
{
	return adjacencyMatrix[i][j];

}

//returns label 
string Graph::getLabel(Vertex n) {
	return intToLabels[n];
}

//return int val for label
Vertex Graph::getVertex(string label)
{
	return labelsToInt[label];
}

//used in recommendFriends
queue<Vertex> Graph::vectorToQueue(vector<Vertex> & v)
{
	queue<Vertex> queueFromVector;

	while(!v.empty())
	{
	Vertex vert = v.back();
	queueFromVector.push(vert);
	v.pop_back();

	}

	return queueFromVector;
}



// TO DO
// return a list of names that contain friends of friends of person
// names should not be repeated

vector<string> recommendFriends(Graph &graph, const string &person)
{
	queue<Vertex> qFirstFriends;
	
	vector<Vertex> friendsFirstOrder;
	vector<Vertex> friendsSecondOrderAdj;
	
	
	vector<string> friendsOfFriends;


	//get vertex
	Vertex startingPerson = graph.getVertex(person);
	// find all friends
	friendsFirstOrder = graph.getAdjacentVertices(startingPerson);
	//make into queue
	qFirstFriends = graph.vectorToQueue(friendsFirstOrder);

	
	string newFriend;

	//gets vector of friends' friends and adds their names to the strign vector
	while (!qFirstFriends.empty())
	{
		//get friends of one existing friend, 
		friendsSecondOrderAdj = graph.getAdjacentVertices(qFirstFriends.front());//vector<vertex>
		
																				 																	 
		//for debugging:
		//for (auto it = friendsSecondOrderAdj.begin(); it != friendsSecondOrderAdj.end(); it++){
		//cout << graph.getLabel(*it) << endl; }
																				  //populate vector of names 
		while (!friendsSecondOrderAdj.empty()) //while friends of a friend vector isnt empty
		{
			newFriend = graph.getLabel(friendsSecondOrderAdj.back()); // get name 
			friendsOfFriends.push_back(newFriend); //add to string vector
			//maybe add error handling here???
			
			
			friendsSecondOrderAdj.pop_back();

		}
	
		qFirstFriends.pop(); //so you can go through the first friends

	}
 
		
	return friendsOfFriends;

}




// COMPLETED
// read from a text file, the labels (names) to be associate with each vertex (int)
void readNamesFromFile(Graph &graph, const string& filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile)
		throw invalid_argument("Unable to open file " + filename);
	string s;
	int i;
	while (!inputFile.eof()) {
		inputFile >> i >> s;
		// cout << "adding label " << i << ": " << s << endl;
		graph.addLabel(i, s);
	}
}

// COMPLETED
// read from a text file, the list of friends for each vertex (int)
void readFriendsFromFile(Graph &graph, const string& filename) {
	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile)
		throw invalid_argument("Unable to open file " + filename);

	for (string line; getline(inputFile, line); ) {
		istringstream iss(line);
		int i;
		iss >> i;
		int j;
		while (!iss.eof()) {
			iss >> j;
			// cout << "adding edge " << i << " to " << j << endl;
			graph.addEdge(i, j);
		}
	}
}
