
// pb1.cpp
// To compile: g++ pb1.cpp -lglut -lGLU -o pb1
// To run: ./pb1

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

float Y = 0.0;
int win;

void keyboard(unsigned char key,int x,int y)
{
      printf("%f",Y);
      if ( key == 'w' ) Y-= 0.1;
      
      if(key == 'q')
      {
            glutDestroyWindow(win);
            exit(0);
      } 
}

void renderScene(void) {
      
      glMatrixMode(GL_MODELVIEW);
      // clear the drawing buffer.
      glClear(GL_COLOR_BUFFER_BIT);

      // Red color used to draw.
      glColor3f(0.9, 0.3, 0.2); 
      
      glTranslatef(0,Y,0.5);
      /* 
      //rotation about X axis
      glRotatef(2.0,1.0,0.0,0.0);
      rotation about Y axis
      glScalef(1.0,1.0,1.0);
      /**/
      glutWireSphere(0.5,50,50); 
      //glutSolidSphere(0.2,200,200);
     
      glBegin(GL_LINE_LOOP);
      glColor3f(0, 1.0, 0.0); // yellow
      glVertex3f(-0.5, -0.5, -0.0);
      glVertex3f(0.5, 0.0, -0.0);
      glVertex3f(0.0, 0.5, -0.0);
      glEnd();
            
      glBegin(GL_LINE_LOOP);
      glColor3f(1.0, 1.0, 0.0); // yellow
      glVertex3f(0.0, 0.0,0); 
      glVertex3f(0.0, 3.0,0); 
      glVertex3f(4.0, 3.0,0); 
      glVertex3f(6.0, 1.5,0); 
      glVertex3f(4.0, 0.0,0);
      glEnd();
      /**/
      
      glFlush();

}

int main(int argc, char** argv) { 
      
      glutInit(&argc, argv);
      glutInitWindowPosition(100,100);
      glutInitWindowSize(800,600);
      //~GLUT_SINGLE: single buffer use DOUBLE for double buffer 
      //~ 
      glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
      win = glutCreateWindow("GLUT");
      glutDisplayFunc(renderScene);
      glutKeyboardFunc(keyboard); 
      glutMainLoop();
      return 0;
} 


