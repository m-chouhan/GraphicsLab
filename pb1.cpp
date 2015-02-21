
// pb1.cpp
// To compile: g++ pb1.cpp -lglut -lGLU -o pb1
// To run: ./pb1

#include <GL/glut.h>
#include <stdlib.h>

void renderScene(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glVertex3f(-0.5, -0.5, 0.0);
  glVertex3f(0.5, 0.0, 0.0);
  glVertex3f(0.0, 0.5, 0.0);
  glEnd();
  glFlush();
}

int main(int argc, char** argv) { 
  glutInit(&argc, argv);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(600,600);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow("GLUT");
  glutDisplayFunc(renderScene);
  glutMainLoop();
} 


