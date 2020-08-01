// undirected graph

#include <iostream>
#include <iterator>
#include <set>
using namespace std;

typedef char Value;
struct Vertex;

struct Edge {
  set<Vertex>::iterator src, dst;
  Edge(set<Vertex>::iterator _src, set<Vertex>::iterator _dst)
      : src(_src), dst(_dst) {}
};

struct Vertex {
  Value val;
  mutable set<set<Edge>::iterator> inc; // incident edges
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
  if (G.E.find({ix, iy}) == G.E.end() && G.E.find({iy, ix}) == G.E.end()) {
    auto ie = G.E.insert({ix, iy}).first;
    ix->inc.emplace(ie);
    iy->inc.emplace(ie);
  }
}

void removeVertex(Graph &G, Value x) {
  auto ix = G.V.find(x);
  if (ix != G.V.end()) {
    for (auto e : ix->inc) {
      auto adj = (e->src == ix) ? e->dst : e->src;
      adj->inc.erase(e);
      G.E.erase(e);
    }
    G.V.erase(ix);
  }
}

void removeEdge(Graph &G, Value x, Value y) {
  auto ix = G.V.find(x);
  auto iy = G.V.find(y);

  auto ie = G.E.find({ix, iy});
  if (ie == G.E.end())
    ie = G.E.find({iy, ix});

  if (ie != G.E.end()) {
    ix->inc.erase(ie);
    iy->inc.erase(ie);
    G.E.erase(ie);
  }
}

void printAdjList(Graph &G) {
  cout << "\n_Adjacency List_____\n\n";
  for (auto v : G.V) {
    cout << " [" << v.val << "]: ";
    for (auto e : v.inc) {
      Value adj = (v.val == e->src->val) ? e->dst->val : e->src->val;
      cout << adj << " ";
    }
    cout << "\n";
  }
  cout << "____________________\n";
}
