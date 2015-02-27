
/* Library for handling DCEL 
 * Author:Mahendra CHouhan (14CS60R12)
 */

#ifndef __DCEL__
#define __DCEL__

#include "Point3D.h"
#include <vector>
#include <assert.h>
#include <string.h>

class Vertex;
class Edge;
class Face;

class HalfEdge
{
      static int counter;
      public:
      int ID;
      HalfEdge() { ID = counter++; }
      Vertex *origin;
      HalfEdge *twin;
      HalfEdge *next,*prev;
      Face *face;
      Vertex *dest() { return twin->origin; }
};

typedef std::vector<Edge *> EdgeList;
typedef std::vector<HalfEdge *> HEdgeList;
typedef std::vector<Vertex> VerList;

class Face
{
      static int counter;
      public:
      int ID;
      HalfEdge *edge;
      Face() { ID = counter++; } 
};

class Edge
{
      static HEdgeList HEDGE_LIST;      
      public:
      Edge(Vertex *v1,Vertex *v2); 
};

class Vertex
{
      static int counter;
      enum{ ORPH,TERM,LINK };
      public:
      int ID;
      Point3D origin;
      HEdgeList out_edges; 
      //~ out_edges: edges pointing outwards
      //~ f: face to search
      //~ Each vertex has atmost 1 edge for a face in simple polygon graphs
      HalfEdge *searchEdge(Face *f);      
      Face *getCommonFace(Vertex *v);
      int getType();
      
      bool IsLinked(Vertex *v2);
      Vertex(Point3D o):origin(o) { ID = counter++;}
      Vertex & operator >> ( Vertex &V2 );
};

#endif
