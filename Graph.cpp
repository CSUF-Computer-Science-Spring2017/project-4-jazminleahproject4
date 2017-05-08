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
	if (i >= 0 && i < n && j > 0 && j < n)
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
	cout << *it << getLabel(*it) << endl;
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

//might need this but I'm not sure 
//queue<string>Graph::errorCheckQueue(vector<Vertex> & v)
//{
//	/*****************************************************************************************************
//	ERROR CHECKING
//	*******************************************************************************************************/
//	string alreadyFriendName;
//	//tring startingprson = graph.getLabel(startingPerson);
//	//ldFriend.push_back(startingprson);
//	for (auto it = friendsFirstOrder.begin(); it != friendsFirstOrder.end(); it++)
//	{
//		alreadyFriendName = graph.getLabel(*it);
//
//		oldFriend.push_back(alreadyFriendName);
//		//cout << "old friend is " << alreadyFriendName << *it << endl;
//	}
//
//
//}



// TO DO
// return a list of names that contain friends of friends of person
// names should not be repeated

vector<string> recommendFriends(Graph &graph, const string &person)
{
	queue<Vertex> qFirstFriends;
	queue<Vertex> qTempSecondFriends;
	
	vector<Vertex> friendsFirstOrder;
	vector<Vertex> friendsSecondOrderAdj;
	queue<Vertex> mapVertices;
	
	map<Vertex, string> mapMutualFriends;
	
	vector<string> friendsOfFriends;

	string newFriend;
	vector<Vertex> oldFriend; // for error checking  
	Vertex secondFriend; // for map
	


	//get vertex
	Vertex startingPerson = graph.getVertex(person);
	//cout << "vertex for Jonathan is " << startingPerson << endl;
	
	// find all friends
	friendsFirstOrder = graph.getAdjacentVertices(startingPerson);
	/*****************************************************************************************************
	ERROR CHECKING
	*******************************************************************************************************/
	string alreadyFriendName;
//tring startingprson = graph.getLabel(startingPerson);
	oldFriend.push_back(startingPerson);
	for (auto it = friendsFirstOrder.begin(); it != friendsFirstOrder.end(); it++)
	{
	//	alreadyFriendName = graph.getLabel(*it);
		
		oldFriend.push_back(*it);
cout << "old friend is " << alreadyFriendName << *it << endl;
	}
	
	
	//make into queue
	qFirstFriends = graph.vectorToQueue(friendsFirstOrder);
	
	string labelSecondFriend;
	Vertex vertexSecondFriend;
	queue<Vertex> qVertexSecondFriend;
	
	
	while (!qFirstFriends.empty())
	{
		//get friends of each person in queue, returns vector of mutual friends 
		friendsSecondOrderAdj = graph.getAdjacentVertices(qFirstFriends.front());
		for (auto it = friendsSecondOrderAdj.begin(); it != friendsSecondOrderAdj.end(); it++)
		{
		qTempSecondFriends.push(*it);
		}
		//queue of vertices of mutual friends

		//now populate mutualfriends map
		while (!qTempSecondFriends.empty())
		{
			vertexSecondFriend = qTempSecondFriends.front();
			labelSecondFriend = graph.getLabel(vertexSecondFriend);
			mapMutualFriends.emplace(vertexSecondFriend, labelSecondFriend);
			mapVertices.push(vertexSecondFriend);
			
				qTempSecondFriends.pop();
		}

		qFirstFriends.pop(); //so you can go through the first friends

	}



	for (auto iterator = oldFriend.begin(); iterator != oldFriend.end(); iterator++)
	{
		map<Vertex, string>::iterator it;
		it = mapMutualFriends.find(*iterator);
		mapMutualFriends.erase(*iterator);


	}
	//for debugging print you map
	map<Vertex, string>::iterator iter;
	for (iter = mapMutualFriends.begin(); iter != mapMutualFriends.end(); iter++)
	{
		cout << "key: " << iter->first << " value: " << iter->second << endl;
	}


	Vertex searchVertex;
	
	//while (!mapMutualFriends.empty())
	while (!mapVertices.empty())
	{
	searchVertex = mapVertices.front();
	map<Vertex, string>::iterator it;
	it = mapMutualFriends.find(searchVertex);

	mapVertices.pop();		
	}

	for (auto it = mapMutualFriends.begin(); it != mapMutualFriends.end(); it++)
	{
		friendsOfFriends.push_back(it->second);

	}
	
	//fcn that turns map into string vector	
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
