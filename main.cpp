
#include <iostream>
#include <stdlib.h>
#include "Avl.cpp"
using namespace std;

int main()
{
	BinaryTree Bt;
	/*
	Bt.insert(5);Bt.insert(4);Bt.insert(6);
	Bt.insert(10);Bt.insert(11);Bt.insert(14);
	Bt.insert(1);
	Bt.insert(2);Bt.insert(18);
      */
      
	cout<<"Inserting.."<<endl;
	for(int i = 0;i<8;++i)
	{
		int var = rand()%20;
		cout<<var<<"->";
		Bt.insert(var);
	}
      
	cout<<endl<<"Contents of Binary tree inorder traversal .."<<endl;
	Bt.print();
      Bt.BalanceTree(Bt.root);
      cout<<"After Balancing"<<endl;
	Bt.print();
      Bt.printInorder(Bt.root);
	cout<<endl;
      return 0;
}
