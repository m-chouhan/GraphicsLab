
/* Polygon :
 *    Takes input points from inpoints.txt ( clokwise direction ) 
 *    and calculates if the points form a polygon or not
 *    Author:Mahendra Chouhan(14CS60R12)
 * */

#include <iostream>
#include "src/Point3D.h"
#include "src/Segments.hpp"
#include "src/graphics.h"
#include "src/Dcel.hpp"

using namespace std;

bool CheckPolygon(VerList &list)
{
      HEdgeList &H = Edge::HEDGE_LIST;      
      for(unsigned int i = 0;i<H.size();++i)
      {
            for(unsigned int j = 0;j<i;++j)
                  if(H[i]->intersect(H[j])) return false;
      }
      /*
      int sz = list.size();
      float sum = 0,sumR = 0,target = (sz-2)*180;
      
      for(int i = 0;i<sz;++i)
      {
            int two = (i+1) % sz,three = (i+2) % sz;
            
            Vector2D front = list[three] - list[two];
            Vector2D back = list[two] - list[i];
            Vector2D backrev = back*-1;
            
            float f = Deg(front.angleX());
            float b = Deg(back.angleX());

            float turn =  front.angleX() - back.angleX();//normR(v2.angleX()) - normR(v1.angleX());
                        
            float angle = front^(backrev);
            if (angle == 0) angle = PI;
            if(turn > 0 ) 
            {
                  if(  f>= 0 &&  b<= -90) ;     
                  else angle = 2*PI - angle;//take larger angle
            }      
            if(turn < 0)
            {
                  //@float f = Deg(front.angleX());
                  //@float b = Deg(back.angleX());
                  if(  b>= 90 &&  f<= -90) angle = 2*PI - angle;     

            }                  
            sumR += angle;
            sum = Deg(sumR);
                  
            cout<<"["<<two<<","<<Deg(angle)<<"]\t";
      }
      
      cout<<endl<<"target:"<<target<<":"<<sz<<":sum="<<sum<<":"<<endl;
      if( (sum < target+2) && (sum > target-2) ) 
            cout<<"\nSimple Polygon Found\n";/**/
      return true;      
}

bool Connect(Vertex *v1,Vertex *v2)
{
      Line L(*v1,*v2);
      HEdgeList &H = Edge::HEDGE_LIST;
      Point2D p;
      
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

void Traingulate(VerList &list)
{
      Vertex *minX,*maxX;
      minX = maxX = &list.front();
      //~ Get min and maxX vertices (not required :/ ??)
      for(unsigned int i = 1;i<list.size();++i)
      {
            if( list[i].origin.x < minX->origin.x ) minX = &list[i];
            if( list[i].origin.x > maxX->origin.x ) maxX = &list[i];
      }
      
      assert(minX->out_edges.size() == 2);
      
      //~ Dividing into monotone lines using forward & reverse
      
      HalfEdge *forward = NULL,*rev = NULL;
      if( minX->out_edges[0]->face->ID == 0 )
      {
            forward = minX->out_edges[0];
      }
      else
      {     forward = minX->out_edges[1];
            assert(forward->face->ID == 0);            
      }
      rev = forward->prev;
            
      do{
            Vertex *Vup = forward->dest(),*Vdown = rev->origin;
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
      ifstream in("inpoints.txt");
      ofstream out("polygon.svg");    
      out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"1000\" width=\"1500\">\n";

      Point3D P(100,0,0),orig(500,500,0);

      while(in>>P)
      {
            list.push_back(P);
            vlist.push_back(Vertex(P));
            //cout<<P<<endl;
      } 
            
      for(unsigned int i = 1;i<vlist.size();++i)
      {
            vlist[i-1]>>vlist[i];
      }
      vlist.back()>>vlist.front();
      
      assert(Edge::HEDGE_LIST.size() == vlist.size() );
      
      writeDcel(Edge::HEDGE_LIST,out);
      //writeDcel(vlist,out);
      
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
      
      /*
      cout<<"\nAfter new edge\n";
      e = vlist[0].out_edges[1];
      while ( e->next != NULL && e->next != vlist[0].out_edges[1] )
      {
            cout<<e->ID<<"("<<e->face->ID<<")"<<"=>";
            e = e->next;
      }
      cout<<e->ID<<"("<<e->face->ID<<")\n";/**/

      if( CheckPolygon(vlist) )
      {
            cout<<"Polygon Found..."<<endl;
            //~ vector<PointList2D> bgraph =  GenVertexCover(list);
            //~ SelectMinCover(bgraph);
            Traingulate(vlist);;
      } /**/     
      else cout<<"Not A Polygon"<<endl;
      
      writeDcel(Edge::HEDGE_LIST,out);
      out<<"</svg>\n";
    	out.close();

      return 0;
}
