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
		for (int j = 0; j < n; j++)
			adjacencyMatrix[i][j] = false;
	}
	

}

// TO DO
// return the maximum number of vertices
int Graph::size() {
	return 0;
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
	//adjacencyMatrix[i] = s;

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

}


// TO DO
// return a list of names that contain friends of friends of person
// names should not be repeated
//vector<string> recommendFriends(Graph &graph, const string &person) {
//	return ;
//}


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
