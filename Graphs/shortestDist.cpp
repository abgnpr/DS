// Shortest Distance

#include "graph.h"

float Graph::shortestDistance(Value source, Value target) {
  DistanceRecord distance;
  ExplorationRecord explored;
  queue<VertexIt> Q;
  VertexIt v, _v, _w;

  for (const auto &i : V)
    distance[i.val] = INFINITY;

  if ((v = V.find(source)) != V.end() && V.find(target) != V.end()) {
    explored[source] = true;
    distance[source] = 0;
    Q.push(v);
    while (!Q.empty()) {
      v = Q.front();
      Q.pop();
      for (EdgeIt e : v->out) {
        _v = (e->src == v) ? e->src : e->dst; // required for
        _w = (e->src == v) ? e->dst : e->src; // undirected edges
        if (!explored[_w->val]) {
          explored[_w->val] = true;
          Q.push(_w);
          distance[_w->val] = distance[_v->val] + 1;
        }
      }
    }
  }

  return distance[target];
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

  cout << G.shortestDistance('A', 'D') << "\n";
  cout << G.shortestDistance('9', 'C') << "\n";
}