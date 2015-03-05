
#ifndef __SMASHER__
#define __SMASHER__

class Cube;
class Rect;
class Sphere;

class Smasher
{
      public:
      static bool Smash(Cube &c1,Rect &r1);
      static bool Smash(Sphere &s,Cube &c);
};

#endif
