#include <map>
#include <iostream>
#include <vector>

typedef int vertex;
typedef std::pair<int, int> edge;

class GraphD {
private:
	std::map<vertex, std::vector<vertex>> g;
public:
	GraphD(GraphD *_g) {
		g = _g->g;
	}

	GraphD(std::vector<edge> ed) {
		for (int i{ 0 }; i < ed.size(); i++)
			Insert(ed[i]);
	}

	~GraphD() {
		for (auto it = g.begin(); it != g.end();) {
			it->second.clear();
			g.erase(it);
		}
	}

	void Insert(edge e) {
		if (g.empty()) {	//El mapa esta vacio? Si
			g[e.first].push_back(e.second);
			g[e.second];
		}
		else {	//El mapa esta vacio? No
			auto itF = g.find(e.first);
			auto itS = g.find(e.second);

			if (itF == g.end()) {	//Existe el primer vértice? No
				g[e.first].push_back(e.second);
			}
			else {	//Existe el primer vértice? Si
				//Miro si ya tiene el segundo vértice en su vector. Si no lo tiene hago push;
				if (std::find(g[e.first].begin(), g[e.first].end(), e.second) == g[e.first].end()) {
					g[e.first].push_back(e.second);
				}
			}

			if (itS == g.end()) {	//Existe el segundo vértice? No
				g[e.second];
			}
		}
	}

	void Remove(edge e) {
		if (!g.empty()) {	//Si el mapa no esta vacio, busca los vértices en el map
			auto itF = g.find(e.first);
			auto itS = g.find(e.second);
			
			if (itF != g.end()) {	//Si existe el primer vertice...
				auto tmpIt = std::find(g[e.first].begin(), g[e.first].end(), e.second);	//...busca el segundo vertice...
				if(tmpIt != g[e.first].end()) g[e.first].erase(tmpIt);	//...y eliminalo del vector. 

				if (g[e.first].empty()) g.erase(e.first); //Si el vértice no tiene arcos, cargate-lo.
			}

			if (itS != g.end()) {	//Si existe el segundo vertice...
				if (g[e.second].empty()) g.erase(e.second);	//...y el vértice no tiene arcos, cargate-lo.
			}
		}
	}

	bool Path(vertex init, vertex end) {
		std::vector<vertex> vertexVisited;
		vertexVisited.push_back(init);
		return searchPath(init, end, vertexVisited);
	}

	bool searchPath(vertex v, vertex end, std::vector<vertex> _vertexVisited) {
		bool allRepeated = true;	//Control para saber si los vertices que tiene el vertice dado son todos repetidos.
		std::vector <bool> verificated;	//Guardan el resultado de los searchPath de todos los caminos possibles;
		for (int i{ 0 }; i < g[v].size(); i++) {	//Recorre el vector del vértice donde nos encontramos
			if (g[v][i] == end) return true;	//Si encontramos el que buscamos, devolvemos true.
			if (std::find(_vertexVisited.begin(), _vertexVisited.end(), g[v][i]) == _vertexVisited.end()) {	//Tenemos que comprovar que el vertice que visitaremos próximamente 
				_vertexVisited.push_back(g[v][i]);	//Hacemos push del vertice que visitaremos 				  no se haya visitado ya.
				verificated.push_back(searchPath(g[v][i], end, _vertexVisited));	//Volvemos a hacer la función recursiva con el nuevo vértice pasandole el vector de vertices POR COPIA;
				allRepeated = false;	//Como ha encontrado un vertice NO repetido, no estan todos repetidos.
			}
		}
		if (allRepeated) return false;	//Si no ha encontrado el que buscamos y ya hemos visitado sus vértices anteriormente, devuelve falso.
		if (std::find(verificated.begin(), verificated.end(), true) == verificated.end()) return false;	//Si no encuentra ningun TRUE en el vector de verificados, devuelve falso.
		else return true; //En caso contrario, una de las funciones recursivas ha encontrado un camino y se devuelve TRUE.
	}

	void Print() {
		for (auto it = g.begin(); it != g.end(); it++) {
			std::cout << it->first <<": ";
			for (int j{ 0 }; j < it->second.size(); j++) {
				std::cout << it ->second[j] <<", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl; 
	}

	bool IsEulerian() {
		int impares = 0;
		for (auto it = g.begin(); it != g.end(); it++) {
			if (it->second.size() % 2 != 0) {
				impares++;
			}	
			if (impares > 2) return false;
		}
		return true;
	}

	int Index(vertex e) {
		return g[e].size();
	}
};