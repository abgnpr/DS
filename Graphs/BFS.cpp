// BFS

#include "graph.h"

ExplorationRecord Graph::BFS(Vertex source) {
  ExplorationRecord explored;
  queue<Vertex> Q;

  explored[source] = true;
  Q.push(source);
  while (!Q.empty()) {
    Vertex v = Q.front();
    Q.pop();
    for (EdgeIt e : out[v]) {
      Vertex w = (e->src == v) ? e->dst : e->src;
      if (!explored[w]) {
        explored[w] = true;
        Q.push(w);
      }
    }
  }

  return explored;
}

int main() {
  UndirectedGraph G; // or DirectedGraph

  G.addEdge('A', 'B');
  G.addEdge('B', 'C');
  G.addEdge('C', 'D');
  G.addEdge('D', 'C');
  G.addEdge('9', 'D');
  G.addEdge('Z', 'x');
  G.addEdge('Z', 'z');
  G.addEdge('X', 'x');

  G.printAdjList();

  ExplorationRecord explored = G.BFS('D');
  explored['A'] ? cout << "A is reachable from D\n"
                : cout << "A is unreachable from D\n";

  explored = G.BFS('A');
  explored['Z'] ? cout << "Z is reachable from A\n"
                : cout << "Z is unreachable from A\n\n";
}
