#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/glut.h>
#include "src/Sphere.hpp"
#include "src/Simulator.hpp"

using namespace std;

int main(int argc, char **argv) {
            
      Simulator::SimulatorInit(argc,argv,600,600);
      Sphere S( Point3D(0.0,0.0,0),10.2,60) ,S2( Point3D(-10,40,20) , 1.2,20,false);
      Sphere S3( Point3D(30,0,50), 2,30,false);
      Sphere S4( Point3D(0,-35,-1), 2.5,40,false);
      Sphere S5( Point3D(-55,-35,-1), 12.5,40,false);
      Sphere S6( Point3D(55,-35,-100), 8.5,40,false);
      
      //S.velocity = Point3D( -7,5,1 );

      Simulator::AddObject( &S);
      Simulator::AddObject( &S5);
      Simulator::AddObject( &S6);
      
      Simulator::AddObject( &S2,Earth3);
      Simulator::AddObject( &S3,Neptune);
      Simulator::AddObject( &S4,Earth);
      
      Simulator::AddLighSource( &S );      
      Simulator::AddLighSource( &S5 );      
      Simulator::AddLighSource( &S6 );      
      //Simulator::AddLighSource( &S3 );      
      
      S2.velocity = Point3D(-10.2,1,20.5);
      S3.velocity = Point3D( 10,21,10 );
      S4.velocity = Point3D( 10,10,- 10 );
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
