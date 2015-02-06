/*
 * Graphics Library for my projects :P
 * Author: Mahendra Chouhan (14CS60R12)
 * */
#include <stdlib.h>
#include <time.h> 
#include "Shape.cpp"

Point3D getGaussianDistri(float sigX,float sigY,float sigZ)
{
        Point3D P;
        P.x = rand() % 900+50;P.y = rand() % 900+50;
        //~ TODO: Generate gaussian distrubution
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
