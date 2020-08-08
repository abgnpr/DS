// Shortest Distance

#include "graph.h"

float Graph::shortestDistance(Vertex source, Vertex target) {
  DistanceRecord distance;
  ExplorationRecord explored;
  queue<Vertex> Q;

  for (Vertex v : V)
    distance[v] = INFINITY;

  explored[source] = true;
  distance[source] = 0;
  Q.push(source);

  while (!Q.empty()) {
    Vertex v = Q.front();
    Q.pop();
    for (EdgeIt e : out[v]) {
      Vertex _v = (e->src == v) ? e->src : e->dst; // required for
      Vertex _w = (e->src == v) ? e->dst : e->src; // undirected edges
      if (!explored[_w]) {
        explored[_w] = true;
        Q.push(_w);
        distance[_w] = distance[_v] + 1;
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

  cout << "Shortest distance between A & D = " << G.shortestDistance('A', 'D')
       << "\n";

  cout << "Shortest distance between A & Z = " << G.shortestDistance('A', 'Z')
       << "\n\n";
}