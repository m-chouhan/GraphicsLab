
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "src/Shape.h"
#include "src/graphics.h"

using namespace std;


class A {
      public:
      virtual void Print(A *obj) = 0;
};

//@class B;
//@class C;

class B:public A {

      public:      
      void Print(A *obj);      
};

class C:public A {
      
      public:
      void Print(A *obj)
      {
            if ( dynamic_cast<B*>(obj) != NULL )
                  cout<<"Print called(B,C)"<<endl;
            else if ( dynamic_cast<C*>(obj) != NULL )
                  cout<<"Print called(C,C)"<<endl;
      }
};

void B::Print(A *obj)
      {
            if ( dynamic_cast<B*>(obj) != NULL )
                  cout<<"Print called(B,B)"<<endl;
            else if ( dynamic_cast<class C*>(obj) != NULL )
                  cout<<"Print called(B,C)"<<endl;
      }


int main(int argc,char *argv[])
{
      /*
      srand(time(NULL));
      B objb;
      C objc;
      A *b = &objb,*c = &objc;
      c->Print(c);*/
      
      /*
      vector<Cube> World;
      vector<Cube> Cubes;
      Cube C1( Point3D(500,500,0),200,200,200 ),
         C2( Point3D(500,720,0),200,200,200 );
      World.push_back(C1);
      C2.Rotate(0,0,7);
      Cube c1,c2;
      C1.getAbsolutes(c1);C2.getAbsolutes(c2);
      */
      Rect R1( Point3D(500,300,0),Point3D(400,200,0),Point3D(400,600,0),
      Point3D(600,600,0),Point3D(600,200,0));
      //~ Rect R2( Point3D(500,500,0),Point3D(500,350,0),Point3D(650,500,0),
      //~ Point3D(500,650,0),Point3D(350,500,0));


      ofstream out("test.svg");
      out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"1000\" width=\"1000\">\n";

      Point3D orig(atof(argv[1]),atof(argv[2]),atof(argv[3]));
      
      float degx = atoi(argv[4]);
      float degy = atoi(argv[5]);
      float degz = atoi(argv[6]);

      R1.Translate(orig);
      R1.Project(Point3D(400,200,100));      
      R1.Write(out);
      /*
      R2.write(out);  
      c1.Faces[1].write(out);
      c2.Faces[1].write(out);
      C1.write(out);
      C2.write(out);*/

      out<<"</svg>\n";
      out.close();
      
      return 0;
}
