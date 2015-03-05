#include <stdlib.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

struct { int topX,topY,bottomX,bottomY;}
       SCREEN;
int Width=400,Height=400;
// all variables initialized to 1.0, meaning
// the triangle will initially be white
float red=1.0f, blue=1.0f, green=1.0f;
float x = 0,y = 0;
// angle for rotating triangle
float angle = 0.0f;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio =  w * 1.0 / h;
      
      SCREEN.topX = glutGet((GLenum)GLUT_WINDOW_X);
      SCREEN.topY = glutGet((GLenum)GLUT_WINDOW_Y); 
      SCREEN.bottomX = SCREEN.topX+w;
      SCREEN.bottomY = SCREEN.topY+h;
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

/* Callback handler for mouse event */
void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // Pause/resume
      
      int deltax = (SCREEN.bottomX-SCREEN.topX)/2;
      int deltay = (SCREEN.bottomY-SCREEN.topY)/2;
      ::x = x-Width/2,::y = y-Height/2;   
      cout<<"["<<::x<<","<<::y<<"]\n";
      /*paused = !paused;         // Toggle state
      if (paused) {
         xSpeedSaved = xSpeed;  // Save parameters for restore later
         ySpeedSaved = ySpeed;
         xSpeed = 0;            // Stop movement
         ySpeed = 0;
      } else {
         xSpeed = xSpeedSaved;  // Restore parameters
         ySpeed = ySpeedSaved;
      }*/
   }
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(	0.0f, 0.0f,  30.0f,
			0.0f, 0.0f,  0.0f,
			0.0f, 1.0f,  0.0f);

	glRotatef(angle, 0.0f, 0.0f, 1.0f);
      
      glutWireSphere(10,50,50); 

	glColor3f(red,green,blue);
	glBegin(GL_TRIANGLES);
            glColor3f(0.9, 0.3, 0.2); 
		glVertex3f(-2.0f+x,-2.0f+y, 0.0f);
            glColor3f(0.0, 0.3, 0.0);
		glVertex3f( 0.0f+x, 2.0f+y, 0.0);
            glColor3f(0.0, 0.0, 0.2);
		glVertex3f( 2.0f+x, -2.0f+y, 0.0);
	glEnd();
      
	glBegin(GL_POLYGON);
		glVertex3f(-2.0f+4,-2.0f, 0.0f);
		glVertex3f( 0.0f+4, 2.0f, 0.0);
		glVertex3f( 2.0f+4, -2.0f, 0.0);
	glEnd();

	angle+=0.1f;

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y) {

	switch(key) {
		case GLUT_KEY_F1 :
				red = 1.0;
				green = 0.0;
				blue = 0.0; break;
		case GLUT_KEY_F2 :
				red = 0.0;
				green = 1.0;
				blue = 0.0; break;
		case GLUT_KEY_F3 :
				red = 0.0;
				green = 0.0;
				blue = 1.0; break;
	}
}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(Width,Height);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// here are the new entries
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
      glutMouseFunc(mouse);
	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}
