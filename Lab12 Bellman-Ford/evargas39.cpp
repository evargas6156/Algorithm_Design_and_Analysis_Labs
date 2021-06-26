#include <iostream>
using namespace std;

//a structure made to hold edge values
struct Edge {
	//stores edges starting vertex
	int start;
	//stores edges ending vertex
	int end;
	//stores the weight of the edge 
	int weight;
};

//a structure to represent a graph
struct Graph {
	//stores the number of vertices 
	int numVertices;
	//stores the number of edges
	int numEdges;
	//stores all of the graphs edges
	Edge* edges; 
	
	//constructor to create and initialize a graph with v vertices and e edges
	Graph(int v, int e){
		numVertices = v;
		numEdges = e;
		edges = new Edge[e];
	}
};

void printDistances(int distances[], int size){
	for(int i = 0; i < size; i++){
		if(distances[i] == INT8_MAX){
			cout<<"INFINITY\n";
		}else{
			cout<<distances[i]<<endl;
		}
	}
}	

//a function to relax the edge 
void relax(int u, int v, int w, int distances[]){
	if(distances[v] > (distances[u] + w)){
		distances[v] = distances[u] + w;
	}
}

void bellmanFord(Graph* graph, int start){
	//create an array of distances, get info of vertices and edges from graph
	int numEdges = graph->numEdges;
	int numVertices = graph->numVertices;
	int distances[numVertices];
	
	//initialize the distances to infinity
	for(int i = 0; i < numVertices; i++){
		distances[i] = INT8_MAX;
	}
	//make starting distance = 0
	distances[start] = 0;
	int currU;
	int currV;
	int currW;
	
	//relax each edge v - 1 times
	for(int i = 1; i < numVertices; i++){
		for(int j = 0; j < numEdges; j++){
			currU = graph->edges[j].start;
			currV = graph->edges[j].end;
			currW = graph->edges[j].weight;
			relax(currU, currV, currW, distances);
		}
	}
	
	//check for negative weight cycles, if there is one return false 
	for(int i = 0; i < numEdges; i++){
			currU = graph->edges[i].start;
			currV = graph->edges[i].end;
			currW = graph->edges[i].weight;
			if(distances[currV] > (distances[currU] + currW)){
				cout<<"FALSE\n";
				return;
			}
	}
	//print true and the corresponding distances 
	cout<<"TRUE\n";
	printDistances(distances, numVertices);

}

int main(int argc, char **argv){
	int u, v, w;
	int numVertices, numEdges;
	
	//get number of vertices and edges for the graph
	cin >> numVertices;
	cin >> numEdges;
	
	//create a new graph with parameters above 
	Graph* graph = new Graph(numVertices, numEdges);
	
	//get the information for each edge 
	for(int i = 0; i < numEdges; i++){
		cin >> u;
		cin >> v;
		cin >> w;
		graph->edges[i].start = u;
		graph->edges[i].end = v;
		graph->edges[i].weight = w;
	}

	//run the bellman ford algorithm on the given graph
	bellmanFord(graph, 0);
	
}