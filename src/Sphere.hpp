
#ifndef __SPHERE__
#define __SPHERE__

#include "Point3D.h"
#include "Shape.h"
#include <fstream>

class Sphere : public Shape
{            
      float radius;
      float mass;
      Shape::origin;
      public:
      
      Sphere(Point3D orig,float rad,float m) : radius(rad),mass(m)
      { 
            origin = orig;
      }
      
      Sphere(std::ifstream &in) { in>>origin;in>>radius; in>>mass;}
      
      //don't need complicated stuff here :P 
      void getAbsolutes(Shape &s)  { s = *this; };
      void Rotate(int xdeg,int ydeg,int zdeg) { };
       
      virtual void Scale(float S) {  radius *= S; };
      bool CollisionSelf( Sphere &s) ;
	bool Collision(Shape &S);
      void Write(std::ofstream &out) ;

      friend class Smasher;
      void setRad(float r) { radius = r;}
      float getRad(void )  { return radius; }
};

#endif 
