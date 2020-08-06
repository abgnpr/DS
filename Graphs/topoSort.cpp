// topological sort using DFS

#include "graph.h"

Assortment DirectedGraph::topoSort() {
  Assortment assorted;
  stack<Vertex> S;
  ExplorationRecord explored;

  for (Vertex _v : V) {
    if (!explored[_v]) {
      S.push(_v);

      while (!S.empty()) {
        Vertex v = S.top();
        if (!explored[v]) {
          int outCount = 0;
          explored[v] = true;
          for (EdgeIt e : out[v]) {
            Vertex w = e->dst;
            if (!explored[w]) {
              S.push(w);
              outCount++;
            }
          }

          if (outCount == 0) {
            assorted.push_front(v);
            S.pop();
          }

        } else {
          assorted.push_front(v);
          S.pop();
        }
      }
    }
  }

  return assorted;
}

int main() {
  DirectedGraph G;

  G.addEdge('C', 'A');
  G.addEdge('F', 'A');
  G.addEdge('A', 'Z');
  G.addEdge('A', 'D');
  G.addEdge('K', 'E');
  G.addEdge('K', 'C');
  G.addEdge('K', 'F');
  G.addEdge('F', 'B');

  G.printAdjList();

  Assortment assorted = G.topoSort();
  cout << "Topo Sort: ";
  for (Vertex v : assorted)
    cout << v << " ";
  cout << "\n\n";
}