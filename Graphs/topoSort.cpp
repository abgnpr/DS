// topological sort using DFS

#include "graph.h"

// note: behaviour undefined if cycles are present
Assortment DirectedGraph::topoSort() {
  Assortment assorted;
  stack<Vertex> S;
  ExplorationRecord explored;

  for (Vertex i : V) {
    if (!explored[i]) {
      S.push(i);

      while (!S.empty()) {
        Vertex v = S.top();
        if (!explored[v]) {
          explored[v] = true;
          
          int outCount = 0;
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