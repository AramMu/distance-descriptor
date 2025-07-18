#include "edge.h"

Edge::Edge() {}
Edge::Edge (int u, int v, double w) : u(u), v(v), w(w) {}
bool Edge::operator < (const Edge& e) const {
    return w < e.w;
}

Vertex::Vertex() {}
Vertex::Vertex (int u, double w) : u(u), w(w) {}
bool Vertex::operator < (const Vertex& v) const {
    return w < v.w;
}

bool Vertex::IsGreater::operator () (const Vertex& v1, const Vertex& v2) {
    return v1.w > v2.w;
}

