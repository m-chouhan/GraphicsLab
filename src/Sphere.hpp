
#ifndef __SPHERE__
#define __SPHERE__

#include <fstream>
#include <stdlib.h>
#include <GL/glut.h>

#include "Point3D.h"
#include "Shape.h"
#include "graphics.h"

class Sphere : public Shape
{            
      float radius;
      Shape::origin;
      public:
      
      Color col;
      bool light;
      int TextureID; //Texture Id for this sphere
      GLUquadric *Quad;

      int xdeg,ydeg,zdeg; //rotation along 3 axis
      
      Sphere() :radius(0),TextureID(0),light(false) 
      { 
            Quad = 0;
            xdeg = ydeg = zdeg = mass = 0; 
      }
      Sphere(Point3D orig,float rad,float m = 0,bool l = false)       
      {
            light = l;
            Quad = 0;TextureID = 0;
            Shape::size = radius = rad;
            if(m  == 0)             
                  mass = 10*radius*radius*radius;
            else mass = m;
            
            origin = orig;
            col.a =  ((float)(rand()%100))/100;
            col.r =  ((float)(rand()%100))/100;
            col.g =  ((float)(rand()%100))/100; 
            col.b =  ((float)(rand()%100))/100;
      }
      
      friend std::ifstream & operator >>(std::ifstream &in,Sphere &S)
      {
            in>>S.origin>>S.radius;
            S.size = S.radius; 
            in>>S.col;
            S.mass = 10*S.radius*S.radius*S.radius;
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
