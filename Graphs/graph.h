#include <bits/stdc++.h>
using namespace std;

typedef char Vertex;

struct Edge {
  Vertex src, dst; // source and destination

  Edge(Vertex s, Vertex d) : src(s), dst(d) {}
  bool operator<(const Edge &other) const {
    return src == other.src ? dst < other.dst : src < other.src;
  }
};

typedef set<Edge>::iterator EdgeIt; // similar to edge pointers
bool operator<(const EdgeIt &a, const EdgeIt &b) { return *a < *b; }

typedef unordered_map<Vertex, bool> ExplorationRecord;
typedef unordered_map<Vertex, float> DistanceRecord;
typedef unordered_map<int, vector<Vertex>> ConnectedComponents;

struct Graph {
  set<Vertex> V;
  set<Edge> E;

  unordered_map<Vertex, set<EdgeIt>> inc;
  unordered_map<Vertex, set<EdgeIt>> out;

  // supported operations (in separate files)
  ExplorationRecord BFS(Vertex source);
  ExplorationRecord DFS(Vertex source);
  void DFS_rec(Vertex source, ExplorationRecord &explored);
  float shortestDistance(Vertex source, Vertex target);
  ConnectedComponents connectedComponents();

  void printAdjList();
};

struct UndirectedGraph : public Graph {
  void addVertex(Vertex x) { V.insert(x); }

  void addEdge(Vertex x, Vertex y) {
    if (V.find(x) == V.end())
      V.insert(x);
    if (V.find(y) == V.end())
      V.insert(y);

    if (E.find({x, y}) == E.end() && E.find({y, x}) == E.end()) {
      EdgeIt ie = E.insert({x, y}).first;
      out[x].insert(ie);
      out[y].insert(ie);
    }
  }

  void removeVertex(Vertex x) {
    if (V.find(x) != V.end()) {
      for (EdgeIt e : out[x]) {
        Vertex y = (e->src == x) ? e->dst : e->src;
        out[y].erase(e);
        E.erase(e);
      }
      V.erase(x);
    }
  }

  void removeEdge(Vertex x, Vertex y) {
    EdgeIt ie;
    if ((ie = E.find({x, y})) != E.end() || (ie = E.find({y, x})) != E.end()) {
      out[x].erase(ie);
      out[y].erase(ie);
      E.erase(ie);
    }
  }
};

struct DirectedGraph : public Graph {
  void addVertex(Vertex x) { V.insert(x); }

  void addEdge(Vertex x, Vertex y) {
    if (V.find(x) == V.end())
      V.insert(x);
    if (V.find(y) == V.end())
      V.insert(y);

    if (E.find({x, y}) == E.end()) {
      EdgeIt ie = E.insert({x, y}).first;
      out[x].insert(ie);
      inc[y].insert(ie);
    }
  }

  void removeVertex(Vertex x) {
    if (V.find(x) != V.end()) {
      for (EdgeIt e : inc[x]) {
        out[e->src].erase(e);
        E.erase(e);
      }
      V.erase(x);
    }
  }

  void removeEdge(Vertex x, Vertex y) {
    EdgeIt ie;
    if ((ie = E.find({x, y})) != E.end() || (ie = E.find({y, x})) != E.end()) {
      out[x].erase(ie);
      inc[y].erase(ie);
      E.erase(ie);
    }
  }
};

void Graph::printAdjList() {
  cout << "\n_Adjacency List_____\n";
  for (Vertex v : V) {
    cout << "\n [" << v << "]: ";
    for (EdgeIt e : out[v]) {
      Vertex y = (v == e->src) ? e->dst : e->src;
      cout << y << " ";
    }
  }
  cout << "\n____________________\n\n";
}
