
/* Polygon :
 *    Takes input points from inpoints.txt ( clokwise direction ) 
 *    and calculates if the points form a polygon or not
 *    Author:Mahendra Chouhan(14CS60R12)
 * */

#include <iostream>
#include "src/Point3D.h"
#include "src/graphics.h"
#include "src/Dcel.hpp"

using namespace std;

bool CheckPolygon(PointList2D &list)
{
      
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
            cout<<"\nSimple Polygon Found\n";
      return true;      
}

void Traingulate(PointList2D &list)
{
                  
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
            P = P + orig;
            list.push_back(P);
            vlist.push_back(Vertex(P));
            //cout<<P<<endl;
      } 
            
      for(int i = 1;i<vlist.size();++i)
      {
            vlist[i-1]>>vlist[i];
      }
      
      
      if( CheckPolygon(list) )
      {
            //~ vector<PointList2D> bgraph =  GenVertexCover(list);
            //~ SelectMinCover(bgraph);
            Traingulate(list);;
      }      
      
      out<<"</svg>\n";
    	out.close();

      return 0;
}
