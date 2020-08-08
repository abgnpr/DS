// Connected components in an undirected graph

#include "graph.h"

ConnectedComponents UndirectedGraph::connectedComponents() {
  ConnectedComponents CC;
  ExplorationRecord explored;
  queue<Vertex> Q;

  int numCC = 0;
  for (Vertex i : V)
    if (!explored[i]) {
      explored[i] = true;
      numCC += 1;
      Q.push(i);
      while (!Q.empty()) {
        Vertex v = Q.front();
        Q.pop();
        CC[numCC].push_back(v);
        for (EdgeIt e : out[v]) {
          Vertex w = (e->src == v) ? e->dst : e->src;
          if (!explored[w]) {
            explored[w] = true;
            Q.push(w);
          }
        }
      }
    }

  return CC;
}

int main() {
  UndirectedGraph G; // undirected graph only

  G.addEdge('A', 'B');
  G.addEdge('B', 'C');
  G.addEdge('C', 'D');
  G.addEdge('D', 'C');
  G.addEdge('9', 'D');
  G.addEdge('Z', 'x');
  G.addEdge('Z', 'z');
  G.addEdge('X', 'x');

  G.printAdjList();

  ConnectedComponents cc = G.connectedComponents();
  cout << "numCC = " << cc.size() << "\n";
  for (auto i = cc.begin(); i != cc.end(); ++i) {
    for (auto v : i->second)
      cout << v << " ";
    cout << "\n";
  }
}