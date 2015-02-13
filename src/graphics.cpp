/*
 * Graphics Library for my projects :P
 * Author: Mahendra Chouhan (14CS60R12)
 * */
#include "graphics.h"

Point3D getGaussianDistri(float sigX,float sigY,Point2D mean)
{
        Point3D P;
        
        double x = 0,y = 0,s = 0;
        do
        {
            x = rand() % 2000,y = rand() % 2000;
            x = x/1000;y = y/1000;
            s = x*x + y*y;            
        } while(s >= 1 || s == 0);   
        double Multi = sqrt( -2.0 * log(s) / s); 
        x*=Multi;y*=Multi;
        P.x = mean.x + sigX*x;P.y = mean.y + sigY*y;
                
        //@std::cout<<"\nGaussian("<<x<<","<<y<<","<<s<<","<<Multi<<","<<log(s)<<")\n";
        //@P.x = rand() % 900+50;P.y = rand() % 900+50;
        return P;
}
//conflicts contain objects in world colliding with C 
bool CheckCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts)
{
      conflicts.clear();
      Cube c1,c2;
      C.getAbsolutes(c1);
      bool flag = false;
      //~ for now the cubes are laying on floor so compare bottom faces i.e face[1] only
      for(std::vector<Cube>::iterator it =  world.begin();it != world.end();++it)
      {
            (*it).getAbsolutes(c2);
            if( c1.Faces[1].CollisionSelf(c2.Faces[1])) 
            {
                  flag = true;
                  conflicts.push_back(c2);
            }
      }
      return flag;
}
//@conflicts contain absolute values
Point2D HandleCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts)
{
      Cube temp;
      C.getAbsolutes(temp);
      Rect R1 = temp.Faces[1];
      Vector direction;
      for(int i = 0;i<conflicts.size();++i)
      {
            Rect R2 = conflicts[i].Faces[1];
            Vector2D dir = R1.origin - R2.origin;
            Vector2D r1 = R1.Points[0] - R1.origin,
                        r2 = R2.Points[0] - R2.origin;
            float mul = (r1.mod()+r2.mod())/dir.mod();
            dir = dir*mul*1.0;
            dir = R2.origin + dir;
            if( i == 0) direction = dir;
            else direction = direction + dir;//vector addition to calculate resultant dir
      }                  
      return direction;
}
