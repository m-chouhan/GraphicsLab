#include <stdlib.h>
#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

int Width=400,Height=400;
// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;
//float x = 0,y = 0;
// angle for rotating triangle
// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,y = 0.0f, z=30;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
      
      Width = w,Height = h;
        // Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

        // Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void draw2DFrame(void)
{
      glBegin(GL_LINES);
      glColor3f(0,1,0);
      for(int i = 0;i<20;i++)
      {
            glVertex3f(-10.0f+i, 10.0f, 0);
		glVertex3f(-10.0f+i, -10.0f,0);
		
            glVertex3f( -10.0f, -10.0f+i,0);
		glVertex3f( 10.0f, -10.0f+i, 0);

      }
      glEnd();
}

void renderScene(void) {
      
      angle += 0.02;
      x = 4*cos(angle);y = 4*sin(angle);
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Reset transformations
	glLoadIdentity();
      
      int up = 1;
      if ( z < 0 ) up = -1;
      
      gluLookAt(	0, 20, z,
                  0, 0,  0,
                  0.0f, up ,0.0f);

      glPushMatrix();
      glColor3f(0.5,1,0.5);
      glTranslatef(x,y,0);
      glutSolidSphere(1,20,20);
      glPopMatrix();
      
      glPushMatrix();
      glColor3f(1,0.5,0.5);
      glTranslatef(0,0,0);
      glutSolidSphere(2,20,20);
      glPopMatrix();

      draw2DFrame();
      /*      
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );*/
            /*Draw Background First*/

      glEnable(GL_DEPTH_TEST);
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key) {
		case GLUT_KEY_LEFT :
			break;
		case GLUT_KEY_RIGHT :
			break;
		case GLUT_KEY_UP :
                  z++;
			break;
		case GLUT_KEY_DOWN :
                  z--;
			break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(Width,Height);
	glutCreateWindow("Rotating Spheres");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
      
      glutMainLoop();
	// enter GLUT event processing cycle
	return 1;
}
