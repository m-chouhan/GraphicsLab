
/* Contains Abstract Shape class and corresponding Rect and cube classes
 * Author:Mahendra Chouhan(14CS60R12)
 */ 
 
#include "Shape.h"

/*Parent Shape class for all shapes
 * any new shape must inherit this
 * Note: All movement must be relative to origin
 * if absolute values are needed than compute using getAbs()
 * */
inline void Cube::getAbsolutes(Cube &c)
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

void Cube::Scale(float S)
{
      float MatS[4][4] = { S, 0, 0,  0,
                         0, S, 0,  0,
                         0, 0, S,  0,
                         0, 0, 0,  1 };
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
