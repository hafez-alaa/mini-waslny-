#include "Graph.h"
#include<assert.h>
#include<iostream>
#include<unordered_map>
#include<queue>
#include<stack>
#include<fstream>
#include<filesystem>
using namespace std;
bool Graph::not_exist(string city1, string city2 ) // to check city exist or not 
{
	return graph.find(city1) == graph.end() || graph.find(city2) == graph.end();	// if equal end  in one or both graph then return true
}

bool Graph::not_exist(string city)
{
	return graph.find(city) == graph.end();	// if equal end  in one or both graph then return true
}

Graph::Graph()
{
	type_Graph = NULL;
	Control::load(graph, type_Graph);
}
Graph::~Graph()
{
	Control::save(graph, type_Graph);
}

void Graph::delete_graph()
{
		graph.clear();	
		cout << "Graph deleted successfully \n";
}

void Graph::display()
{
	unordered_map<string, vector<pair<string, int>>>::iterator it;
	for (it = graph.begin(); it != graph.end(); it++)
	{
		cout << it->first << " : ";
		for (int i = 0; i < it->second.size(); i++)	// for each element in vector 
		{
			if (it->second[i].first == "0")
				continue;
			cout << it->second[i].first << " <- " << it->second[i].second << "   ";
		}
		cout << endl;
	}
}
// implementation of update graph (add)
void Graph::add_NewCity(string city)
{
	if (not_exist(city)) // check  this city exist or not
	{
		graph[city].push_back({ "0",0 });	
	}
	else {
		cout << "Failed to add because this is city already exist \n ";
		return;
	}
}

void Graph::add_NewEdge(string start, string end, int distance, char type)
{
	// check exist or not

	try {
		if (not_exist(start, end))
		{
			cout << "city " << start << " or city " << end << " not exist, ";
			throw "failed ,Try again and enter an existing citys\n";
		}
	}
	catch (const char* e)
	{
		cout << e;
		return;
	}
	if (type_Graph == NULL)
		type_Graph = type;
	// for undirected graph
	if (type_Graph == '1')
	{
		graph[start].push_back({ end,distance });
		graph[end].push_back({ start,distance });
	}
	else // for directed graph
	{
		graph[start].push_back({ end,distance });	 
	}
	
}
// implementation of update graph (delete)
void Graph::delete_city(string city)
{
	try {
		if (not_exist(city))
			throw "try again and enter an existing citys\n";
	}
	catch (const char* e)
	{
		cout << e;
		return;
	}
	graph.erase(city);
	for (auto it = graph.begin(); it != graph.end(); it++)
	{
		for (int i = 0; i < it->second.size(); i++)	// for each element in vector  
		{
			if (it->second[i].first == city)
			{
				swap(it->second[i], it->second[it->second.size() - 1]);	// swap element before delete to avoid shift element  
				it->second.pop_back();	// to erase all connection with citys
				i--;			
			}

		}
	}

}
//delete all edges
void Graph::delete_edge(string start, string end) {
	try {
		if (not_exist(start, end))	// check  citys exist or not 
		{
			cout << "city " << start << " or city " << end << " not exist, ";
			throw "Try again and enter an existing citys\n";
		}
	}
	catch (const char* e)
	{
		cout << e;
		return;//a c
	}
	for (int i = 0; i < graph[start].size(); i++)
	{
		if (graph[start][i].first == end) // i=1
		{
			swap(graph[start][i], graph[start][graph[start].size() - 1]);	// swap element before delete to avoid shift element  
			graph[start].pop_back();		// to erase all connection with citys
			i--;
		}
	}
	for (int i = 0; i < graph[end].size(); i++)
	{
		if (graph[end][i].first == start)
		{
			swap(graph[end][i], graph[end][graph[end].size() - 1]);	// swap element before delete to avoid shift element  
			graph[end].pop_back();	// to erase all connection with citys
			i--;
		}
	}
	
}
// delete a specific edge
void Graph::delete_edge(string start, string end ,int edge)
{
	bool check=1;
	try {
		if (not_exist(start, end))	// check  citys exist or not 
		{
			cout << "city " << start << " or city " << end << " not exist, ";
			throw "try again and enter an existing citys\n";
		}
	}
	catch (const char* e)
	{
		cout << e;
		return;
	}
	for (int i = 0; i < graph[start].size(); i++)
	{	
		if (graph[start][i].first == end && graph[start][i].second == edge)
		{
			swap(graph[start][i], graph[start][graph[start].size() - 1]);	// swap element before delete to avoid shift element  
			graph[start].pop_back();		// to erase all connection with citys
			check = 0;
			break;
			i--;
		}	
	}
	if (check) { cout << "Enter an existing edge \n"; return; }
	for (int i = 0; i < graph[end].size(); i++)
	{
		if (graph[end][i].first == start && graph[end][i].second == edge)
		{
			swap(graph[end][i], graph[end][graph[end].size() - 1]);	// swap element before delete to avoid shift element  
			graph[end].pop_back();	// to erase all connection with citys
			i--;
		}
	}
	
} 
//BFS
void Graph::BFS(string source)
{
	queue<string>q;
	unordered_map <string, bool>visited;
	string start;
	q.push(source);
	while (!q.empty())
	{
		start = q.front();
		q.pop();
		if (!visited[start])
		{
			visited[start] = 1;
			cout << start << " ";
			for (auto it : graph[start])
			{
				if (!visited[it.first] &&it.first != "0")
					q.push(it.first);
			}
		}
	}
	cout << endl;
}
void Graph::DFS(string source)
{
	stack<string>s;
	unordered_map <string, bool>visited;
	string start;
	s.push(source);
	while (!s.empty())
	{
		start = s.top();
		s.pop();
		if (!visited[start])
		{
			visited[start] = 1;
			cout << start << " ";
			for (auto child: graph[start])
			{
				if (!visited[child.first] && child.first != "0")
					s.push(child.first);
			}
		}
	}
	cout << endl;
}
void Graph::Dijkstra(string startCity, string endCity)
	{
		// Check if the start and end cities exist
		if (not_exist(startCity, endCity))
		{
			cout << "City " << startCity << " or city " << endCity << " does not exist." << endl;
			return;
		}

		// Declaration priority_queue 
		priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> priority_queue;

		// Declaration destance to carry all distance from first city to another
		unordered_map<string, int> distance;

		// Declaration previous to carry all previous node
		unordered_map<string, string> previous;

		for ( auto it = graph.begin(); it != graph.end(); it++)
		{

			distance[it->first] = INT_MAX;
			previous[it->first] = "";
		}
		distance[startCity] = 0;

		priority_queue.push(make_pair(0, startCity));

		while (!priority_queue.empty())
		{   
			string current = priority_queue.top().second;
			priority_queue.pop();
			if (current == endCity)
	    		break;
		
			for (auto neighbor : graph[current])
			{
				string next = neighbor.first;
				int weight = neighbor.second;
				int newDistance = distance[current] + weight; 
				if (newDistance < distance[next])
				{
					distance[next] = newDistance;
					previous[next] = current;
					priority_queue.push(make_pair(newDistance, next));
				}
			}
		}
		if (previous[endCity] == "")
		{
			cout << "There is no path from " << startCity << " to " << endCity << "." << endl;
			return;
		}

		//stack to inverse order
		stack<string> pathStack;
		string current = endCity;
		while (current != "")
		{
			pathStack.push(current);
			current = previous[current];
		}

		cout << "Shortest path from " << startCity << " to " << endCity << ": ";
		while (!pathStack.empty())
		{
			cout << pathStack.top();
			pathStack.pop();
			if (!pathStack.empty())
				cout << " -> ";
		}
		cout << endl;
		cout << "Total distance: " << distance[endCity] << endl;
}
void  Graph::Control::save(unordered_map<string, vector<pair<string, int>>>& graph, char& type_Graph)
{

	ofstream tmp("Graph.txt");
	ofstream file("tmp.txt");
	if (!file) {
		cout << " Error \n";
		return;
	}
	if (!tmp) {
		cout << " Error \n";
		return;
	}
	file << type_Graph << endl;
	file.close();
	for (auto it : graph)
	{
		for (int i = 0; i < it.second.size(); i++)
		{
			
			tmp << it.first << " " << it.second[i].first << " " << it.second[i].second << endl;
		}
	}
	tmp.close();
}
void Graph::Control::load(unordered_map<string, vector<pair<string, int>>>& graph, char& type_Graph)
{
	ifstream file("Graph.txt");

	string start, end;
	char type;
	int distance;

	if (file.peek() == fstream::traits_type::eof()) // to check file is empty 
	{
		ifstream tmp("tmp.txt", ios::trunc);
		tmp.close();
	}
		
	else
	{
		ifstream tmp("tmp.txt");
		if (!tmp.is_open()) {
			cout << " file failed to open\n";
			return;
		}
		tmp >> type;
		type_Graph = type;
		tmp.close();
	}
	if (!file.is_open()) {
		cout << " file failed to open\n";
		return;
	}
	while (file >> start >> end >> distance) {
	
		graph[start].push_back({ end,distance });
	}
	file.close();
}