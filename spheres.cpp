#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/glut.h>
#include "src/Sphere.hpp"
#include "src/Simulator.hpp"

using namespace std;

int main(int argc, char **argv) {
            
      Simulator::SimulatorInit(argc,argv,600,600);
      Sphere S( Point3D(0.0,0.0,0),3.2,60) ,S2( Point3D(-10,0,10) , 1.2,20,false);
      Sphere S3( Point3D(0,0,10), 2,30,false);
      Sphere S4( Point3D(0,-5,-1), 2.5,40,false);

      S.velocity = Point3D( -7,5,1 );

      Simulator::AddObject( &S);
      Simulator::AddObject( &S2,Earth3);
      Simulator::AddObject( &S3,Neptune);
      Simulator::AddObject( &S4,Earth);
      
      Simulator::AddLighSource( &S );      
      
      S2.velocity = Point3D(-1.1,0,5);
      S3.velocity = Point3D( 1,1,1 );
      ifstream in("planets.txt");
      
      Sphere *s = new Sphere();
      while( in>>(*s) )
      {
            Point3D origin = s->getOrigin();
            origin.y = 0;
            s->Move(origin);
            Simulator::AddObject( s ,Moon);
            //~ Simulator::AddLighSource( s );      
            s = new Sphere();
      }/**/
      in.close();
      //cout<<S.getOrigin()<<S.getRad();
      Simulator::StartSimulation();      
      //glutMainLoop();
	return 1;
}
