/*
 * Graphics Library for my projects :P
 * Author: Mahendra Chouhan (14CS60R12)
 * */
#include <stdlib.h>
#include <time.h> 
#include <math.h>
#include "Shape.cpp"

//~ TODO: Generate gaussian distrubution
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
                
        std::cout<<"\nGaussian("<<x<<","<<y<<","<<s<<","<<Multi<<","<<log(s)<<")\n";
        //@P.x = rand() % 900+50;P.y = rand() % 900+50;
        return P;
}

bool CheckCollision(std::vector<Cube> world,Cube C)
{
      Cube c1,c2;
      C.getAbsolutes(c1);
      //~ for now the cubes are laying on floor so compare bottom faces i.e face[1] only
      for(std::vector<Cube>::iterator it =  world.begin();it != world.end();++it)
      {
            (*it).getAbsolutes(c2);
            if( c1.Faces[1].CheckCollision(c2.Faces[1])) 
                  return true;
      }
      return false;
}
