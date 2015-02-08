/*
 *  Contains Point3d class and wrappers for writing points to file(.svg)
 *  Author: Mahendra Chouhan(14CS60R12)
 * */
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <vector>


double Rad(float Deg) 
{
	return (3.14*Deg/180);
}

typedef struct Point3D Vector;

struct Point3D
{
	float x;
	float y;
	float z;
	Point3D() { x = y = z = 0; }
	Point3D(int X,int Y,int Z) { x = X;y = Y;z = Z;}
	Point3D * Multiply(float Matrix[][4]);
	Point3D  X(Point3D p1);
	Point3D operator +(const Point3D &p1)
	{
		return Point3D(p1.x+x,p1.y+y,p1.z+z);
	}
      Point3D add(int X,int Y,int Z)
      {
        x+=X,y+=Y,z+=Z;
        return *this;
      }

      //~ dot product
      float operator *(const Point3D &P2) {
            return x*P2.x + y*P2.y + z*P2.z;
      }

      Point3D operator -(const Point3D &P)
      {
            return Point3D(x-P.x,y-P.y,z-P.z);
      }
      Point3D operator *(const float mul)
      {     
            return Point3D(x*mul,y*mul,z*mul);
      }
      bool operator <(const Point3D &P) const
      {
            return ( x < P.x);
      }

      friend std::ofstream & operator <<(std::ofstream &out,const Point3D &P)
      {
            out<<P.x<<" "<<P.y<<" "<<P.z;
            return out;
      }

      float angleX()
      {
        return atan2f(y,x);
      }
      float angleY()
      {
        return atan2f(x,y);
      }
    
};

Point3D Point3D::X(Point3D p)
{
	float X = y*p.z - p.y*z,
	      Y = -x*p.z + p.x*z,
	      Z = x*p.y - p.x*y;
	return Point3D(X,Y,Z);
}

Point3D * Point3D::Multiply(float  Matrix[][4])
{
	float temp[4] = {0};
	for(int i = 0;i<4;++i)
		temp[i] = x*Matrix[i][0] + y*Matrix[i][1] + z*Matrix[i][2];
	
    x = temp[0];y = temp[1]; z = temp[2];
    return this;
}

typedef struct Point2D Vector2D;
struct Point2D:Point3D
{
        Point2D(int X = 0,int Y=0)
        {  x = X;y = Y; z = 0;}
        Point2D(const Point3D &P)
        { x = P.x;y = P.y;z = 0;}
        
        //@returns magnitude of vector
        float mod()
        {
            return sqrt( x*x + y*y);
        }
        //Returns angle between two vectors    
        float operator ^(Point2D &P)
        {
            Point2D p = *this;
            return acosf( p*P/(p.mod() * P.mod()) ); 
        }
        
};

void writeLine(Point2D p1,Point2D p2,std::ofstream &out)
{	
	out<<"\n\t<line x1 = \""<<p1.x
	<<"\" y1 = \""<<p1.y 
	<<"\" x2 = \""<<p2.x
	<<"\" y2 = \""<<p2.y
	<<"\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n";
}

void writeLines(std::vector<Point2D> &P,std::ofstream &out)
{
        for(std::vector<Point2D>::iterator it = P.begin();it != (P.end()-1);++it)
            writeLine(*it,*(it+1),out);
        //~ writeLine(P.front(),P.back(),out);            
}

void writePoint(Point2D P,std::ofstream &out)
{
	out<<"\n\t<circle cx = \""<<P.x
	<<"\" cy = \""<<P.y 
	<<"\" r = \""<<2
	<<"\" stroke = \"black\" stroke-width = \"3\" />\n";
}

void writePoints(std::vector<Point2D> &P,std::ofstream &out)
{
        for(std::vector<Point2D>::iterator it = P.begin();it != P.end();++it)
            writePoint(*it,out);
}
