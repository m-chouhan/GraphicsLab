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

//ScreenSize
#define WIDTH 1500
#define HEIGHT 1200

#include "Cube.hpp"

struct Color{ 
      float a,r,g,b; 
};
std::ifstream & operator >>(std::ifstream &in,Color &C);

Point3D getGaussianDistri(float sigX,float sigY,Point2D mean);
//conflicts contain objects in world colliding with C 
bool CheckCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts);
//@conflicts contain absolute values
Point2D HandleCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts);

#endif
