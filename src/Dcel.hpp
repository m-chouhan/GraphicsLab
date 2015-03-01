
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
      bool intersect(HalfEdge *e);
};

typedef std::vector<Edge *> EdgeList;
typedef std::vector<HalfEdge *> HEdgeList;
typedef std::vector<Vertex> VerList;
typedef std::vector<Face *> FacesList;

class Face
{
      static int counter;
      public:
      static FacesList Faces;
      int ID;
      HalfEdge *edge;
      Face(HalfEdge *e) { ID = counter++;Faces.push_back(this);edge = e; } 
};

class Edge
{
      //HalfEdge *left,*right;??
      public:      
      static HEdgeList HEDGE_LIST;
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
      bool operator==(const Vertex &v2) const
      {
            return ( origin == v2.origin );
      }
      Vertex & operator >> ( Vertex &V2 );
};

void writeDcel(VerList &list,std::ofstream &out,const char * color = NULL);
void writeDcel(HEdgeList &list,std::ofstream &out,const char * color = NULL);
#endif
