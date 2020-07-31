// undirected graph

#include <iostream>
#include <iterator>
#include <set>
using namespace std;

typedef char Value;

struct Vertex;

struct Edge {
  set<Vertex>::iterator src, dst;
  Edge(const set<Vertex>::iterator _src, const set<Vertex>::iterator _dst)
      : src(_src), dst(_dst) {}
};

struct Vertex {
  Value val;
  mutable set<set<Edge>::iterator> inc; // incident edges
  Vertex(Value _val) : val(_val) {}
};

struct Graph {
  set<Vertex> V;
  set<Edge> E;
};

bool operator<(const Vertex &a, const Vertex &b) { return a.val < b.val; }
bool operator<(const Edge &a, const Edge &b) { return a.src->val < b.src->val; }
bool operator<(const set<Edge>::iterator a, const set<Edge>::iterator b) {
  return a->src->val <= b->src->val;
}
// bool operator==(const Edge &a, const Edge &b) { return a.src == b.src &&
// a.dst == b.dst; } bool operator==(const Vertex &a, const Vertex &b) { return
// a.val == b.val; }

auto addVertex(Graph &G, Value x) { return G.V.insert(x).first; }

void addEdge(Graph &G, Value x, Value y) {
  auto ix = addVertex(G, x);
  auto iy = addVertex(G, y);

  auto ie = G.E.emplace(ix, iy).first;
  ix->inc.insert(ie);
  iy->inc.insert(ie);
}

void removeVertex(Graph &G, Value x) {
  /*
    for (auto &e : G.E) {
      if (e.src->val == x) {
        e.dst->inc.erase();
      }

      else if(e.dst->val == x) {
        e.src->inc.erase()
      }
    }
    G.V.erase(G.V.find(x));
    cout << " ";
  */
}

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

  cout << "Front: " << G.V.begin()->val << "\n";
  cout << "Back: " << (--G.V.end())->val << "\n";

  cout << "\n";

  for (auto e : G.E) {
    cout << e.src->val << " - " << e.dst->val << "\n";
  }

  cout << "\n";

  for (auto v : G.V) {
    cout << "[" << v.val << "]: ";
    for (auto e : v.inc) {
      Value adj = (v.val == e->src->val) ? e->dst->val : e->src->val;
      cout << adj << " ";
    }
    cout << "\n";
  }
}
