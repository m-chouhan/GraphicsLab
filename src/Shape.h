
/* Contains Abstract Shape class and corresponding Rect  classes
 * Author:Mahendra Chouhan(14CS60R12)
 */ 

#ifndef __SHAPE__
#define __SHAPE__
 
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"

/*Parent Shape class for all shapes
 * any new shape must inherit this
 * Note: All movement must be relative to origin
 * if absolute values are needed than compute using getAbs()
 * */
class Shape
{
      public:
      Point3D origin;
      //stores the rotation around each axis (not required for now)
      int degX,degY,degZ;
      
      //generate absolute values of shape (if required)  
      virtual void getAbsolutes(Shape &) = 0;
      virtual void Rotate(int,int,int)= 0;
      virtual void Scale(float)= 0;
      
      //~ Absolute To World Space
      virtual void Move(Point3D & P) { origin = P;}
     //~ Relative To Current coordinates in world space
      virtual void Translate(Point3D &P) { origin = origin + P; }
      virtual bool Collision(Shape &)= 0;
      //every shape should provide atleast one write method 
      virtual void Write(std::ofstream &out) = 0;
      Point3D getOrigin() { return origin; }
      
      //Smasher class handles collision between different 'shapes' so it needs to access the origin
      friend class Smasher;
};

class Rect:private Shape
{
      Point3D Points[4];
      public:
      friend class Cube;
      friend class Smasher;
      friend bool CheckCollision(std::vector<class Cube> &,class Cube ,std::vector<class Cube> &);
      friend Point2D HandleCollision(std::vector<class Cube> &,class Cube ,std::vector<class Cube> &);

      Rect() {}
      Rect(Point3D origin,Point3D p0,Point3D p1,Point3D p2,Point3D p3)
      {
            this->origin = origin;
            Points[0] = p0;Points[1] = p1;
            Points[2] = p2;Points[3] = p3;
      }
      Point3D getOrigin() { return origin;}
      void setOrigin(Point3D P) { origin = P; }
      Point3D * getPoints() { return Points;}
      //@not implemented
      //~ Rect(Point3D origin,int orientation,int length,int breadth)
      /*use the file extension in write to call different write functions*/
      //void Write(char *file) {}
      void getAbsolutes(Shape &S) {}
      void Write(std::ofstream &out);    
      bool isAbove(Rect &R2)
      {
            return (R2.origin.z < origin.z);
      }
      //Not implemented
      void Rotate(int Degx,int Degy,int Degz) {}
      void Scale(float S){}
      
      bool Collision(Shape &S)
      {
            //@if( dynamic_case<Cube
            return false;
      }
      bool CollisionSelf(Rect &R2) ;  

      void Translate(Point3D P)
      {
            for(int i = 0;i<4;++i) Points[i] = Points[i] + P;
            origin = origin + P;
      }
      bool check_inside(Point3D q);
};

#endif

