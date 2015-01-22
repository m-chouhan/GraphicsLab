
#include <iostream>
#include <math.h>
#include <fstream>
#include <stdlib.h>

double Rad(float Deg) 
{
	return (3.14*Deg/180);
}

//~ 
//~ void GenerateMat(int Deg,float MatX[4][4],float MatY[4][4],float MatZ[4][4])
//~ {
    //~ float rad = Rad(Deg);
	//~ 
    //~ float MatZ[4][4] = { cosf(rad), -sinf(rad), 0,  0,
                         //~ sinf(rad), cosf(rad),  0,  0,
                         //~ 0       ,  0      ,    1,  0,
                         //~ 0       ,  0      ,    0,  1 };
                         //~ 
    //~ float MatY[4][4] = { cosf(rad), 0,    sinf(rad),0,
                         //~ 0       , 1,       0    ,0,
                         //~ -sinf(rad), 0,   cosf(rad),0,
                         //~ 0       ,  0      ,  0  ,1 };
                         //~ 
	//~ float MatX[4][4] = { 1       ,  0      ,  0     ,0,
                         //~ 0,     cosf(rad), -sinf(rad) ,0,
                         //~ 0,     sinf(rad), cosf(rad)  ,0,
                         //~ 0,         0   ,       0   ,1 };
//~ 
//~ }

using namespace std;


struct Point3D
{
	float x;
	float y;
	float z;
	Point3D() { x = y = z = 0; }
	Point3D(int X,int Y,int Z) { x = X;y = Y;z = Z;}
	Point3D * Multiply(float Matrix[][4]);
	Point3D add(Point3D p1,Point3D p2)
	{
		return Point3D(p1.x+p2.x,p1.y+p2.y,p1.z+p2.z);
	}
	Point3D add(Point3D p1)
	{
		return Point3D(p1.x+x,p1.y+y,p1.z+z);
	}
    //~ dot product
    float operator *(const Point3D &P2) {
            return x*P2.x + y*P2.y + z*P2.z;
        } 
};

Point3D * Point3D::Multiply(float  Matrix[][4])
{
	float temp[4] = {0};
	for(int i = 0;i<4;++i)
		temp[i] = x*Matrix[i][0] + y*Matrix[i][1] + z*Matrix[i][2];
	
    x = temp[0];y = temp[1]; z = temp[2];
    return this;
}

void writeLine(Point3D p1,Point3D p2,ofstream &out)
{	
	out<<"\n\t<line x1 = \""<<p1.x
	<<"\" y1 = \""<<p1.y 
	<<"\" x2 = \""<<p2.x
	<<"\" y2 = \""<<p2.y
	<<"\" style=\"stroke:rgb(255,0,0);stroke-width:2\" />\n";
}

struct Rect
{
    Point3D Points[4];
    Point3D origin;
    int orientation;
    Rect(){}
    Rect(Point3D origin,Point3D p0,Point3D p1,Point3D p2,Point3D p3)
    {
	this->origin = origin;
        Points[0] = p0;Points[1] = p1;
	Points[2] = p2;Points[3] = p3;
	//for(int i = 0;i<4;++i) this->Points[i] = Points[i];
    }
    //not implemented
    Rect(Point3D origin,int orientation,int length,int breadth)
    {
	float deg = Rad(orientation);
	this->origin = origin;
        
    }
    //Not implemented	
    bool checkCollision(Rect &R2)
    {
        
        return false;
    }
	
    void write(ofstream &out)
    {
        for(int i = 0;i<3;++i)
                writeLine(Points[i].add(origin),Points[i+1].add(origin),out);
	   writeLine(Points[0].add(origin),Points[3].add(origin),out); 
    }
    //Not implemented
    void Rotate(int Deg)
    {

    }

};

struct Cube
{
	Point3D Points[8];
    Rect Faces[6];
	Point3D origin;
	//length - along x axis
	//bredth - along y axis , depth - along z axis
	Cube(Point3D orig,int length,int breadth,int depth)
	{	
		Point3D temp;	
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
		Faces[0] = Rect(origin.add(origin,temp),
				Points[0],Points[1],Points[2],Points[3]);                
		temp = Point3D(0,0,-depth/2);
		Faces[1] = Rect(origin.add(origin,temp),
				Points[4],Points[5],Points[6],Points[7]);
		temp = Point3D(0,breadth/2,0);
		Faces[2] = Rect(origin.add(origin,temp),
				Points[2],Points[3],Points[4],Points[7]);
		temp = Point3D(0,-breadth/2,0);
		Faces[3] = Rect(origin.add(origin,temp),
				Points[0],Points[1],Points[6],Points[5]);
		temp = Point3D(length/2,0,0);
		Faces[4] = Rect(origin.add(origin,temp),
				Points[1],Points[2],Points[7],Points[6]);
		temp = Point3D(-length/2,0,0);
		Faces[5] = Rect(origin.add(origin,temp),
				Points[0],Points[3],Points[4],Points[5]);		
	}
	Cube(const char *objfile)
    {
        ifstream in("cube.obj");
        int x=0,y=0,z=0;
        int l=0,b=0,h=0;
        in>>l>>b>>h>>x>>y>>z;
        cout<<l<<b<<h<<x<<y<<z;
        Cube c(Point3D(x,y,z),l,b,h);
        in.close();	
    }
	void Scale(float S);
	void Rotate(int Degx,int Degy,int Degz);
	void write(const char *svgFile);
};

void Cube::Scale(float S)
{
    float MatS[4][4] = { S, 0, 0,  0,
                         0, S, 0,  0,
                         0, 0, S,  0,
                         0, 0, 0,  1 };
	for(int i = 0;i<8;++i)
		Points[i].Multiply(MatS);
	for(int i = 0;i<6;++i)
    {
            for(int j = 0;j<4;++j)
            Faces[i].Points[j].Multiply(MatS);
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

	for(int i = 0;i<8;++i)
		Points[i].Multiply(MatX)->Multiply(MatY)->Multiply(MatZ);
    //~ for(int i = 0;i<8;++i)
		//~ Points[i].Multiply(MatY);	
	for(int i = 0;i<6;++i)
    {
            for(int j = 0;j<4;++j)
            Faces[i].Points[j].Multiply(MatX)->
                               Multiply(MatY)->
                               Multiply(MatZ);
    }
}

void Cube::write(const char *svgFile)
{
	ofstream out(svgFile);
    
	out<<"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" height=\"310\" width=\"500\">\n";

	for(int i = 0;i<7;++i)
	{
		writeLine(Points[i].add(origin),Points[i+1].add(origin),out);
	}
    writeLine(Points[0].add(origin),Points[3].add(origin),out);    
    writeLine(Points[0].add(origin),Points[5].add(origin),out);    
    writeLine(Points[7].add(origin),Points[2].add(origin),out);    
    writeLine(Points[4].add(origin),Points[7].add(origin),out);    
    writeLine(Points[1].add(origin),Points[6].add(origin),out);    

    for(int i = 0;i<4;++i)
    {
        //~ Faces[i].write(out);
    }
    out<<"</svg>\n";
    
	out.close();
}

int  main(int argc,char *argv[])
{ 
    ifstream in("cube.obj");
    int x=0,y=0,z=0;
    int l=0,b=0,h=0;
    in>>l>>b>>h>>x>>y>>z;
    cout<<l<<b<<h<<x<<y<<z;

	Cube c(Point3D(x,y,z),l,b,h);
    
    in.close();
	if(argc != 5)
        { 
            c.Rotate(30,30,0);
            c.Scale(1.5);
        }
    else
    {
            float S = atof(argv[1]);
            float degx = atoi(argv[2]);
            float degy = atoi(argv[3]);
            float degz = atoi(argv[4]);
            c.Rotate(degx,degy,degz);
            c.Scale(S);
    }        
	c.write("svgfile.svg");	
	return 0;
}

