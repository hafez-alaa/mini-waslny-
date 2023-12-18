#pragma once
#include<unordered_map>
#include<vector>
#include<string>

using namespace std;
class Graph
{
private://
	
	unordered_map<string, vector<pair<string, int>>>graph; // hash table because fast than map , and we don't care order
	char type_Graph;
	// check city exist or not
	bool not_exist(string, string);
	bool not_exist(string);
public:
	Graph();
	~Graph();
	void delete_graph();
	void display(); 
	
	// update graph (add)/
	void add_NewCity(string); 
	void add_NewEdge(string, string, int, char);
	// update graph (delete)//
	void delete_city(string);
	void delete_edge(string, string, int);
	void delete_edge(string, string);
	// Traverse the graph
	void BFS(string); 
	void DFS(string); 
	// Dijkstra's Algorithm
	void Dijkstra(string , string ); 
	// save & load 
	class Control {
	public:
		static void save(unordered_map<string, vector<pair<string, int>>>&, char&);
		static void load(unordered_map<string, vector<pair<string, int>>>&, char&);

	};
	
};


