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
typedef forward_list<Vertex> Assortment;

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
      EdgeIt e = E.insert({x, y}).first;
      out[x].insert(e);
      out[y].insert(e);
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

  void removeEdge(EdgeIt e) {
    out[e->src].erase(e);
    out[e->dst].erase(e);
    E.erase(e);
  }

  void removeEdge(Vertex x, Vertex y) {
    EdgeIt e;
    if ((e = E.find({x, y})) != E.end() || (e = E.find({y, x})) != E.end()) {
      out[x].erase(e);
      out[y].erase(e);
      E.erase(e);
    }
  }

  ConnectedComponents connectedComponents();
};

struct DirectedGraph : public Graph {
  void addVertex(Vertex x) { V.insert(x); }

  void addEdge(Vertex x, Vertex y) {
    if (V.find(x) == V.end())
      V.insert(x);
    if (V.find(y) == V.end())
      V.insert(y);

    if (E.find({x, y}) == E.end()) {
      EdgeIt e = E.insert({x, y}).first;
      out[x].insert(e);
      inc[y].insert(e);
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

  void removeEdge(EdgeIt e) {
    out[e->src].erase(e);
    inc[e->dst].erase(e);
    E.erase(e);
  }

  void removeEdge(Vertex x, Vertex y) {
    EdgeIt e;
    if ((e = E.find({x, y})) != E.end() || (e = E.find({y, x})) != E.end()) {
      out[x].erase(e);
      inc[y].erase(e);
      E.erase(e);
    }
  }

  ConnectedComponents stronglyConnectedComponents();

  Assortment topoSort();
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
