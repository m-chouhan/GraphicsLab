
#ifndef __DCEL__
#define __DCEL__

#include "Point3D.h"
#include <vector>

struct Vertex;
struct Edge;
struct Face;

typedef std::vector<Edge *> EdgeList;

struct Vertex
{
      Point3D origin;
      EdgeList edges;
};

struct Edge
{
      Edge e;
};

#endif
