#include <bits/stdc++.h>
using namespace std;

typedef char Value;

struct Vertex;
typedef set<Vertex>::iterator VertexIt;
struct Edge;
typedef set<Edge>::iterator EdgeIt;

typedef map<Value, bool> ExplorationRecord;
typedef map<Value, float> DistanceRecord;

// clang-format off

struct Vertex {
  Value val;
  mutable set<EdgeIt> inc; // incoming edges
  mutable set<EdgeIt> out; // outgoing edges

  Vertex(Value _val) : val(_val) {} // constructor
  bool operator<(const Vertex &other) const { return val < other.val; }
};

struct Edge {
  VertexIt src, dst; // source and destination
  
  Edge(VertexIt _src, VertexIt _dst) : src(_src), dst(_dst) {} // constructor
  bool operator<(const Edge &other) const { return src->val == other.src->val ? dst->val < other.dst->val : src->val < other.src->val; }
};

// clang-format on

bool operator<(const EdgeIt &a, const EdgeIt &b) { return *a < *b; }

struct Graph {
  set<Vertex> V; // edge set
  set<Edge> E;   // vertex set

  ExplorationRecord BFS(Value source) {
    ExplorationRecord explored;
    queue<VertexIt> Q;
    VertexIt v, dst;
    if ((v = V.find(source)) != V.end()) {
      explored[source] = true;
      Q.push(v);
      while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        for (EdgeIt e : v->out) {
          dst = (e->src == v) ? e->dst : e->src;
          if (!explored[dst->val]) {
            explored[dst->val] = true;
            Q.push(dst);
          }
        }
      }
    }

    return explored;
  }

  bool reachable(Value source, Value target) {
    ExplorationRecord explored = BFS(source);
    return explored[target];
  }

  float shortestDistance(Value source, Value target) {
    DistanceRecord distance;
    ExplorationRecord explored;
    queue<VertexIt> Q;
    VertexIt v, _src, _dst;

    for (const auto &v_ : V)
      distance[v_.val] = INFINITY;

    if ((v = V.find(source)) != V.end() && V.find(target) != V.end()) {
      explored[source] = true;
      distance[source] = 0;
      Q.push(v);
      while (!Q.empty()) {
        v = Q.front();
        Q.pop();
        for (EdgeIt e : v->out) {
          _src = (e->src == v) ? e->src : e->dst; // required for
          _dst = (e->src == v) ? e->dst : e->src; // undirected edges
          if (!explored[_dst->val]) {
            explored[_dst->val] = true;
            Q.push(_dst);
            distance[_dst->val] = distance[_src->val] + 1;
          }
        }
      }
    }

    return distance[target];
  }

  void DFS(Value source, ExplorationRecord &explored) {}
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

  void printAdjList() {
    cout << "\n_Adjacency List_____\n\n";
    for (const auto &v : V) {
      cout << " [" << v.val << "]: ";
      for (const auto &e : v.out) {
        VertexIt dst = (v.val == e->src->val) ? e->dst : e->src;
        cout << dst->val << " ";
      }
      cout << "\n";
    }
    cout << "____________________\n";
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

  void printAdjList() {
    cout << "\n_Adjacency List_____\n";
    for (const auto &v : V) {
      cout << "\n [" << v.val << "]: ";
      for (const auto &e : v.out)
        cout << e->dst->val << " ";
    }
    cout << "\n____________________\n\n";
  }
};
