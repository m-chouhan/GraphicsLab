
#include <iostream>
#include <GL/glut.h>
#include <vector>

#include "src/Point3D.h"
#include "src/Segments.hpp"

#define MAXIMIZE true

const float MX = 90,MY = 90;
const float norm = 100;

typedef std::vector<struct HalfPlane> HPlanes;

struct Equation
{
      float m1,m2; //only 2 variables needed for 2D equations
      bool type;
      Equation(float a,float b,bool t) { m1 = a,m2 = b,t = type;}
      float operator*(Point2D &P) { return m1*P.x + m2*P.y;}
};
//~ because equation also has only 2 parameters
struct HalfPlane
{
      float a,b,c;
      bool small;
      Line Segment;
      
      HalfPlane(float aa,float bb,float C,bool s)
      {
            a = aa,b = bb,c = C,small = s;
            float m = -a/b;
            C = c/b;
            
            if( C > 0)  Segment.UP = Point2D(0,C);
            else Segment.UP = Point2D(-C/m,0);
            
            float y = m*MX+C,x = (MY-C)/m;
            
            if(y < MY) Segment.Down = Point2D(MX,y);
            else Segment.Down = Point2D(x,MY);
      } 
      bool contains(Point2D p)
      {
            if  ( ( a*p.x + b*p.y)  > c )  return !small;//if point is above the line
            return small;
      }
};

Point2D FindOptimalPoint( HalfPlane &plane,HPlanes &Array,int size,Equation e)
{
      Point2D optimal(-1,-1);
      
      for(int i = 0;i<size;++i)
      {
            Point2D P;
            if( plane.Segment.intersect(Array[i].Segment,P) )
            {
                  if(optimal == Point2D(-1,-1) )
                        optimal = P; 
                  if( e*optimal < e*P  && e.type) 
                        optimal = P;
                  if( e*optimal > e*P && !e.type )
                        optimal = P;
            }
      }
      return optimal;
}

using namespace std;

HPlanes Array;

void renderScene()
{
      //glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//~ glViewport(0, 0, w, h);
	//gluPerspective(45.0f, 1, 0.1f, 100.0f);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//~ gluLookAt(	0.0f, 0.0f,  10.0f,
			//~ 0.0f, 0.0f,  0.0f,
			//~ 0.0f, 1.0f,  0.0f);                  
      glColor3f(0,1,1);
      glBegin(GL_LINE_LOOP);
		glVertex3f(0,0, 0);
		glVertex3f(0,MY/norm, 0);
		glVertex3f(MX/norm,MY/norm, 0);
		glVertex3f(MX/norm,0,0);      
      glEnd();
      
	glBegin(GL_LINES);
      for(int i = 0;i<Array.size();++i)
      {
            Point2D u = Array[i].Segment.UP/norm,d = Array[i].Segment.Down/norm;
		glVertex3f(u.x,u.y, u.z);
		glVertex3f( d.x,d.y, d.z);
      }
	glEnd();
      
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int x, int y) {
		exit(0);
}

int main(int argc,char *argv[])
{
      glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");
	// register callbacks
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
      //~ glutReshapeFunc(changeSize);
      Equation e(5,6,MAXIMIZE);
      
      //Array.push_back(HalfPlane(10,10,10,true));
      Array.push_back(HalfPlane(-2,1,10,true));
      //cout<<H1.contains(Point2D(0,30));
      
      glutMainLoop();

      return 0;
}
