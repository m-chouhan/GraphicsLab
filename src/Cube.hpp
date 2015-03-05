
#ifndef __CUBE__
#define __CUBE__

#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <vector>

#include "Point3D.h"
#include "Shape.h"
#include "Sphere.hpp"
#include "Smasher.hpp"

class Cube: public Shape
{
	Rect Faces[6];
	Shape::origin;
      float mass;
      int length,breadth,depth;
      
	public:

	friend class Smasher;
	friend bool CheckCollision(std::vector<Cube>&, Cube, std::vector<Cube> &);
	friend Point2D HandleCollision(std::vector<Cube> &,Cube ,std::vector<Cube> &);

	//length - along x axis
	//bredth - along y axis , depth - along z axis
	Cube(Point3D orig,int length,int breadth,int depth);
	Cube(const char *objfile)
	{
		std::ifstream in(objfile);
		int x=0,y=0,z=0;
		in>>length>>breadth>>depth>>x>>y>>z;
		std::cout<<"\nCube{"<<length<<breadth<<depth<<x<<y<<z<<"}\n";
		*this = Cube(Point3D(x,y,z),length,breadth,depth);
            
		in.close();	
	}
	Cube(int l)
	{
		*this = Cube(Point3D(),l,l,l);
	}
	Cube()
	{
		*this = Cube(Point3D(),0,0,0);
	}
	void Scale(float S);
	void Rotate(int Degx,int Degy,int Degz);
      
	//@Inline so that can be executed faster
	void getAbsolutes(Shape &S);      
	//~ A relative movement
      bool CollisionSelf( Cube &c) { return false;}
      
	bool Collision(Shape &S)
      {
            if( Cube *c = dynamic_cast<Cube *>(&S))
                  return CollisionSelf(*c);
            if(Sphere *s = dynamic_cast<Sphere*>(&S) )
                  return Smasher::Smash(*s,*this);
            return false;
      }
	//@doesnot projects hidden space
	//@standard write function inherited from shape class
	void Write(std::ofstream &out);
      	
      void write(const char *svgFile);
	//projects hidden faces
	void writeHidden(const char*svgFile);
	//~ returns projection at z = 0,
      //~ *stores initial z ordering of cube 
      Cube Project(Point3D viewPoint);
	//@Writes to ofstream and uses the id to determine vertex position
	void writeObj(std::ofstream &out,int ID);
};

#endif
