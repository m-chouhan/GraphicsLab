
#ifndef __SPHERE__
#define __SPHERE__

#include "Point3D.h"
#include "Shape.h"
#include <fstream>

class Sphere : public Shape
{            
      float radius;
      Shape::origin;
      public:
      
      Sphere(Point3D orig,float rad) { origin = orig;radius = rad; }
      Sphere(std::ifstream &in) { in>>origin;in>>radius;}
      
      //don't need complicated stuff here :P 
      void getAbsolutes(Shape &s)  { s = *this; };
      void Rotate(int xdeg,int ydeg,int zdeg) { };
       
      virtual void Scale(float S) {  radius *= S; };
      bool Collision(Shape &S);
      bool CollisionSelf(Sphere &S);
      //every shape should provide atleast one write method 
      void Write(std::ofstream &out) ;

      friend class Smasher;
      void setRad(float r) { radius = r;}
      float getRad(void )  { return radius; }
};

#endif 
