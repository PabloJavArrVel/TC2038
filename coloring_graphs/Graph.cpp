
#include "Graph.h"
#include <queue>
#include <vector>

Graph::Graph() {
  adjList.clear();
  adjMatrix.clear();
  grados.clear();
  numNodes = 0;
  numEdges = 0;
}

Graph::~Graph() {
  adjList.clear();
  adjMatrix.clear();
  grados.clear();
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
    if (i == 0) {
      std::vector<int> res;
      split(line, res);
      numNodes = res[0];
      numEdges = res[1];
      // Reservar memoria para los renglones de la lista de adyacencia
      // cada uno tiene un set vacio
      adjList.resize(numNodes, std::set<int>());
      // Reservar memoria para los renglones de la matriz de adyacencia
      // cada uno tiene un vector con valores cero
      adjMatrix.resize(numNodes, std::vector<int>(numNodes, 0));
      // Reservar memoria para el vector grados
      grados.resize(numNodes);
      for (int k = 0; k < numNodes; k++) {
        grados[k].first = 0; // grado
        grados[k].second = k; // nodo
      }
      i++;
      continue;
    }
    std::vector<int> res;
    split(line, res);
    int u = res[0] - 1; // convierte nodo a cero-basado
    int v = res[1] - 1; // convierte nodo a cero-basado
    // Grafos no dirigidos agrega la arista (u,v) y la (v,u)
    adjList[u].insert(v);
    adjList[v].insert(u);
    adjMatrix[u][v] = 1;
    adjMatrix[v][u] = 1;
    // El nodo u y v tienen una arista mas
    grados[u].first++;
    grados[v].first++;
    i++;
  }
}

// Imprime grafo 
void Graph::print() {
  std::cout << "Adjacency List" << std::endl;
  for (int u = 0; u < numNodes; u++) {
    std::cout << "vertex " << u + 1 << ":"; // convierte nodo a uno-basado
    std::set<int> g = adjList[u];
    std::set<int>::iterator it;
    for (it = g.begin(); it != g.end(); ++it) {
      int w = *it;
      // convierte nodo a uno-basado
      std::cout << '\t' << w + 1 << ",";
    }
    std::cout << std::endl;
  }
  std::cout << "Adjacency Matrix" << std::endl;
  for (int u = 0; u < numNodes; u++) {
    for (int v = 0; v < numNodes; v++) {
      if (adjMatrix[u][v] == INF)
        std::cout << "Inf\t";
      else  
        std::cout << adjMatrix[u][v] << "\t";
    }
    std::cout << std::endl;
  }
}

void Graph::BFSColoring(int v, std::vector<int>& schedule) {
    std::vector<int> color(numNodes, 0); // 0 = unvisited, 1/2 = colors/shifts
    std::vector<bool> visited(numNodes, false);
    std::queue<int> q;

    visited[v] = true;
    color[v] = 2;
    q.push(v);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int neighbor : adjList[u]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                (color[u] == 1)? (color[neighbor] = 2) : (color[neighbor] = 1);
                q.push(neighbor);
            }
            else {
              if (color[neighbor] == color[u]) {
                    return;
                } else {
                    continue;
                }
            }
        }
    }
    schedule = color;
}
 

void Graph::algoritmoWelshPowell() {
  // Ordenar el vector grados descendentemente
  std::sort(grados.rbegin(), grados.rend());
  // Vector con el color de cada nodo
  std::vector<int> color(numNodes, 0);
  int colorAssigned = 0;
  for (int i = 0; i < numNodes; i++) {
    int u = grados[i].second; // nodo u
    if (!color[u]) {
      color[u] = ++colorAssigned;
      // conjunto de nodos coloreados con colorAssigned
      std::unordered_set<int> coloredWithColorAssigned;
      coloredWithColorAssigned.insert(u);
      for (int j = i+1; j < numNodes; j++) {
        int v = grados[j].second; // nodo v
        // Verificar si u es vecino de v
        bool notAdyacent = adjList[u].find(v) == adjList[u].end();
        if (!color[v] && notAdyacent) {
          // Verificar si v es adyacente 
          // a vertices coloreados con colorAssigned
          bool adyacentToColored = false;
          std::unordered_set<int>::iterator it;
          for (it = coloredWithColorAssigned.begin(); it != coloredWithColorAssigned.end(); ++it) {
            int w = *it; // nodo w
            if (adjList[v].find(w) != adjList[v].end())
              adyacentToColored = true;
          }
          if (!adyacentToColored) {
            color[v] = colorAssigned;
            coloredWithColorAssigned.insert(v);
          }
        }
      }
    }
  }
  std::cout << "Colores asignados" << std::endl;
  for (int u = 0; u < numNodes; u++) {
    std::cout << "vertice: " << u+1 << " color: " << color[u] << std::endl;
  }  
}
