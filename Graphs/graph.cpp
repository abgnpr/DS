// undirected graph

#include <iostream>
#include <iterator>
#include <list>
#include <set>
using namespace std;

typedef char Value;

struct Vertex;
struct Edge;

struct Vertex {
    Value val;
    list<list<Edge>::iterator> inc;
};

struct Edge {
    list<Vertex>::iterator src, dst;
};

struct Graph {
    list<Vertex> V;
    list<Edge> E;
};

bool operator<(const Vertex& a, const Vertex& b) { return a.val < b.val; }
bool operator<(const Edge& a, const Edge& b) { return a.src->val < b.src->val; }
// bool operator<(const set<Edge>::iterator& a, set<Edge>::iterator& b) { }

auto addVertex(Graph& G, Value x)
{
    Vertex v;
    v.val = x;

    return G.V.insert(v); // try emplace
}

void addEdge(Graph& G, Value x, Value y)
{
    auto ix = addVertex(G, x).first;
    auto iy = addVertex(G, y).first;

    Edge e;
    e.src = ix;
    e.dst = iy;

    auto ie = G.E.insert(e).first;
    (*ix).inc.push_back(ie);
}

void removeVertex(Graph& G, Value x)
{
}

void removeEdge(Graph& G, Value x, Value y) {}

int main()
{
    Graph G;

    addVertex(G, 'A');
}
