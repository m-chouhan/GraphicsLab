
/* Polygon :
 *    make using "make polygon"
 *    Takes input points from inpoints.txt ( clokwise direction ) 
 *    and calculates if the points form a polygon or not
 *    Output: Traingulated Dcel structure displayed in polygon.svg file
 *    Author:Mahendra Chouhan(14CS60R12)
 * */

#include <iostream>
#include "src/Point3D.h"
#include "src/Segments.hpp"
#include "src/graphics.h"
#include "src/Dcel.hpp"

#define SPLIT 0
#define MERGE 1
#define HELPER 2
#define NORMAL 10

using namespace std;

struct MyCustomList
{
      int ID; 
      vector<int> list; 
};

typedef vector<MyCustomList> BiparteGraph;


/*Brute Force method for checkpolygon*/
bool CheckPolygon(VerList &list)
{
      float total = 0;
      int size = list.size();
      
      for(unsigned int i = 0;i<size;++i)
      {
            int two = (i+1) % size,three = (i+2) % size;

            Point3D p1 = list[i].origin,p2 = list[two].origin,p3 = list[three].origin;
            
            float angle = interiorClockwise(p1,p2,p3);
            total+= angle;
      }
      
      cout<<"Interior Angle:"<<Deg(total)<<endl;
      
      HEdgeList &H = Edge::HEDGE_LIST;      
      for(unsigned int i = 0;i<H.size();++i)
      {
            for(unsigned int j = 0;j<i;++j)
                  if(H[i]->intersect(H[j])) return false;
      }      
      return true;      
}

//~ returns true if its OK to connect vertices v1 &v2 i.e
//~ no previous edges interescects this new edge
bool Connect(Vertex *v1,Vertex *v2)
{     
      for(unsigned int i = 0;i<v1->out_edges.size();++i)
      {
            if( v2 == v1->out_edges[i]->dest() ) return false;
      }
                         
      Line L(*v1,*v2);
      HEdgeList &H = Edge::HEDGE_LIST;
      Point3D p;
      for(unsigned int i = 0 ;i<H.size();++i)
      {
            Vertex *v3 = H[i]->dest(),*v4 = H[i]->origin;
            Line l(*v3,*v4);
            
            if( L.intersect(l,p) ) 
            {
                  if( p == v1->origin || p == v2->origin || p == v3->origin || p == v4->origin )
                        continue;                  
                  return false;
            }
      }
      return true;
}

int getType( Vertex *v1,Vertex*v2,Vertex *v3 )
{
      float angle = Deg(interiorClockwise(v1->origin,v2->origin,v3->origin));
      
      if( angle < 180 )
      {
            if( v1->origin.y < v2->origin.y && v3->origin.y < v2->origin.y ) return HELPER;
            if( v1->origin.y > v2->origin.y && v3->origin.y > v2->origin.y ) return HELPER;
            return NORMAL;
      }
      if( v1->origin.y < v2->origin.y && v3->origin.y < v2->origin.y ) return SPLIT;
      if( v1->origin.y > v2->origin.y && v3->origin.y > v2->origin.y ) return MERGE;
      
      assert(1); 
      return -100;     
}

void ResolveStack(vector<pair<int,Vertex*> > &Stack,vector<Vertex*> HelperStack)
{
      int size = Stack.size();
      if( size == 0 ) return;
      
      while( !Stack.empty() )
      {
            bool flag = true;
            pair<int,Vertex*> top = Stack.back();
            Stack.pop_back();
            for(int i = 0;i<Stack.size();++i)
            {
                  if(Connect(top.second,Stack[i].second))
                  {      
                        Edge(top.second,Stack[i].second);
                        Stack.erase( Stack.begin() + i );
                        flag = false;
                  }     
            }
            if(flag) 
            {            
                  Stack.push_back(top);
                  break;
            }
      }
      
      if ( !Stack.empty() )
      {
            bool flag = true;
            pair<int,Vertex*> top = Stack.back();
            Stack.pop_back();
            /*traverse Helperstack from top to bottom */
            for(int i = HelperStack.size()-1;i>=0;i--)
            {
                  if(Connect(top.second,HelperStack[i]))
                  {      
                        Edge(top.second,HelperStack[i]);
                        //Stack.erase( Stack.begin() + i );
                        flag = false;
                  }     
            }
            if(flag) 
                  Stack.push_back(top);            
      }
      
}

void BreakPolygon(VerList &vlist)
{
      vector<pair<int,Vertex*> > Stack;
      vector<Vertex*> HelperStack;
      
      Vertex *minY,*maxY;
      int maxId = 0;
      maxY = &vlist.front();//largest point first
      /**/      
      for(unsigned int i = 1;i<vlist.size();++i)
      {
            if( vlist[i].origin.y > maxY->origin.y ) 
            {
                  maxY = &vlist[i];
                  maxId = i;
            }
      }
      /**/
      if(maxId>0) maxId--;
      assert(maxY->out_edges.size() == 2);
      maxId = 0;      
      int size = vlist.size();
      for(unsigned int i = 0;i<size;++i)
      {
            int one = (i+maxId)%size,two = (i+1+maxId) % size,three = (i+2+maxId) % size;
            int type = getType(&vlist[one],&vlist[two],&vlist[three]);            
                              
            switch( type )
            {
                  case SPLIT:case MERGE:
                              //if( Stack.size() == 0 )
                              Stack.push_back(make_pair(type,&vlist[two]) );
                              break;
                              /*else 
                              {
                                    Vertex *top = Stack.back().second;
                                    if( connect(
                                    //if( Stack.front().first == MERGE )
                                    {
                                        Edge(Stack.front().second,&vlist[two]);  
                                        Stack.clear();
                                        Stack.push_back(make_pair(SPLIT,&vlist[two]));
                                    }    
                              }
                              break;
                  /*
                  case MERGE: 
                              if( Stack.size() == 0 )
                                    Stack.push_back(make_pair(MERGE,&vlist[two]) );
                              else 
                              {
                                    //if( Stack.front().first == MERGE )
                                    {
                                        Edge(Stack.front().second,&vlist[two]);  
                                        Stack.clear();
                                        Stack.push_back(make_pair(MERGE,&vlist[two]));
                                    }    
                              }
                              break;/**/
                  case HELPER: 
                              HelperStack.push_back(&vlist[two]);
                              break;
                  
                  case NORMAL:
                              if( !Stack.empty())
                              {
                                    pair<int,Vertex*> top = Stack.back();

                                    if(  (top.first == MERGE && vlist[two].origin.y < top.second->origin.y) ||
                                         (top.first == SPLIT && vlist[two].origin.y > top.second->origin.y)  )
                                    {
                                          if( Connect(top.second,&vlist[two]) ) 
                                          {
                                                Edge(top.second,&vlist[two]);  
                                                Stack.pop_back();
                                                HelperStack.push_back(&vlist[two]);
                                          }
                                    }
                              }
                              break;
            }
            ResolveStack(Stack,HelperStack);
      }
}

void Traingulate(Face *face)
{
      Vertex *minX,*maxX;
      minX = maxX = face->edge->origin;
      //~ Get min and maxX vertices (not required :/ ??)
      /*for(unsigned int i = 1;i<list.size();++i)
      {
            if( list[i].origin.x < minX->origin.x ) minX = &list[i];
            if( list[i].origin.x > maxX->origin.x ) maxX = &list[i];
      }
      minX = &list[0];*/
      //assert(minX->out_edges.size() == 2);
      
      //~ Dividing into monotone lines using forward & reverse
      
      HalfEdge *forward = face->edge,*rev = NULL;
      /*if( minX->out_edges[0]->face->ID == 0 )
      {
            forward = minX->out_edges[0];
      }
      else
      {     
            forward = minX->out_edges[1];
            assert(forward->face->ID == 0);            
      }*/
      rev = forward->prev;
      
      forward = forward->next;rev = rev->prev;            
      
      do{
            Vertex *Vup = forward->origin,*Vdown = rev->dest();
            assert(Vup != Vdown);
            
            if( Connect(Vup,Vdown) ) 
            {
                  Edge(Vup,Vdown);
                  forward = forward->next;
            }
            else  //Decrement forward also because only one increment should be done per connect() == true
            { rev = rev->prev; forward = forward->prev; }
            
      }while( forward->dest() != rev->origin );//while both don't have same destination
      //~ !! not true for unconnected graph
      
}

int main(int argc,char *argv[])
{
      PointList2D list;
      VerList vlist;
      ifstream in("i.txt");
      ofstream out("polygon.svg");    
      out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"1000\" width=\"1500\">\n";

      Point3D P(100,0,0),orig(500,500,0);

      while(in>>P)
      {
            list.push_back(P);
            vlist.push_back(Vertex(P));
            cout<<P<<endl;
      } 
            
      for(unsigned int i = 1;i<vlist.size();++i)
      {
            vlist[i-1]>>vlist[i];
      }
      vlist.back()>>vlist.front();
      
      assert(Edge::HEDGE_LIST.size() == vlist.size() );
      
      writeDcel(Edge::HEDGE_LIST,out);
      
      HalfEdge *e = vlist[0].out_edges[0];
      
      while ( e->next != NULL && e->next != vlist[0].out_edges[0] )
      {
            cout<<e->ID<<"("<<e->face->ID<<")"<<"=>";
            e = e->next;
      }
      cout<<e->ID<<"("<<e->face->ID<<")\n";
      
      e = e->twin;
      while ( e->next != NULL && e != vlist[0].out_edges[0]->twin )
      {
            cout<<e->ID<<"("<<e->face->ID<<")"<<"=>";
            e = e->next;
      }
      cout<<e->ID<<"("<<e->face->ID<<")\n";
      
      if( CheckPolygon(vlist) )
      {
            cout<<"\n{Polygon Found}\nEnter t to traingulate and b to break the polygon";
            char c;
            cin >> c;
            if(c == 'b') BreakPolygon(vlist);
            
            if(c == 't') Traingulate(Face::Faces[1]);
            //Traingulate(Face::Faces[0]);
      } /**/     
      else cout<<"{Not A Polygon}"<<endl;
            
      writeDcel(Edge::HEDGE_LIST,out);
      writeDcel(vlist,out);

      out<<"</svg>\n";
    	out.close();

      return 0;
}
