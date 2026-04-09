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

void Graph::filterEdges(int maxWeight) {
    for (int u = 0; u < numNodes; u++) {
        adjList[u].remove_if([maxWeight](const std::pair<int,int>& p) {
            return p.second > maxWeight;
        });
    }
}

void Graph::dijkstra(int s, int t, std::vector<int>& path, int& maxEdge){
  //initialize g_n and make max edge negative
  std::vector<int> g_n(numNodes, INT_MAX);
  std::vector<int> parent(numNodes, -1);
  std::vector<bool> visited(numNodes, false);

  g_n[s] = 0;
  maxEdge = -1;

  //While u isn't t
  for (int i = 0; i < numNodes; i++) {

    int u = -1;

    // choose the node with minimum g_n 
    for (int j = 0; j < numNodes; j++) {
      if (!visited[j] && (u == -1 || g_n[j] < g_n[u])) {
        u = j;
      }
    }

    if (u == -1 || g_n[u] == INT_MAX)
      break;

    visited[u] = true;

    if (u == t)
      break;

    //Starting from s choose the neighbour that minimizes g_n, sum it to g_n and add to path
    for (auto& par : adjList[u]) {
      int v = par.first;
      int w = par.second;

      if (!visited[v] && g_n[u] + w < g_n[v]) {
        g_n[v] = g_n[u] + w;
        parent[v] = u;
      }
    }
  }

  // reconstruct path
  for (int v = t; v != -1; v = parent[v]) {
    path.push_back(v);
  }
  std::reverse(path.begin(), path.end());


  for (int i = 0; i + 1 < path.size(); i++) {
    int u = path[i];
    int v = path[i + 1];

    for (auto& par : adjList[u]) {
      if (par.first == v) {
        maxEdge = std::max(maxEdge, par.second);
        break;
      }
    }
  }
}

void Graph::DFS(int v, int t, std::vector<int>& path) {
  // Declaramos un set del STL de C++ (elementos unicos y ordenados)
  std::set<int> visited;
  std::vector<int> parent(numNodes, -1);
  // Creamos un stack
  std::stack<int> stack;
  bool isInVisited = false;
  // Entra al stack el vertice inicial
  stack.push(v);
  while (!stack.empty()) {
    // Extraemos un vertice del stack y lo procesamos (print)
    v = stack.top();
    stack.pop();
    isInVisited = visited.find(v) != visited.end();
    if (isInVisited)
      continue;
    if (!isInVisited) {
      visited.insert(v);
    }
    if (v==t) {
      for(int i = t; i != -1; i = parent[i]){
          path.push_back(i);
      }
      std::reverse(path.begin(), path.end()); 
      return;
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
      if (!isInVisited) {
        if (parent[u] == -1)
          parent[u] = v;
        stack.push(u);
      }
    }
  }
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