#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <GL/glut.h>
#include "src/Sphere.hpp"
#include "src/Simulator.hpp"
#include "src/graphics.h"

using namespace std;

int main(int argc, char **argv) {
            
      Simulator::SimulatorInit(argc,argv,600,600);
      //~ Sphere S( Point3D(1.0,1.0,1),26.2) ,S2( Point3D(-10,40,20) , 1.2);
      //~ Sphere S3( Point3D(30,0,50), 5);
      //~ Sphere S4( Point3D(0,-35,-1), 2.5);
      //~ Sphere S5( Point3D(-55,-35,-1), 12.5);
      //~ Sphere S6( Point3D(55,-35,-100), 8.5);
      //~ 
      //~ S.velocity = Point3D( -7,5,1 );
      //~ 
      //~ Simulator::AddObject( &S);
      //~ Simulator::AddObject( &S5);
      //~ Simulator::AddObject( &S6);
      
      //~ Simulator::AddObject( &S2,Earth3);
      //~ Simulator::AddObject( &S3,Neptune);
      //~ Simulator::AddObject( &S4,Earth);
      //~ 
      //~ Simulator::AddLighSource( &S );      
      //~ Simulator::AddLighSource( &S5 );      
      //~ 
      //~ S2.velocity = Point3D(-10.2,1,20.5);
      //~ S3.velocity = Point3D( 10,21,10 );
      //~ S4.velocity = Point3D( 10,10,- 10 );
      ifstream in("planets.txt");
      
      Sphere *s = new Sphere();
      while( in>>(*s) )
      {
            int num = rand() % 4;
            
            Simulator::AddObject( s ,static_cast<Planets>(num)  );
            cout<<num<<'\t'<<s->getOrigin()<<"::"<<s->getRad()<<"\n";
            if (s->light) Simulator::AddLighSource( s );      
            s = new Sphere();
      }/**/
      in.close();
      if( s->getRad() )
      {
            Simulator::AddObject( s ,static_cast<Planets>(2)  );
            cout<<'\t'<<s->getOrigin()<<"::"<<s->getRad()<<"\n";
            if (s->light) Simulator::AddLighSource( s );      
      }
      //~ for(int i = 0;i<6;++i)
      //~ {
            //~ s = new Sphere(uniformDistr(150),rand()%8+1);
            //~ 
            //~ while( CheckCollision(Simulator::World,s) )
            //~ {
                  //~ s->Move( uniformDistr(150) );
            //~ }
            //~ 
            //~ Simulator::AddObject( s,Earth3 );
      //~ }
      for( unsigned int i = 0;i<Simulator::World.size();++i)
      {
            cout<<i<<"||"<<Simulator::World[i].first->origin<<"\n";
      }
      
      Simulator::StartSimulation();      
	return 1;
}
