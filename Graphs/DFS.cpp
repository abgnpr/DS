// DFS

#include "graph.h"

// iterative DFS
ExplorationRecord Graph::DFS(Vertex source) {
  ExplorationRecord explored;
  stack<Vertex> S;

  S.push(source);
  while (!S.empty()) {
    Vertex v = S.top();
    S.pop();
    if (!explored[v]) {
      explored[v] = true;
      for (EdgeIt e : out[v]) {
        Vertex w = (e->src == v) ? e->dst : e->src;
        S.push(w);
      }
    }
  }

  return explored;
}

// recursive DFS
// precondition: a new or empty instance of ExplorationRecord must be passed
// since it is an auxilary parameter
void Graph::DFS_rec(Vertex source, ExplorationRecord &explored) {
  explored[source] = true;
  for (EdgeIt e : out[source]) {
    Vertex v = (e->src == source) ? e->dst : e->src;
    if (!explored[v])
      DFS_rec(v, explored);
  }
}

int main() {
  UndirectedGraph /* or DirectedGraph */ G;

  G.addEdge('A', 'B');
  G.addEdge('B', 'C');
  G.addEdge('C', 'D');
  G.addEdge('D', 'C');
  G.addEdge('9', 'D');
  G.addEdge('Z', 'x');
  G.addEdge('Z', 'z');
  G.addEdge('X', 'x');

  G.printAdjList();

  ExplorationRecord explored = G.DFS('D');
  explored['A'] ? cout << "A is reachable from D\n"
                : cout << "A is unreachable from D\n";

  explored = G.DFS('Z');
  explored['A'] ? cout << "A is reachable from Z\n"
                : cout << "A is unreachable from Z\n\n";

  explored.clear();
  G.DFS_rec('Z', explored);
  explored['x'] ? cout << "x is reachable from Z\n"
                : cout << "x is unreachable from Z\n";
}
