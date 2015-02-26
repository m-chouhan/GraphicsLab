
#ifndef __DCEL__
#define __DCEL__

#include "Point3D.h"
#include <vector>
#include <assert.h>


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
int HalfEdge::counter = 0;

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

int Face::counter = 0;

class Edge
{
      static HEdgeList HEDGE_LIST;      
      public:
      Edge(Vertex *v1,Vertex *v2); 
};
HEdgeList Edge::HEDGE_LIST;


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
      HalfEdge *searchEdge(Face *f)
      {
            for(int i = 0;i<out_edges.size();++i)
                  if( f == out_edges[i]->face ) return out_edges[i];
            return NULL;      
      }
      
      Face *getCommanFace(Vertex *v)
      {
            for( int i = 0;i<out_edges.size();++i)
                  for( int j = 0; j < v->out_edges.size() ; ++j)
                  { 
                        if(out_edges[i]->face == out_edges[j]->face)
                              return out_edges[i]->face;
                  }
            return NULL;
      }
      
      int getType()
      {
            switch(out_edges.size())
            {
                  case 0: return ORPH;
                  case 1: return TERM;
                  default: return LINK;
            } 
      }
      
      bool IsLinked(Vertex *v2)
      {
            HalfEdge *e = out_edges[0];
            while( e->next != NULL && e->next != out_edges[0]) 
            {
                  //~ Careful!! can lead to infinite loop
                  e = e->next;
                  if( e->origin == v2 ) return true;
            }
            return false;
      }
      Vertex(Point3D o):origin(o) { ID = counter++;}
      Vertex & operator >> ( Vertex &V2 )
      {
            /*Idiot proofing *
            for(int i = 0;i<V2.out_edges.size();++i)
            {     
                  if( V2.out_edges[i]->twin->origin == this )
                  {      
                        std::cout<<"\nAlready Connected\n";
                        return V2;
                  }
            }*/
            /*
            if( getType() == ORPH && V2.getType() == ORPH )
            {
                  Edge(this,&V2);
            }
            if( getType() == ORPH && V2.getType() == TERM )
            {
                  Edge(&V2,this);
            }
            if( getType() == TERM && V2.getType() == ORPH )
            {
                  Edge(this,&V2);
            }
            if( getType() == TERM && V2.getType() == TERM )
            {
                  //~ check for loops if true make new face
                  if(IsLinked(&V2))
                  {
                        Face *f = new Face();
                        Edge(this,&V2);
                        Edge *e = out_edges[0]->next;
                        while( e != out_edges[0]
                  }
            }
            
            if( getType() == LINK && V2.getType() == LINK );
            */
            
            if( getType() == ORPH && V2.getType() == TERM )
            {
                  Edge(&V2,this);
            }
            else Edge(this,&V2);
            
            return V2;
      }
};
int Vertex::counter = 0;

Edge::Edge(Vertex *v1,Vertex *v2)
{
      HalfEdge *e1 = new HalfEdge();
      HalfEdge *e2 = new HalfEdge();
      
      e1->twin = e2;e2->twin = e1;
      e1->origin = v1;e2->origin = v2;
      
      //Assume v2 is a orphan 
      if( v1->out_edges.size() == 0 ) //both are orphans no need to assign pre/next
      {
            Face *f = new Face();
            v1->out_edges[0]->face = v2->out_edges[0]->face = f;
            f->edge = v1->out_edges[0];     
      }
      else if ( v1->out_edges.size() == 1 && v2->out_edges.size() == 0 )
      {
            HalfEdge *e = v1->out_edges[0];
            e->prev = e2;e2->next = e;
            e = e->twin;
            e->next = e1;e1->prev = e;
            
            e1->face = e2->face = e->face;
      }
      else //link - link handling 
      {
            Face *f = v1->getCommanFace(v2);
            assert(f != NULL);
            
            e1->next = v2->searchEdge(f);
            e2->next = v1->searchEdge(f);
            
            e1->prev = e2->next->prev;
            e2->prev = e1->next->prev;
            
            e2->next->prev = e2->prev->next = e2;
            e1->next->prev = e1->prev->next = e1;
            
            f = new Face();
            for( HalfEdge *e = e1->next;e != e1;e = e->next)
                  e->face = f;
            e1->face = f;
            
      }
            
      v1->out_edges.push_back(e1);
      v2->out_edges.push_back(e2);
            
      HEDGE_LIST.push_back(e1);
      HEDGE_LIST.push_back(e2);
}      
#endif
