
//TODO: define Screen Size in graphics.h

/* Contains defination of Abstract Shape class and corresponding Rect and cube classes
 * Author:Mahendra Chouhan(14CS60R12)
 */ 
#include "graphics.h" 
#include "Shape.h"

bool Rect::CollisionSelf(Rect &R2)    
{   
      //@Assuming absolute values
      bool flag = false;
      for(int i = 0;i<4;++i)
      {
      flag = check_inside(R2.Points[i]) or 
            R2.check_inside(Points[i]) or flag;
      }
      flag = check_inside(R2.origin) or flag;
      return flag;
}

bool Rect::check_inside(Point3D q)
{
      Vector prev;
      for(int i = 0;i<4;++i)
      {
            Vector V = Points[(i+1)%4] - Points[i],
            Q = q - Points[i];
            Vector R = V.X(Q);//cross product

            if( i == 0) prev = R;

            if( (prev.z > 0 && R.z > 0) or
            (prev.z < 0 && R.z < 0) or (!prev.z ^ !R.z)) 
            prev = R;
            else return false;
      }	
      return true;
}

void Rect::Write(std::ofstream &out)
{
      //@Add origin to all points
      for(int i = 0;i<3;++i)
          writeLine(Points[i],Points[i+1],out);
      writeLine(Points[0],Points[3],out);
      writePoint(origin,out); 
}

