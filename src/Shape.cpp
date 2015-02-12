
/* Contains Abstract Shape class and corresponding Rect and cube classes
 * Author:Mahendra Chouhan(14CS60R12)
 */ 
 
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "Point3D.cpp"

/*Parent Shape class for all shapes
 * any new shape must inherit this
 * Note: All movement must be relative to origin
 * if absolute values are needed than compute using getAbs()
 * */
/*
class Shape
{
      Point3D origin;
      int degX,degY,degZ;
      public:
      //generate absolute values of shape (if required)  
      virtual Shape& getAbsolutes(Shape &) = 0;
      virtual void Rotate(int,int,int)= 0;
      virtual void Scale(float)= 0;
      virtual void Move(Point3D &)= 0;
      virtual bool Collision(Shape &)= 0;
};

class Rect
{
    Point3D origin;
  
    Point3D Points[4];
    //int orientation;
    public:
    friend class Cube;
    friend bool CheckCollision(std::vector<class Cube> world,class Cube c);
    friend Point2D HandleCollision(std::vector<class Cube> &world,class Cube C,std::vector<class Cube> &conflicts);

    Rect(){}
    Rect(Point3D origin,Point3D p0,Point3D p1,Point3D p2,Point3D p3)
    {
        this->origin = origin;
            Points[0] = p0;Points[1] = p1;
        Points[2] = p2;Points[3] = p3;
    }
    Point3D getOrigin() { return origin;}
    void setOrigin(Point3D P) { origin = P; }
    Point3D * getPoints() { return Points;}
    //@not implemented
    //~ Rect(Point3D origin,int orientation,int length,int breadth)
    //~ {
	//~ float deg = Rad(orientation);
	//~ this->origin = origin;
        //~ 
    //~ }
    void write(std::ofstream &out)
    {
        //@Add origin to all points
        for(int i = 0;i<3;++i)
                writeLine(Points[i],Points[i+1],out);
	   writeLine(Points[0],Points[3],out);
         writePoint(origin,out); 
    }
    bool isAbove(Rect &R2)
    {
        return (R2.origin.z < origin.z);
    }
    //Not implemented
    void Rotate(int Degx,int Degy,int Degz);
    void Scale(int S);
    bool CheckCollision(Rect &R2)
    {   
        //@Assuming absolute values
        bool flag = false;
        for(int i = 0;i<4;++i)
        {
		flag = check_inside(R2.Points[i]) or 
			R2.check_inside(Points[i]) or flag;
        }
        flag = check_inside(R2.origin) or flag;
        return flag;
    }
    
    void Translate(Point3D P)
    {
        for(int i = 0;i<4;++i) Points[i] = Points[i] + P;
        origin = origin + P;
    }
    
    bool check_inside(Point3D q)
    {
        Vector prev;
        for(int i = 0;i<4;++i)
        {
            Vector V = Points[(i+1)%4] - Points[i],
                   Q = q - Points[i];
            Vector R = V.X(Q);//cross product
            
            if( i == 0) prev = R;
            
            if( (prev.z > 0 && R.z > 0) or
                (prev.z < 0 && R.z < 0) or (!prev.z ^ !R.z)) 
                prev = R;
            else return false;
        }	
        return true;
    }
};

class Cube
{
	Point3D origin;
      public:
      Rect Faces[6];

      friend bool CheckCollision(std::vector<Cube> world,Cube c);
      friend Point2D HandleCollision(std::vector<Cube> &world,Cube C,std::vector<Cube> &conflicts);

      //int length,breadth,depth;
	//length - along x axis
	//bredth - along y axis , depth - along z axis
	Cube(Point3D orig,int length,int breadth,int depth)
	{	
		Point3D temp;
            Point3D Points[8];
	
		origin = orig;
		temp.y -= breadth/2;temp.x -= length/2;temp.z += depth/2;
		
		Points[0] = temp;
		temp.x += length;Points[1] = temp;
		temp.y += breadth;Points[2] = temp;
		temp.x -= length;Points[3] = temp;
		temp.z -= depth;Points[4] = temp;
		temp.y -= breadth;Points[5] = temp;
		temp.x += length;Points[6] = temp;
		temp.y += breadth;Points[7] =temp;
		
		temp = Point3D(0,0,depth/2);
		Faces[0] = Rect(temp,
				Points[0],Points[1],Points[2],Points[3]);                
		temp = Point3D(0,0,-depth/2);
		Faces[1] = Rect(temp,
				Points[4],Points[5],Points[6],Points[7]);
		temp = Point3D(0,breadth/2,0);
		Faces[2] = Rect(temp,
				Points[2],Points[3],Points[4],Points[7]);
		temp = Point3D(0,-breadth/2,0);
		Faces[3] = Rect(temp,
				Points[0],Points[1],Points[6],Points[5]);
		temp = Point3D(length/2,0,0);
		Faces[4] = Rect(temp,
				Points[1],Points[2],Points[7],Points[6]);
		temp = Point3D(-length/2,0,0);
		Faces[5] = Rect(temp,
				Points[0],Points[3],Points[4],Points[5]);		
	}
	Cube(const char *objfile)
      {
            std::ifstream in(objfile);
            int x=0,y=0,z=0;
            int l=0,b=0,h=0;
            in>>l>>b>>h>>x>>y>>z;
            std::cout<<"\nCube{"<<l<<b<<h<<x<<y<<z<<"}\n";

            *this = Cube(Point3D(x,y,z),l,b,h);
            in.close();	
      }
	Cube(int l)
      {
            *this = Cube(Point3D(),l,l,l);
      }
      Cube()
      {
            *this = Cube(Point3D(),0,0,0);
      }
	void Scale(float S);
	void Rotate(int Degx,int Degy,int Degz);
	void write(const char *svgFile);
	//projects hidden faces
	void writeHidden(const char*svgFile);
      void getAbsolutes(Cube &c)
      {
            c.origin = origin;
            for(int i = 0;i<6;++i)
                  for(int j = 0;j<4;++j)
                  {
                        c.Faces[i].Points[j] = 
                        Faces[i].Points[j] + origin;
                        c.Faces[i].origin = Faces[i].origin+origin;
                  }      
      }
      //~ A relative movement
      void Translate(Point3D &P)
      {
            origin = origin + P;
      }
      //~ Absolute movement of cube to that point
      void Move(Point3D &P)
      {
            origin = P;    
      }
      //@doesnot projects hidden space
      void write(std::ofstream &out);
      //@Writes to ofstream and uses the id to determine vertex position
      void writeObj(std::ofstream &out,int ID);
};
*/
void Cube::Scale(float S)
{
      float MatS[4][4] = { S, 0, 0,  0,
                         0, S, 0,  0,
                         0, 0, S,  0,
                         0, 0, 0,  1 };
	//@for(int i = 0;i<8;++i)
		//@Points[i].Multiply(MatS);
	for(int i = 0;i<6;++i)
      {
            for(int j = 0;j<4;++j)
            {
                Faces[i].Points[j].Multiply(MatS);
            }
            
            Faces[i].origin.Multiply(MatS);

      }    
}

void Cube::Rotate(int Degx,int Degy,int Degz)
{
    float   radx = Rad(Degx),
            rady = Rad(Degy),
            radz = Rad(Degz);
	
    float MatZ[4][4] = { cosf(radz), -sinf(radz), 0,  0,
                         sinf(radz), cosf(radz),  0,  0,
                         0       ,  0      ,    1,  0,
                         0       ,  0      ,    0,  1 };
                         
      float MatY[4][4] = { cosf(rady), 0,    sinf(rady),0,
                         0       , 1,       0    ,0,
                         -sinf(rady), 0,   cosf(rady),0,
                         0       ,  0      ,  0  ,1 };
                         
	float MatX[4][4] = { 1       ,  0      ,  0     ,0,
                         0,     cosf(radx), -sinf(radx) ,0,
                         0,     sinf(radx), cosf(radx)  ,0,
                         0,         0   ,       0   ,1 };

	//@for(int i = 0;i<8;++i)
		//@Points[i].Multiply(MatX)->Multiply(MatY)->Multiply(MatZ);
	for(int i = 0;i<6;++i)
      {
            for(int j = 0;j<4;++j)
            Faces[i].Points[j].Multiply(MatX)->
                               Multiply(MatY)->
                               Multiply(MatZ);
            Faces[i].origin.Multiply(MatX)->
                            Multiply(MatY)->
                            Multiply(MatZ);                   
      }
}

void Cube::writeHidden(const char *svgFile)
{
      Cube C;
      getAbsolutes(C);
	std::ofstream out(svgFile);
    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

      for(int i = 0;i<6;++i)
            C.Faces[i].write(out);
      out<<"</svg>\n";
    
	out.close();
}

void Cube::write(std::ofstream &out)
{
    Cube C;
    getAbsolutes(C);
      
    for(int i = 0;i<6;++i)
    {
        bool collision = false;
        for(int j = 0;j<6;++j)
        {
            if( i == j) continue;  
            if(C.Faces[i].CheckCollision(C.Faces[j]))
            {
                collision = true;
                if(C.Faces[i].isAbove(C.Faces[j]))
                    C.Faces[i].write(out);
                break;
            }
        
        }
        if(!collision)
            C.Faces[i].write(out);
    }
        
}

void Cube::write(const char *svgFile)
{
	std::ofstream out(svgFile);    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";
      write(out);
      out<<"</svg>\n";
    	out.close();
}

void Cube::writeObj(std::ofstream &out,int ID)
{
      Cube C;
      getAbsolutes(C);
      
      for(int i = 0;i<2;++i)
            for(int j = 0;j<4;++j)
            {
                  out<<"v ";
                  out<<C.Faces[i].Points[j]<<std::endl;
            }
            
      out<<"f "<<ID+0<<" "<<ID+1<<" "<<ID+2<<" "<<ID+3<<std::endl;            
      out<<"f "<<ID+4<<" "<<ID+5<<" "<<ID+6<<" "<<ID+7<<std::endl;            
      out<<"f "<<ID+2<<" "<<ID+3<<" "<<ID+4<<" "<<ID+7<<std::endl;            
      out<<"f "<<ID+0<<" "<<ID+1<<" "<<ID+6<<" "<<ID+5<<std::endl;            
      out<<"f "<<ID+1<<" "<<ID+6<<" "<<ID+7<<" "<<ID+2<<std::endl;            
      out<<"f "<<ID+0<<" "<<ID+3<<" "<<ID+4<<" "<<ID+5<<std::endl;            
      out<<std::endl;
}
