
#include "Physics.hpp"
#include <assert.h>
#include <vector>

void Physics::GravityManager(ShapeList2 &list)
{
      //reset acc
      for(int i = 0;i<list.size();++i) list[i].first->acc = Point3D(0,0,0);
      //~ Acceleration for current time step
      for(int i = 0;i<list.size();++i)
      {
            for(int j = i+1;j<list.size();++j)
            {
                  Shape *s1 = list[i].first,*s2 = list[j].first;
                  Vector force = GVector(s1,s2);
                  s1->acc = s1->acc + force/s1->mass;
                  s2->acc = s2->acc + (force/s2->mass)*-1;
                  //~ std::cout<<( s1->acc.x != s1->acc.x && s2->acc.x != s2->acc.x )<<"\n";
            }
      }
      
      //~ Now we have acc and velocity for current time step 
      //~ So apply Approximation
      for(int i = 0;i<list.size();++i)   
      {
            Vector delta  = EulersApproximation(list[i].first->velocity,list[i].first->acc,0.02);
            //~ std::cout<<"Prev  "<<i<<"="<<list[i].first->origin<<"\t"<<"delta:"<<delta<<":"<<list[i].first->velocity<<":"<<list[i].first->acc;
            list[i].first->Translate(delta);
            //~ std::cout<<"\tNew value ="<<list[i].first->origin<<"\n";
            //~ RungeKutta();
      }
}

void Physics::GravityManagerRunge(ShapeList2 &list)
{
      for(unsigned int i = 0;i<list.size();++i)
            RungeApproximation(i,list,0.02);
}

void Physics::RungeApproximation(int pos,ShapeList2 &list,float tstep)
{
      Vector delta;
      Shape *s = list[pos].first;Vector vi = s->velocity,ri = s->origin;
      
      /**/
      Vector  k1r = vi;                                                 Vector k1v = Acc(pos,list,delta);
      Vector  k2r = vi.Multiply(k1v*(tstep/2));       Vector k2v = Acc(pos,list,k1r*(tstep/2));
      Vector  k3r = vi.Multiply(k2v*(tstep/2));       Vector k3v = Acc(pos,list,k2r*(tstep/2));
      Vector  k4r = vi.Multiply(k1v*tstep);              Vector k4v = Acc(pos,list,k3r*tstep);
      /**/
      
}

void Physics::Separate(Shape *s1,Shape *s2)
{
      //~ 
      Point3D dist = s2->origin - s1->origin;
      float size = (s1->size + s2->size);
      std::cout<<"Separating:\ts1:"<<s1->origin<<"("<<s1->size<<'+'<<s2->size<<")\tFrom s2:"<<s2->origin<<std::endl;
      
      assert (dist.mod() < size );
       
       float mul =  (size )/dist.mod();    
       assert( mul > 1 );
       while ( dist.mod() < size )
       {
            dist = dist*mul;
            s2->Move(dist+s1->origin);
            dist = s2->origin - s1->origin;
      }
      //assert (dist.mod() >= size);
      //~ s1->Translate(s1->velocity*0.02f);
      //~ s2->Translate(s2->velocity*0.02f);
      //~ //float mul
}

void Physics::CollisionManager(ShapeList2 &list)
{
      for(int i = 0;i<list.size();++i)
      {
            Shape *s1 = list[i].first;
            Point3D dist = s1->getOrigin();
            //~ Collision with Frame
            if( dist.mod()+s1->size > WorldSize )
            {
                  s1->Move( dist*((WorldSize-1)/(dist.mod() + s1->size) ) );
                  dist = dist/dist.mod();//distance unit vector
                  Vector velox1 = dist*(s1->velocity*dist);
                  Vector veloy1 = dist.X(s1->velocity.X(dist));
                  veloy1 = veloy1/veloy1.mod();
                  s1->velocity = (veloy1 - velox1)*0.5;                        
            }
            //~ Collision with objects
            for(int j = i+1;j<list.size();++j)
            {
                  Shape *s2 = list[j].first;
                  if( s1->Collision(*s2))
                  {
                        //~ reset pos and velocites ( note that acc will be same )
                        std::cout<<"\n"<<i<<"|||Collision|||"<<j<<"\t";
                        float k1 = (s1->mass  - s2->mass)/(s1->mass + s2->mass);
                        float k2 = ( 2* s2->mass)/ (s1->mass + s2->mass);
                        float k3 = ( 2* s1->mass)/ (s1->mass + s2->mass);
                        
                        Vector dist = s2->origin - s1->origin;
                        dist = dist/dist.mod();//distance unit vector
                        
                        Vector velox1 = dist*(s1->velocity*dist);
                        Vector velox2 = dist*(s2->velocity*dist);
                        Vector veloy1 = dist.X(s1->velocity.X(dist));
                        Vector veloy2 = dist.X(s2->velocity.X(dist));
                        
                        veloy1 = veloy1/veloy1.mod();veloy2 = veloy2/veloy2.mod(); //normalize
                        veloy1 = veloy1*(s1->velocity*veloy1),veloy2 = veloy2*(s2->velocity*veloy2);
                        
                        Vector vx1 = (velox1*k1 + velox2*k2);
                        Vector vx2 = (velox1*k3 - velox2*k1);
                        
                        //~ veloy1 = veloy1*elasticity;veloy2 = veloy2*elasticity;
                        
                        s1->velocity = (vx1+veloy1*1)*elasticity;
                        s2->velocity = (vx2+veloy2*1)*elasticity;
                        Separate(s1,s2);//seperates shape from  each other ( collision means they are inside each other )
                  }
            }
      }
}
