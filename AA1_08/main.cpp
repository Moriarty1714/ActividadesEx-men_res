#include <map>
#include <iostream>
#include "grafo.h"

int main() {
	std::vector<edge> myEdges;
	myEdges.push_back(edge(2, 3));
	myEdges.push_back(edge(3, 1));
	myEdges.push_back(edge(1, 12));
	myEdges.push_back(edge(1, 6));
	myEdges.push_back(edge(4, 1));
	myEdges.push_back(edge(8, 4));
	myEdges.push_back(edge(6, 8));
	myEdges.push_back(edge(6, 10));
	myEdges.push_back(edge(10, 12));
	myEdges.push_back(edge(12, 6));

	GraphD myGraph (myEdges);

	myGraph.Print();

	myGraph.Remove(edge(6, 8));

	myGraph.Print();

	bool existPath = myGraph.Path(2,4);

	std::cout << existPath << std::endl;
	return 0;
}