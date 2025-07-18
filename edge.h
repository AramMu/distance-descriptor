#ifndef EDGE_H
#define EDGE_H
#include <vector>

struct Edge {
    Edge();
    Edge (int u, int v, double w);

    bool operator < (const Edge& e) const;

    int u;
    int v;
    double w;
};

struct Vertex {
    Vertex ();
    Vertex (int u, double w);
    bool operator < (const Vertex& v) const;

    int u;
    double w;
    struct IsGreater {
        bool operator () (const Vertex& v1, const Vertex& v2);
    };
};

typedef std::vector <std::vector <double> > Graph;

#endif // EDGE_H
