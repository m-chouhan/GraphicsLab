#ifndef __PHYSICS__
#define __PHYSICS__

#include "Shape.h"
#include "Smahser.hpp"

class Physics{
      
      void Update(ShapeList &list)
      {
            GravityManager(list);
            CollisionManager(list);
      }
};

#endif
