// undirected graph

#include <iostream>
#include <iterator>
#include <list>
using namespace std;

typedef char Value;

struct Vertex;

struct Edge {
  list<Vertex>::iterator src, dst;
  Edge(list<Vertex>::iterator src, list<Vertex>::iterator dst)
      : src(src), dst(dst) {}
};

struct Vertex {
  Value val;                      // vertex value
  list<list<Edge>::iterator> inc; // incident edges
  Vertex(Value val) : val(val) {} // constructor
};

struct Graph {
  list<Vertex> V;
  list<Edge> E;
};

bool operator<(const Vertex &a, const Vertex &b) { return a.val < b.val; }
bool operator==(const Vertex &a, const Vertex &b) { return a.val == b.val; }
// bool operator<(const Edge& a, const Edge& b) { return; }

auto addVertex(Graph &G, Value x) {
  auto ix = G.V.emplace(G.V.cend(), x);
  // G.V.unique();
  G.V.sort();

  return ix;
}

auto addEdge(Graph &G, Value x, Value y) {
  auto ix = addVertex(G, x);
  auto iy = addVertex(G, y);

  auto ie = G.E.emplace(G.E.cend(), ix, iy);
  ix->inc.push_back(ie);
  iy->inc.push_back(ie);

  return ie;
}

void removeVertex(Graph &G, Value x) {}

void removeEdge(Graph &G, Value x, Value y) {}

int main() {
  Graph G;
  addVertex(G, 'B');
  addVertex(G, 'A');
  addVertex(G, '9');
  addEdge(G, 'B', '4');
  addEdge(G, 'D', '9');
  addEdge(G, 'A', '9');
  
  cout << "\n";

  cout << "Front: " << G.V.front().val << "\n";
  cout << "Back:" << G.V.back().val << "\n";

  cout << "\n";

  for (auto e: G.E) {
    cout << e.src->val << " - " << e.dst->val << "\n";
  }

  cout << "\n";

  for (auto v: G.V) {
    cout << "[" << v.val << "]: ";
    for (auto e : v.inc) {
      Value adj = (v.val == e->src->val) ? e->dst->val : e->src->val;
      cout << adj << " ";
    }
    cout << "\n";
  }
}
