#include<string>
#include"Graph.h"
#include<fstream>
#include<iostream>
using namespace std;
bool IsNumber(string); // to be sure that user will enter number
int main()
{
	ifstream file("Graph.txt");
	char type = '0';
	//int check = 0; //check for directed or undirected graph
	char option; //menu options
	string cityName ; 
	string cityName2 ; 
	string checkNum;
	string start_city; //Bfs ,Dfs
	bool flag = false;
	int distance = 0, num_cities = 0, num_edges = 0; //the distance between the two cities
	Graph g;
	cout << "\t\t\t\t\t\t Welcome To Wasalny \n\n";
	if (file.peek() == fstream::traits_type::eof())// to check file is empty 
	{
		cout << "\t\tIf you want directed graph press 0 and and if you want undirected graph press 1: ";
		cin >> type;
	}
	
	while (type != '0' && type != '1') {
		cout << "-----------------------------Enter 0 or 1 only------------------------------\n";
		cin >> type;
	 }
	while (true) {
		cout << "What operation do you want to perform? " <<
			" Select Option number. " << endl;
		cout << "A. Add Graph" << endl;
		cout << "B. Add city" << endl;
		cout << "C. Add Edge" << endl;
		cout << "D. Display City" << endl;
		cout << "F. Delete City" << endl;
		cout << "T. Delete specific edge "<<endl;
		cout << "G. Delete edge" << endl;
		cout << "H. BFS" << endl;
		cout << "K. DFS " << endl;
		cout << "J. Dijkstra " << endl;
		cout << "L. Delete grapg " << endl;
		cout << "E. Exit Program" << endl;
		cin >> option;
		switch (option)
		{
			//add graph 
		case 'a':
		case 'A':
			cout << "How many cities do you want to add: ";
			cin >> checkNum;
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_cities = stoi(checkNum);
			while (num_cities != 0) {
				cout << "Enter the name of the city you want to add: ";
				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				g.add_NewCity(cityName);
				num_cities--;
			}
			cout << "Added successfully \n";
			num_cities = 0;
			cout << "How many edges do you want to add : ";
			cin >> checkNum;
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_edges = stoi(checkNum);
			while (num_edges != 0)
			{
				cout << "Enter the name of the first city : \n";
				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				cout << "Enter the name of the second city : \n";
				cin >> cityName2;
				cityName2[0] = toupper(cityName2[0]);
				cout << "Enter the distance between the two cities : \n";
				cin >> checkNum;
				if (!IsNumber(checkNum)) {
					cout << "Invalid ,Enter number next time \n";
					break;
				}
				distance = stoi(checkNum);
				g.add_NewEdge(cityName, cityName2, distance, type);
				num_edges--;
			}
			cout << "Added successfully \n";
			break;
			//add vertex 
		case 'b':
		case 'B':
			cout << "How many cities do you want to add: ";

			cin >> checkNum;  
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_cities = stoi(checkNum);
		

			while (num_cities != 0) {
				cout << "Enter the name of the city you want to add :";
				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				g.add_NewCity(cityName);
				num_cities--;
			}
			cout << "Added successfully \n";
			break;
			//add edge
		case 'c':
		case 'C':
			cout << "How many edges do you want to add : ";

			cin >> checkNum;
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_edges = stoi(checkNum);


			while (num_edges != 0)
			{
				cout << "Enter the name of the first city : \n";
				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				cout << "Enter the name of the second city : \n";
				cin >> cityName2;
				cityName2[0] = toupper(cityName2[0]);
				cout << "Enter the distance between the two cities : \n";
				cin >> checkNum;
				if (!IsNumber(checkNum)) {
					cout << "Invalid ,Enter number next time \n";
					break;
				}
				distance = stoi(checkNum);
				g.add_NewEdge(cityName, cityName2, distance, type);
				num_edges--;
			}
			cout << "Added successfully \n";
			break;			//display graph 
		case 'd':
		case 'D':
			g.display();
			break;
			//delete city
		case 'f':
		case 'F':
			cout << "How many cities do you want to delete: ";

			cin >> checkNum;  
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_cities = stoi(checkNum);
			while (num_cities != 0) {

				cout << "Enter the name of the the city you want to delete : ";

				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				g.delete_city(cityName);
				num_cities--;
			}
			cout << "Deleted successfully \n";
			break;
			//delete all edges
		case 'g':
		case 'G':
			cout << "How many edges do you want to delete: ";

			cin >> checkNum;
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_edges = stoi(checkNum);
			while (num_edges != 0) {
				cout << "Enter the name of the two cities connected by the edge  \n";
				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				cin >> cityName2;
				cityName2[0] = toupper(cityName2[0]);
				g.delete_edge(cityName, cityName2);
				num_edges--;
			}
			cout << "Deleted successfully \n";
			break;
			//Delete specific edge
		case'T':
		case't':
			cout << "How many edges do you want to delete: ";

			cin >> checkNum;
			if (!IsNumber(checkNum)) {
				cout << "Invalid \n";
				break;
			}
			num_edges = stoi(checkNum);
			while (num_edges != 0) {
				cout << "Enter the name of the two cities connected by the edge and the distance between them  \n";
				cin >> cityName;
				cityName[0] = toupper(cityName[0]);
				cin >> cityName2; cityName2[0] = toupper(cityName2[0]);
				cin >> distance;
				g.delete_edge(cityName, cityName2,distance);
				num_edges--;
			}
			cout << "Deleted successfully \n";
			break;
			//BFS
		case 'h':
		case 'H':
			cout << "Enter the start city name \n";
			cin >> start_city;
			start_city[0] = toupper(start_city[0]);
			g.BFS(start_city);
			break;
			//DFS
		case 'k':
		case 'K':
			cout << "Enter the start city name \n";
			cin >> start_city;
			start_city[0] = toupper(start_city[0]);
			g.DFS(start_city);
			break;
			//exist and save
		case 'e':
		case 'E':
			flag = true;
			cout << "Saved successfully \n";
			break;
			//dijkstra algo
		case 'j':
		case 'J':
			cout << "Enter the source: ";
			cin >> cityName;
			cityName[0] = toupper(cityName[0]);
			cout << "Enter the destination: ";
			cin >> cityName2;
			cityName2[0] = toupper(cityName2[0]);
			g.Dijkstra(cityName, cityName2);
			break;
			//delete graph
		case 'l':
		case 'L':
			g.delete_graph();
			break;
		}
		if (flag) break;
	}
}

bool IsNumber(string Num) {
	for (int i = 0; i < Num.size(); i++) {
		if (!isdigit(Num[i])) {
			return false;
		}
	}
	return true;
}


