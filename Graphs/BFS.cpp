#include "graph.h"

ExplorationRecord Graph::BFS(Value source) {
  ExplorationRecord explored;
  queue<VertexIt> Q;
  VertexIt v, w;

  if ((v = V.find(source)) != V.end()) {
    explored[source] = true;
    Q.push(v);
    while (!Q.empty()) {
      v = Q.front();
      Q.pop();
      for (EdgeIt e : v->out) {
        w = (e->src == v) ? e->dst : e->src;
        if (!explored[w->val]) {
          explored[w->val] = true;
          Q.push(w);
        }
      }
    }
  }

  return explored;
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

  ExplorationRecord explored = G.BFS('D');
  explored['A'] ? cout << "A is reachable from D\n"
                : cout << "A isn't reachable from D\n";
}
