// Connected components in an undirected graph

#include "graph.h"

ConnectedComponents Graph::connectedComponents() {
  ConnectedComponents CC;
  ExplorationRecord explored;
  queue<VertexIt> Q;
  VertexIt v, w;

  int numCC = 0;
  for (const Vertex &i : V)
    if (!explored[i.val]) {
      explored[i.val] = true;
      numCC += 1;
      Q.push(V.find(i));
      while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        CC[numCC].push_back(v->val);
        for (EdgeIt e : v->out) {
          w = (e->src == v) ? e->dst : e->src;
          if (!explored[w->val]) {
            explored[w->val] = true;
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