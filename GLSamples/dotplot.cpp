/* Page 52 Figure 2.16
 * A complete OpenGL program to draw "dot plot" of a function
 */


#include <windows.h>  // comment this for linux
#include <math.h>
//#include <Gl.h>
#include <glut.h>
const int screenWidth=640;	// width of screen window in pixels
const int screenHeight=480;	// height of scrren window in pixels
GLdouble A,B,C,D;			// values used for scaling and shifting
//****************** myInit ******************/

void myInit(void)

{
	glClearColor(1.0,1.0,1.0,0.0);			// set whitebackground color
	glColor3f(0.0f,0.0f,0.0f);				// set the drawing color(black)
	glPointSize(2.0);						// a 'dot' is 4 by 4 pixels
	glMatrixMode(GL_PROJECTION);			// set camera shape
	glLoadIdentity();
	gluOrtho2D(0.0,(GLdouble)screenWidth,0.0,(GLdouble)screenHeight);
	A = screenWidth/4;						// set values used for scaling and shifting
	B = 0;
	C = D = screenHeight/2;
}

//****************** myDisplay ******************/

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);		// clear the screen
	glBegin(GL_POINTS);
	for(GLdouble x=0;x<4;x+=0.005)
	{
		GLdouble func=exp(-x) * cos(2*3.14159265*x);
		glVertex2d(A*x+B,C*func+D);
	}
	glEnd();
	glFlush();							// send all output to display
}

//****************** main ******************/

void  main(int argc, char ** argv)
{
	glutInit(&argc,argv);				// Initialize  the toolkit
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	// set Display mode
	glutInitWindowSize(640,480);		// set window size
	glutInitWindowPosition(100,150);	// set window position on screen
	glutCreateWindow("Dot Plot of a function");// open the screen window
	glutDisplayFunc(myDisplay);			// register redrtaw function
	myInit();
	glutMainLoop();						// go into a perpetual loop
}
