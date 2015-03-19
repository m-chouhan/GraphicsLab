
#include "Smasher.hpp"

bool Smasher::Smash(Cube &c1,Rect &r1)
{
      return false;
}

bool Smasher::Smash(Sphere &s,Cube &c)
{
      Cube absCube;
      c.getAbsolutes(absCube);
      
      Vector dist = s.origin - absCube.origin;
      float size = s.size + absCube.size;
      if( dist.mod() > size ) return false;
      
      return false;
}
