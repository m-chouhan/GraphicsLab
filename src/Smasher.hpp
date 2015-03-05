
#ifndef __SMASHER__
#define __SMASHER__

class Cube;
class Rect;
class Sphere;

class Smasher
{
      bool Smash(Cube &c1,Rect &r1);
      bool Smash(Sphere &s,Cube &c);
};
#endif
