
#ifndef __SPHERE__
#define __SPHERE__

#include "Point3D.h"
#include "Shape.h"
#include "graphics.h"
#include <fstream>


class Sphere : public Shape
{            
      float radius;
      Shape::origin;
      Color col;
      public:
      
      Sphere() :radius(0) { mass = 0; };
      
      Sphere(Point3D orig,float rad,float m)       
      {
            radius = rad;
            mass = m;
            origin = orig;
      }
      
      //Sphere(std::ifstream &in) { in>>origin;in>>radius; in>>mass;}
      
      friend std::ifstream & operator >>(std::ifstream &in,Sphere &S)
      {
            in>>S.origin>>S.radius>>S.mass;
            in>>S.col;
            return in;
      }
      //don't need complicated stuff here :P 
      void getAbsolutes(Shape &s)  { s = *this; }
      void Rotate(int xdeg,int ydeg,int zdeg) { }       
      void Scale(float S) {  radius *= S; }
      
      void Draw() ;      
      bool CollisionSelf( Sphere &s) ;
	bool Collision(Shape &S);
      void Write(std::ofstream &out) ;

      friend class Smasher;
      void setRad(float r) { radius = r;}
      float getRad(void )  { return radius; }
};

#endif 
