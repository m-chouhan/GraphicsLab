
#include <GL/glut.h>

#include "Sphere.hpp"
#include "Smasher.hpp"
#include "Cube.hpp"
#include "Simulator.hpp"

void Sphere::Draw()
{  
      //~ Simulator::drawSphere(origin,radius,col,light); 
      glPushMatrix();

      glColor3f(col.r,col.g,col.b);
      glTranslatef(origin.x,origin.y,origin.z);
      
      if(light)
      {
            //~ Material properties
            GLfloat emissiveLight[] = { 1.2f, 0.6f, 0.f}; 
            //Simulator::move_light(Point3D());
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveLight);
            glutSolidSphere(radius,20,20);
            emissiveLight[0] = emissiveLight[1] = emissiveLight[2]  = 0;
            glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emissiveLight);
      }

      else glutSolidSphere(radius,20,20);
      glPopMatrix();
}

bool Sphere::Collision(Shape &S)
{
      if( Cube *c = dynamic_cast<Cube *>(&S))
            return Smasher::Smash(*this,*c);
      if(Sphere *s = dynamic_cast<Sphere*>(&S) )
            return CollisionSelf(*s);
      return false;
}

bool Sphere::CollisionSelf(Sphere &S)
{
      Point3D dist = S.origin - origin;
      std::cout<<"Collision Self:\tS:"<<S.origin<<"\tthis:"<<origin<<std::endl;
      return dist.mod() < (S.radius + radius);
}

void Sphere::Write(std::ofstream &out)
{
      
}
