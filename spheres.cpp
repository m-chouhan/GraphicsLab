#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/glut.h>
#include "src/Sphere.hpp"
#include "src/Simulator.hpp"

using namespace std;

int main(int argc, char **argv) {
            
      Simulator::SimulatorInit(argc,argv,500,500);
      Sphere S( Point3D(0.0,0.0,0),3.2,40 ) ,S2( Point3D(-10,20,20) , 1.2,20);
      Sphere S3( Point3D(10,10,10), 2,30);

      Simulator::World.push_back( &S);
      Simulator::World.push_back( &S2);
      Simulator::World.push_back( &S3);
      
      ifstream in("planets.txt");
      
      Sphere *s = new Sphere();
      while( in>>(*s) )
      {
            Simulator::World.push_back( s );
            s = new Sphere();
      }
      in.close();
      //cout<<S.getOrigin()<<S.getRad();
      Simulator::StartSimulation();      
      //glutMainLoop();
	return 1;
}
