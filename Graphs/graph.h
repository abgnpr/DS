#include "graphUnits.h"

struct Graph {
  set<Vertex> V; // edge set
  set<Edge> E;   // vertex set

  // supported operations split in separate files
  ExplorationRecord BFS(Value source);
  ExplorationRecord DFS(Value source);
  float shortestDistance(Value source, Value target);
  ConnectedComponents connectedComponents();
  
  void printAdjList();
};

struct UndirectedGraph : public Graph {
  VertexIt addVertex(Value x) { return V.insert(x).first; }

  void addEdge(Value x, Value y) {
    VertexIt ix = addVertex(x);
    VertexIt iy = addVertex(y);
    if (E.find({ix, iy}) == E.end() && E.find({iy, ix}) == E.end()) {
      EdgeIt ie = E.insert({ix, iy}).first;
      ix->out.insert(ie);
      iy->out.insert(ie);
    }
  }

  void removeVertex(Value x) {
    VertexIt ix = V.find(x);
    if (ix != V.end()) {
      for (EdgeIt e : ix->out) {
        VertexIt dst = (e->src == ix) ? e->dst : e->src;
        dst->out.erase(e);
        E.erase(e);
      }
      V.erase(ix);
    }
  }

  void removeEdge(Value x, Value y) {
    VertexIt ix = V.find(x);
    VertexIt iy = V.find(y);

    EdgeIt ie = E.find({ix, iy});
    if (ie == E.end())
      ie = E.find({iy, ix});

    if (ie != E.end()) {
      ix->out.erase(ie);
      iy->out.erase(ie);
      E.erase(ie);
    }
  }
};

struct DirectedGraph : public Graph {
  VertexIt addVertex(Value x) { return V.insert(x).first; }

  void addEdge(Value x, Value y) {
    VertexIt ix = addVertex(x);
    VertexIt iy = addVertex(y);
    if (E.find({ix, iy}) == E.end()) {
      EdgeIt ie = E.insert({ix, iy}).first;
      ix->out.insert(ie);
      iy->inc.insert(ie);
    }
  }

  void removeVertex(Value x) {
    VertexIt ix = V.find(x);
    if (ix != V.end()) {
      for (EdgeIt e : ix->inc) {
        e->src->out.erase(e);
        E.erase(e);
      }
      V.erase(ix);
    }
  }

  void removeEdge(Value x, Value y) {
    VertexIt ix = V.find(x);
    VertexIt iy = V.find(y);
    EdgeIt ie = E.find({ix, iy});
    if (ie != E.end()) {
      ix->out.erase(ie);
      iy->inc.erase(ie);
      E.erase(ie);
    }
  }
};

void Graph::printAdjList() {
  cout << "\n_Adjacency List_____\n";
  for (const auto &v : V) {
    cout << "\n [" << v.val << "]: ";
    for (const auto &e : v.out) {
      // required for undirected
      VertexIt dst = (v.val == e->src->val) ? e->dst : e->src;
      cout << dst->val << " ";
    }
  }
  cout << "\n____________________\n\n";
}
