
#include "Sphere.hpp"
#include "Smasher.hpp"
#include "Cube.hpp"

bool Sphere::Collision(Shape &S)
{
      if( Cube *c = dynamic_cast<Cube *>(&S))
            return Smasher::Smash(*this,*c);
      if(Sphere *s = dynamic_cast<Sphere*>(&S) )
            return CollisionSelf(*this);
      return false;
}

bool Sphere::CollisionSelf(Sphere &S)
{
      Point3D dist = S.origin - origin;
      return dist.mod() < (S.radius + radius);
}

void Sphere::Write(std::ofstream &out)
{
      
}
