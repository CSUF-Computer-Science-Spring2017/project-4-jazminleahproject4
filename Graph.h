#pragma once
#include <vector>
#include <string>
#include <map>
#include<queue>

typedef int Vertex;
using namespace std;

class Graph {
public:
	Graph(int n);
	~Graph(); 
	int size();
	void addLabel(Vertex i, string s); 
	void addEdge(Vertex i, Vertex j);
	vector<Vertex> getAdjacentVertices(Vertex n); 


	queue<Vertex> vectorToQueue(vector<Vertex> & v);

	

	Vertex getVertex(string label); 
	string getLabel(Vertex n); 

	bool isEdge(Vertex i, Vertex j);

private:
	// TO DO
	// member variables and functions to implement the public member functions
	map<string,Vertex> labelsToInt;
	map<Vertex,string> intToLabels;
	vector<vector<bool>> adj;
	int n;
	bool ** adjacencyMatrix;

};

// TO DO
// return a list of names that contain friends of friends of person
// names should not be repeated
vector<string> recommendFriends(Graph &graph, const string& person);


// COMPLETED
// read from a text file, the labels (names) to be associate with each vertex (int)
void readNamesFromFile(Graph &graph, const string& filename);

// COMPLETED
// read from a text file, the list of friends for each vertex (int)
void readFriendsFromFile(Graph &graph, const string& filename);
