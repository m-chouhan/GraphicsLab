#include <stdlib.h>
#include <iostream>
#include <math.h>

#include <GL/glut.h>
#include "src/Sphere.hpp"
#include "src/Simulator.hpp"

using namespace std;

int main(int argc, char **argv) {
            
      Simulator::SimulatorInit(argc,argv,500,500);
      Sphere S( Point3D(0.0,0.0,0),4.5,10 ) ,S2( Point3D(-10,1,20) , 5.2,10);
      Simulator::World.push_back( &S);
      Simulator::World.push_back( &S2);
      //cout<<S.getOrigin()<<S.getRad();
      //Simulator::StartSimulation();      
      glutMainLoop();
	return 1;
}
