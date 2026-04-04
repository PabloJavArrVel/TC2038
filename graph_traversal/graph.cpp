#include "graph.h"

Graph::Graph() {
  //std::cout << "Constructor " << this << std::endl;
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  //std::cout << "Destructor " << this << std::endl;
  adjList.clear();
  numNodes = 0;
  numEdges = 0;
}

void Graph::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

void Graph::readGraph(std::istream &input) {
  std::string line;
  int i = 0;
  while (std::getline(input, line)) {
    if (line.empty()) { i++; continue; } // skip empty lines
    if (i == 0) {
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[1];
      // Reservar memoria para los renglones de la lista de adyacencia
      // cada uno tiene una lista vacia
      adjList.resize(numNodes, std::list<std::pair<int, int>>());
      i++;
      continue;
    }
    std::vector<int> res;
    split(line, res);
    int u = res[0] - 1; // convierte nodo a cero-basado
    int v = res[1] - 1; // convierte nodo a cero-basado
    int weight = res[2];
    // Grafos dirigidos agrega solo la arista (u,v)
    // Grafo ponderado guarda pares(nodo, peso)
    adjList[u].push_back(std::make_pair(v, weight));
    i++;
  }
}

int Graph::getNumNodes() const {
    return numNodes;
}

// Imprime grafo 
void Graph::print() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 0; u < numNodes; u++) {
    std::cout << "vertex " << u + 1 << ":"; // convierte nodo a uno-basado
    std::list<std::pair<int, int>> g = adjList[u];
    std::list<std::pair<int, int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int, int> par = *it;
      // convierte nodo a uno-basado
      std::cout << '\t' << "{" << par.first + 1 << "," << par.second << "}";
    }
    std::cout << std::endl;
  }
  //std::cout << "Size adjList print " << adjList.size() << std::endl;
}

// Recorrido del grafo DFS a partir del nodo v (cero-basado)
void Graph::DFS(int v, int t) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Creamos un stack
  std::stack<int> stack;
  bool isInVisited = false;
  std::cout << "Recorrido DFS " << std::endl;
  // Entra al stack el vertice inicial
  stack.push(v);
  while (!stack.empty()) {
    // Extraemos un vertice del stack y lo procesamos (print)
    v = stack.top();
    stack.pop();
    isInVisited = visited.find(v) != visited.end();
    if (!isInVisited) {
      visited.insert(v);
      // convierte nodo a uno-basado
      std::cout << v + 1 << " ";
    }
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados se marcan como visitados
    // y los metemos al stack
    std::list<std::pair<int, int>> g = adjList[v];
    std::list<std::pair<int, int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int, int> par = *it;
      int u = par.first;
      // Verificar si el vecino u ya fue visitado
      isInVisited = visited.find(u) != visited.end();
      if (!isInVisited) // no visitado
        stack.push(u);
    }
  }
  std::cout << std::endl;
}

void Graph::dfsMinimax(int v, int t,
                std::vector<bool>& visited,
                std::vector<int>& path,
                int currentMax,
                int& bestMax,
                std::vector<int>& bestPath) {

    visited[v] = true;
    path.push_back(v);

    if (v == t) {
        if (currentMax < bestMax) {
            bestMax = currentMax;
            bestPath = path;
        }
    } else {
        
        for (auto& par : adjList[v]) {
            int u = par.first;
            int weight = par.second;

            // guardamos le/w más grande en el recorrido
            if (!visited[u]) {
                int newMax = std::max(currentMax, weight);

                //no exploramos ramas peores
                if (newMax < bestMax) {
                    dfsMinimax(u, t, visited, path, newMax, bestMax, bestPath);
                }
            }
        }
    }

    path.pop_back();
    visited[v] = false;
}

// Recorrido del grafo BFS a partir del nodo v (cero-basado)
void Graph::BFS(int v) {
  // Declarar un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  // Crear un queue
  std::queue<int> queue;
  bool isInVisited = false;
  // Entra al queue el vertice inicial
  queue.push(v);
  while (!queue.empty()) {
    // Extraer un vertice del queue y lo procesamos (print)
    v = queue.front();
    queue.pop();
    isInVisited = visited.find(v) != visited.end();
    if (!isInVisited) {
      visited.insert(v);
      // convierte nodo a uno-basado
      std::cout << v + 1 << " ";
    }
    // Obtenemos los vertices adyacentes del vertice v
    // Si estos no han sido visitados se marcan como visitados
    // y los metemos al queue
    std::list<std::pair<int, int>> g = adjList[v];
    std::list<std::pair<int, int>>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      std::pair<int, int> par = *it;
      int u = par.first;
      // Verificar si el vecino u ya fue visitado
      isInVisited = visited.find(u) != visited.end();
      if (!isInVisited) // no visitado
        queue.push(u);
    }
  }
  std::cout << std::endl;
}