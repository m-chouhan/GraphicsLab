
#ifndef __DCEL__
#define __DCEL__

#include "Point3D.h"
#include <vector>



class Vertex;
class Edge;
class Face;

struct HalfEdge
{
      Vertex *origin;
      HalfEdge *twin;
      HalfEdge *next,*prev;
      Face *face;
};

typedef std::vector<Edge *> EdgeList;
typedef std::vector<HalfEdge *> HEdgeList;
typedef std::vector<Vertex> VerList;

class Edge
{
      static HEdgeList HEDGE_LIST;
      
      public:
      Edge(Vertex *v1,Vertex *v2); 
};


struct Vertex
{
      public:
      Point3D origin;
      HEdgeList out_edges; 
      //~ out_edges: edges pointing outwards
      Vertex(Point3D o):origin(o) { }
      Vertex & operator >> ( Vertex &V2 )
      {
            for(int i = 0;i<out_edges.size();++i)
            {     
                  if( V2.out_edges[i]->twin->origin == this )
                  {      
                        std::cout<<"\nAlready Connected\n";
                        return V2;
                  }
            }
            
            Edge(this,&V2);             
            return V2;
      }
      //~ Vertex & operator => ( Edge &e )
      //~ {
      //~ }
      
};

HEdgeList Edge::HEDGE_LIST;
Edge::Edge(Vertex *v1,Vertex *v2)
{
      HalfEdge *e1 = new HalfEdge();
      HalfEdge *e2 = new HalfEdge();
      
      e1->twin = e2;e2->twin = e1;
      e1->origin = v1;e2->origin = v2;
      v1->out_edges.push_back(e1);
      v2->out_edges.push_back(e2);
            
      HEDGE_LIST.push_back(e1);
      HEDGE_LIST.push_back(e2);
}      


class Face
{
      public:
      static int counter;
      int ID;
      Edge *edge;
      Face() { ID = counter++; } 
};

int Face::counter = 0;

#endif
