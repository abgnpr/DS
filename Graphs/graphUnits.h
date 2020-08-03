#include <bits/stdc++.h>
using namespace std;

typedef char Value;

struct Vertex;
struct Edge;
typedef set<Vertex>::iterator VertexIt;
typedef set<Edge>::iterator EdgeIt;

typedef map<Value, bool> ExplorationRecord;
typedef map<Value, float> DistanceRecord;
typedef map<int, vector<Value>> ConnectedComponents;

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

bool operator<(const EdgeIt &a, const EdgeIt &b) { return *a < *b; }
