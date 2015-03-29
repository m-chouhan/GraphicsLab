#ifndef __PHYSICS__
#define __PHYSICS__

#include "Point3D.h"
#include "Shape.h"
#include "graphics.h"
//#include "Smasher.hpp"

class Physics{
      
      //~ G is gravity constant
      double G,elasticity,drag;
      int WorldSize;
      public:
      Physics(double g,double e,double d,int size):G(g),elasticity(e),drag(d),WorldSize(size)  {  }
      
      Vector GVector(Shape *s1,Shape *s2)
      {
            Vector r = s2->origin - s1->origin;
            float force = G*s1->mass*s2->mass/(r.mod()*r.mod());
            return (r*force)/r.mod();
      }
      
      Vector Acc(unsigned int pos,ShapeList2 &list,Vector delta)
      {
            Vector acc;
            Shape *s1 = list[pos].first;
            s1->Translate(delta);
            for(unsigned int i = 0;i<list.size();++i)
            {
                  if(i==pos) continue;
                  Shape *s2 = list[i].first;
                  acc = acc + GVector(s1,s2)/s1->mass;      
            }
            s1->Translate(delta*-1);
            return acc;
      }
      
      void Separate(Shape *s1,Shape *s2);
      
      Vector EulersApproximation(Vector &velo,Vector acc,float Tstep)
      {
            Vector delta = velo*Tstep + acc*Tstep*(Tstep/2);
            velo = (velo + acc*Tstep)*drag;
            return delta;
      }
      
      void GravityManager(ShapeList2 &list);
      void GravityManagerRunge(ShapeList2 &list);
      
      void CollisionManager(ShapeList2 &list);
      void RungeApproximation(int pos,ShapeList2 &list,float tstep);
      void Update(ShapeList2 &list)
      {
            GravityManager(list);
            CollisionManager(list);
            for(unsigned int i = 0;i<list.size();++i)
                  list[i].second.Push(list[i].first->getOrigin());            
      }
};

#endif
