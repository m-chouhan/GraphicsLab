/*
 *  Contains Point3d class and wrappers for writing points to file(.svg)
 *  Author: Mahendra Chouhan(14CS60R12)
 * */

#include "Point3D.h"

double Rad(float Deg) 
{
	return (3.14*Deg/180);
}
float Deg(float Rad)
{
      return (Rad*180/3.14);
}

double normR(double val)
{
      if(val < 0) return 2*PI + val;
      return val;
}
double normD(double val)
{
      if (val < 0) return 360 + val;
      else return val;
}

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

void writeLine(Point2D p1,Point2D p2,std::ofstream &out,const char *color)
{	
      if( color == NULL) color = RED;
      
	out<<"\n\t<line x1 = \""<<p1.x
	<<"\" y1 = \""<<p1.y 
	<<"\" x2 = \""<<p2.x
	<<"\" y2 = \""<<p2.y
	<<"\" style=\"stroke:"<<color<<";stroke-width:2\" />\n";
}

void writeLines(std::vector<Point2D> &P,std::ofstream &out,const char *color)
{
        for(std::vector<Point2D>::iterator it = P.begin();it != (P.end()-1);++it)
            writeLine(*it,*(it+1),out);
        //~ writeLine(P.front(),P.back(),out);            
}

void writePoint(Point2D P,std::ofstream &out,const char *color)
{
	out<<"\n\t<circle cx = \""<<P.x
	<<"\" cy = \""<<P.y 
	<<"\" r = \""<<2
	<<"\" stroke = \"black\" stroke-width = \"3\" />\n";
}

void writePoints(std::vector<Point2D> &P,std::ofstream &out,const char *color)
{
        for(std::vector<Point2D>::iterator it = P.begin();it != P.end();++it)
            writePoint(*it,out);
}
