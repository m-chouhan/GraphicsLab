
#include "Sphere.hpp"
#include "Smasher.hpp"
#include "Cube.hpp"
#include "Simulator.hpp"

void Sphere::Draw()
{  Simulator::drawSphere(origin,radius,col,light); }

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
