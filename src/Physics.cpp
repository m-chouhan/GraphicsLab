
#include "Physics.hpp"
#include <vector>

void Physics::GravityManager(ShapeList &list)
{
      //reset acc
      for(int i = 0;i<list.size();++i) list[i]->acc = Point3D(0,0,0);
      //~ Acceleration for current time step
      for(int i = 0;i<list.size();++i)
      {
            for(int j = i+1;j<list.size();++j)
            {
                  Shape *s1 = list[i],*s2 = list[j];
                  Vector force = GVector(s1,s2);
                  s1->acc = s1->acc + force/s1->mass;
                  s2->acc = s2->acc + (force/s2->mass)*-1;
            }
      }
      
      //~ Now we have acc and velocity for current time step 
      //~ So apply Approximation
      for(int i = 0;i<list.size();++i)   
      {
            Vector delta  = EulersApproximation(list[i]->velocity,list[i]->acc,0.02);
            list[i]->Translate(delta);
            //~ RungeKutta();
      }
}

void Physics::Separate(Shape *s1,Shape *s2)
{
      s1->Translate(s1->velocity*0.02f);
      s2->Translate(s2->velocity*0.02f);
}

void Physics::CollisionManager(ShapeList &list)
{
      for(int i = 0;i<list.size();++i)
      {
            for(int j = i+1;j<list.size();++j)
            {
                  Shape *s1 = list[i],*s2 = list[j];
                  if( s1->Collision(*s2))
                  {
                        //~ reset pos and velocites ( note that acc will be same )
                        std::cout<<"\n"<<i<<"|||Collision|||"<<j<<"\t";
                        float k1 = (s1->mass  - s2->mass)/(s1->mass + s2->mass);
                        float k2 = ( 2* s2->mass)/ (s1->mass + s2->mass);
                        float k3 = ( 2* s1->mass)/ (s1->mass + s2->mass);
                        
                        Vector v1 = (s1->velocity*k1 + s2->velocity*k2);
                        Vector v2 = (s1->velocity*k3 - s2->velocity*k1);
                        s1->velocity = v1*0.95;
                        s2->velocity = v2*0.95;
                        Separate(s1,s2);//seperates shape from  each other ( collision means they are inside each other )
                  }
            }
      }
}
