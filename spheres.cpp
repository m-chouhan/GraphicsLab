#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glut.h>
#include "src/Sphere.hpp"
#include "src/Simulator.hpp"

using namespace std;

int main(int argc, char **argv) {
            
      SimulatorInit(argc,argv,500,500);
      Sphere S( Point3D(0.0,0.0,0),4.5,10 ) ,S2( Point3D(-10,1) , 5.2,10);
      //S.origin = Point3D(0.9,0.9,0);
      World.push_back( &S);
      World.push_back( &S2);
      cout<<S.getOrigin()<<S.getRad();
      //Simulator::StartSimulation();
      
      /*
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
      */
      glutMainLoop();
	// enter GLUT event processing cycle
	return 1;
}
