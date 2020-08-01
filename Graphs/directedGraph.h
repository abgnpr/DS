// directed graph

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
  mutable set<set<Edge>::iterator> inc; // incoming edges
  mutable set<set<Edge>::iterator> out; // outgoing edges
  Vertex(Value _val) : val(_val) {}
};

// operator overloads
bool operator<(const Vertex &a, const Vertex &b) { return a.val < b.val; }
bool operator<(const Edge &a, const Edge &b) { return a.src->val == b.src->val ? a.dst->val < b.dst->val : a.src->val < b.src->val; }
bool operator<(const set<Edge>::iterator a, const set<Edge>::iterator b) { return operator<(*a, *b); }

struct Graph {

  set<Vertex> V; // edge set
  set<Edge> E;   // vertex set

  auto addVertex(Value x) { return V.insert(x).first; }

  void addEdge(Value x, Value y) {
    auto ix = addVertex(x);
    auto iy = addVertex(y);
    if (E.find({ix, iy}) == E.end()) {
      auto ie = E.insert({ix, iy}).first;
      ix->out.insert(ie);
      iy->inc.insert(ie);
    }
  }

  void removeVertex(Value x) {
    auto ix = V.find(x);
    if (ix != V.end()) {
      for (auto e : ix->inc) {
        e->src->out.erase(e);
        E.erase(e);
      }
      V.erase(ix);
    }
  }

  void removeEdge(Value x, Value y) {
    auto ix = V.find(x);
    auto iy = V.find(y);
    auto ie = E.find({ix, iy});
    if (ie != E.end()) {
      ix->out.erase(ie);
      iy->inc.erase(ie);
      E.erase(ie);
    }
  }

  void printAdjList() {
    cout << "\n_Adjacency List_____\n";
    for (auto v : V) {
      cout << "\n [" << v.val << "]: ";
      for (auto e : v.out)
        cout << e->dst->val << " ";
    }
    cout << "\n____________________\n\n";
  }
};