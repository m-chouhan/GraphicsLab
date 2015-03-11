//TODO: define Screen Size in graphics.h

/*
 * Graphics Library for my projects :P
 * Author: Mahendra Chouhan (14CS60R12)
 * */
#ifndef __GRAPHICS__
#define __GRAPHICS__

#include <stdlib.h>
#include <time.h> 
#include <math.h>
#include <fstream>
#include <vector>
#include <deque>
#include <utility>
//ScreenSize
#define WIDTH 1500
#define HEIGHT 1200

#include "Point3D.h"
#include "Cube.hpp"
#include "Shape.h"

struct Color{ 
      float a,r,g,b; 
};

class FifoQ{
      
      public:
      std::deque<Point3D> Q;
      unsigned int SIZE ;
      int size;
      FifoQ(int size):SIZE(size),size(0) {}
      void Push(Point3D P)
      {
            if( Q.size() > SIZE )  Q.pop_front();
            Q.push_back(P);
            //for(int i = 0;i<Q.size();++i) std::cout<<Q[i];
      }
};

typedef std::pair<Shape *,FifoQ> element;
typedef std::vector<element> ShapeList2;

std::ifstream & operator >>(std::ifstream &in,Color &C);

Point3D getGaussianDistri(float sigX,float sigY,Point2D mean);
//conflicts contain objects in world colliding with C 
bool CheckCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts);
//@conflicts contain absolute values
Point2D HandleCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts);

#endif
