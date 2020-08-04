// DFS

#include "graph.h"

// iterative
ExplorationRecord Graph::DFS(Value source) {
  ExplorationRecord explored;
  stack<VertexIt> S;
  VertexIt v = V.find(source), w;

  S.push(v);
  while (!S.empty()) {
    v = S.top();
    S.pop();
    if (!explored[v->val]) {
      explored[v->val] = true;
      for (EdgeIt e : v->out) {
        w = (e->src == v) ? e->dst : e->src;
        S.push(w);
      }
    }
  }

  return explored;
}

// recursive
// precondition: a new instance of ExplorationRecord
// must be passed otherwise the behaviour is undefined
void Graph::DFS_rec(Value source, ExplorationRecord &explored) {
  VertexIt s = V.find(source), v;
  explored[source] = true;
  for (EdgeIt e : s->out) {
    v = (e->src == s) ? e->dst : e->src;
    if (!explored[v->val])
      DFS_rec(v->val, explored);
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
                : cout << "A isn't reachable from D\n";

  explored.clear();

  G.DFS_rec('Z', explored);
  explored['x'] ? cout << "x is reachable from Z\n"
                : cout << "x isn't reachable from Z\n";
}
