// directed graph

#include <iostream>
#include <iterator>
#include <set>
using namespace std;

typedef char Value;
struct Vertex;

struct Edge {
  set<Vertex>::iterator src, dst;
  Edge(set<Vertex>::iterator _src, set<Vertex>::iterator _dst) : src(_src), dst(_dst) {}
};

struct Vertex {
  Value val;
  mutable set<set<Edge>::iterator> inc; // incoming edges
  mutable set<set<Edge>::iterator> out; // outgoing edges
  Vertex(Value _val) : val(_val) {}
};

struct Graph {
  set<Vertex> V; // edge set
  set<Edge> E;   // vertex set
};

// operator overloads
bool operator<(const Vertex &a, const Vertex &b) { return a.val < b.val; }
bool operator<(const Edge &a, const Edge &b) { return a.src->val == b.src->val ? a.dst->val < b.dst->val : a.src->val < b.src->val; }
bool operator<(const set<Edge>::iterator a, const set<Edge>::iterator b) { return operator<(*a, *b); }

auto addVertex(Graph &G, Value x) { return G.V.insert(x).first; }

void addEdge(Graph &G, Value x, Value y) {
  auto ix = addVertex(G, x);
  auto iy = addVertex(G, y);
  if (G.E.find({ix, iy}) == G.E.end()) {
    auto ie = G.E.insert({ix, iy}).first;
    ix->out.insert(ie);
    iy->inc.insert(ie);
  }
}

void removeVertex(Graph &G, Value x) {
  auto ix = G.V.find(x);
  if (ix != G.V.end()) {
    for (auto e : ix->inc) {
      e->src->out.erase(e);
      G.E.erase(e);
    }
    G.V.erase(ix);
  }
}

void removeEdge(Graph &G, Value x, Value y) {
  auto ix = G.V.find(x);
  auto iy = G.V.find(y);
  auto ie = G.E.find({ix, iy});
  if (ie != G.E.end()) {
    ix->out.erase(ie);
    iy->inc.erase(ie);
    G.E.erase(ie);
  }
}

void printAdjList(Graph &G) {
  cout << "\n_Adjacency List_____\n";
  for (auto v : G.V) {
    cout << "\n [" << v.val << "]: ";
    for (auto e : v.out)
      cout << e->dst->val << " ";
  }
  cout << "\n____________________\n\n";
}
