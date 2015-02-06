
#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "graphics.cpp"

using namespace std;

int main()
{
    srand(time(NULL));
  
    vector<Cube> World;
    vector<Cube> Cubes;
    Cube C1( Point3D(500,500,0),200,200,200 ),
         C2( Point3D(500,720,0),200,200,200 );
    World.push_back(C1);
    C2.Rotate(0,0,7);
    //@Cube c1,c2;
    //@C1.getAbsolutes(c1);C2.getAbsolutes(c2);

    Rect R1( Point3D(500,500,0),Point3D(400,400,0),Point3D(400,600,0),
             Point3D(600,600,0),Point3D(600,400,0));
    Rect R2( Point3D(500,500,0),Point3D(500,350,0),Point3D(650,500,0),
             Point3D(500,650,0),Point3D(350,500,0));
    
    R2.Translate(Point3D(-100,-100,110));
                 
    ofstream out("randomCubes.svg");
    out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"1000\" width=\"1000\">\n";
    //@R1.write(out);
    //@R2.write(out);  
    //@c1.Faces[1].write(out);
    //@c2.Faces[1].write(out);
    C1.write(out);
    C2.write(out);
    out<<"</svg>\n";
    //@cout<<endl<<R1.check_inside(Point3D(401,401,10))<<endl;
    //@cout<<endl<<R1.CheckCollision(R2)<<endl;

    cout<<CheckCollision(World,C2)<<endl;
    out.close();
    return 0;
}
