
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include <assert.h>
#include <algorithm>

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
            
            Point2D points[2];
            int i = 0;
            Point2D p1= Point2D(0,C);
            Point2D p2 = Point2D((MY-C)/m,MY);
            Point2D p3 = Point2D(MX,m*MX+C);
            Point2D p4 = Point2D(-C/m,0);
            
            if( p1.y > 0 && p1.y < MY ) points[i++] = p1;
            if( p2.x > 0 && p2.x < MX) points[i++] = p2;
            if( p3.y > 0 && p3.y < MY) points[i++] = p3;
            if( p4.x > 0 && p4.x < MX) points[i++] = p4;
            assert(i == 2);
            Segment.UP = points[0];Segment.Down = points[1];
            
      } 
      bool contains(Point2D p)
      {
            if  ( ( a*p.x + b*p.y)  > c )  return !small;//if point is above the line
            return small;
      }
};

Point2D FindOptimalPoint( HalfPlane &plane,HPlanes &Array,int size,Equation e)
{
      if( size == 0 )
      {
            if( e.type && (e*plane.Segment.UP < e*plane.Segment.Down ) )
                  return plane.Segment.Down;
            //~ else if( e.type) return plane.Segment.UP;
            //~ else if( e*plane.Segment.UP < e*plane.Segment.Down )
                  return plane.Segment.UP;
            //~ return  plane.Segment.Down;    
      }
      
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
                  //~ if( e*optimal > e*P && !e.type )
                        //~ optimal = P;
            }
      }
      
      if( optimal == Point2D(-1,-1) ) return FindOptimalPoint(plane,Array,0,e);
      
      return optimal;
}

using namespace std;

HPlanes Array;
Point2D optimal;
      Equation e(5,6,MAXIMIZE);

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
      glPushMatrix();
      glTranslatef(optimal.x/norm,optimal.y/norm,0);
      glutSolidSphere(0.01,20,20);
      glPopMatrix();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {
            
      for( int i = 1;i<Array.size();i++)
      {
            if( Array[i].contains(optimal) ) continue;
            optimal = FindOptimalPoint(Array[i],Array,i,e);
      }
		//exit(0);
}

int main(int argc,char *argv[])
{
      glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(600,600);
	glutCreateWindow("HalfPlaneIntersection");
	glutDisplayFunc(renderScene);
	glutKeyboardFunc(processNormalKeys);
	glutIdleFunc(renderScene);

      //~ glutReshapeFunc(changeSize);

      
      Array.push_back(HalfPlane(-2,1,10,true));      
      Array.push_back(HalfPlane(1,1,60,true));
      Array.push_back(HalfPlane(-4,1,60,true));
      Array.push_back(HalfPlane(-0.5,1,20,true));
      //random_shuffle(Array.begin(),Array.end());
      
      //~ optimal=FindOptimalPoint(Array[0],Array,0,e);
      //~ for( int i = 1;i<Array.size();i++)
      //~ {
            //~ if( Array[i].contains(optimal) ) continue;
            //~ optimal = FindOptimalPoint(Array[i],Array,i,e);
      //~ }
      cout<<optimal<<endl;
      
      glutMainLoop();

      return 0;
}
