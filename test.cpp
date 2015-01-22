
#include <iostream>
#include <fstream>

using namespace std;

struct A
{
	int I;
	A(int a) { I = a ; }
	A(){  *this = A(10);}
	
};

int main()
{
	A obj;
	cout<<obj.I;
	
	return 0;
}
