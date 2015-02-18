
#include <iostream>
#include "src/Point3D.h"
#include "src/graphics.h"

using namespace std;

int main(int argc,char *argv[])
{
      PointList list;
      ifstream in("inpoints.txt");
      Point2D P(100,0);
      
      while(in>>P)
      {
            list.push_back(P);
            cout<<P<<endl;
      } 
      
      int sz = list.size();
      float sum = 0,sumR = 0,target = (sz-2)*180;
      
      for(int i = 0;i<sz;++i)
      {
            int two = (i+1) % sz,three = (i+2) % sz;
            
            Vector2D front = list[three] - list[two];
            Vector2D back = list[two] - list[i];
            Vector2D backrev = back*-1;
            float turn =  front.angleX() - back.angleX();//normR(v2.angleX()) - normR(v1.angleX());
                        
            float angle = front^(backrev);
            if (angle == 0) angle = PI;
            if(turn > 0 ) 
            {
                  float f = Deg(front.angleX());
                  float b = Deg(back.angleX());
                  if(  f>= 90 &&  b<= -90) ;     
                  else angle = 2*PI - angle;//take larger angle
            }      
                  
            
            sumR += angle;
            sum = Deg(sumR);
                  
            cout<<"["<<two<<","<<Deg(front^back)<<","<<Deg(angle)<<"]\t";
      }
      
      //cout<<endl<<target<<":"<<sz<<":"<<sumR<<":"<<Rad(target)<<endl;
      if( (sum < target+2) && (sum > target-2) ) 
            cout<<"\tSimple Polygon Found\n";
            
      cout<<endl<<sum<<endl;
      return 0;
}
