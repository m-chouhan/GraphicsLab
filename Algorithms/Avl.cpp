#include "Point3D.cpp"
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

enum EventType{UPPER,LOWER,MIDDLE};



class Node{
		private:
		Point2D p;EventType type;
            int data;      
		Node *left,*right,*parent;
		public:
            Node(Point2D P,EventType t)
            {
                  left = right = parent = NULL;
                  P = p;type = t;
                  data = p.y;
            }
		void setL(Node *lchild)
		{
			left = lchild;
			if(lchild) lchild->parent = this;
		}
		void setR(Node *rchild)
		{
			right = rchild;
			if(rchild) rchild->parent = this;
		}
            //@//setParent determines where to put node
		void setP(Node *parent)
		{
			this->parent = parent;
			if(parent)
				( (parent->data < data) ? parent->right : parent->left) = this;
		}
            
            //@Getters for node class
            
		Node * getL() const 
		{ return left;}
		Node * getR() const
		{ return right;}
		Node * getP() const
		{ return parent;}
		int getData() const
		{ return data; }
		friend class BinaryTree;
};

class BinaryTree{
		
            				
		bool search(int data,Node *root);
		Node * rotateclockwise(Node *node);
		Node * rotateanticlock(Node *node);
		void insert(Point2D P,EventType e,Node * &node,Node *parent);
            //@not used for now
		Node * invert(Node *top,Node * middle,Node *bottom)
		{
			Node * left = bottom->getL(), *right = bottom->getR(),
				*parent = top->getP();

			top->left = top->right = NULL;
			middle->left = middle->right = NULL;
			if(left) left->setP(top);
			if(right)  right->setP(middle);
                  
			bottom->setP(parent);
			top->setP(bottom);
			middle->setP(bottom);
			return bottom;
		}
            int maxHeight(Node *n)
            {
                  if(n == NULL) return 0;
                  return max(maxHeight(n->left),maxHeight(n->right))+1;      
            }      
            public:
            
            //@Pointer to root
		Node *root;
            
            BinaryTree(): root(NULL) {}

		void insert(Point2D P,EventType e)
		{
			insert(P,e,root,NULL);
			//@BalanceTree(root);
		}
		//void remove(int data);
		bool search(int data)
		{  
                  return search(data,root);
            }
		void print() 
		{ 
                  printPreorder(root);
                  //@printInorder(root);
                  std::cout<<std::endl;
            }
            void printInorder(Node *node);
            void printPreorder(Node *node);
		int BalanceTree(Node *node);

};

void BinaryTree::insert(Point2D P,EventType e,Node * &node,Node *parent)
{
	if(node == NULL) 
      {
            //@insert node here
            node = new Node(P,e);
            if ( !parent) return;
            if( parent->data < P.y) parent->setR(node);
            else parent->setL(node);
      }
	else if(node->data < P.y) insert(P,e,node->right,node);
	else insert(P,e,node->left,node);
}

int BinaryTree::BalanceTree(Node *node)
{
	if(node == NULL) return 0;
	int leftH = 0,rightH = 0;
      Node *parent = node->parent;
      
      leftH = BalanceTree(node->getL());
      rightH = BalanceTree(node->getR());
      
      int diff = leftH - rightH;
      if(diff > 1) 
      {
            node = 
            rotateclockwise(node);
      }
      else if( diff < -1)
      {
            node = 
            rotateanticlock(node);
      }
      //@if( diff == 1 && parent->right == node)
            //@node = rotateclockwise(node);
      //@if( diff == -1 && parent->left == node)
            //@node = rotateanticlock(node);

      return maxHeight(node);
}

Node * BinaryTree::rotateclockwise(Node *node)
{
	Node *left = node->getL();
	Node *parent = node->getP();

	if(parent == NULL)
      {
            root = left;root->parent=NULL;
      }
      else if ( parent->left == node)
            parent->setL(left);
      else if ( parent->right == node)
            parent->setR(left);
	//@if( alchild->getL() == NULL) { return invert(node,alchild,alchild->getR()); }

      Node *right = left->getR();
      left->setR(node);
      node->setL(right);
	return left;
}

Node * BinaryTree::rotateanticlock(Node *node)
{
	Node *right = node->getR();
	Node *parent = node->getP();

	if(parent == NULL) 
      {
            root = right;
            root->parent = NULL;
      }
      else if ( parent->left == node)
            parent->setL(right);
      else if ( parent->right == node)
            parent->setR(right);
	//@//if( archild->getR() == NULL) { return invert(node,archild,archild->getL()); }

      Node *left = right->getL();
      right->setL(node);
      node->setR(left);
      
	return right;
}

void BinaryTree::printInorder(Node *node)
{
	if(node == NULL) return;;
	printInorder(node->getL());
	std::cout<<"->"<<node->getData();
	printInorder(node->getR());
}
void BinaryTree::printPreorder(Node *node)
{
	if(node == NULL) return;
      
      Node *parent = node->parent;
      
      std::cout<<node->getData()<<"("<<
      ((parent)?parent->data:0)
      <<")"<<"->[";

	printPreorder(node->getL());
      
      std::cout<<",";
      
	printPreorder(node->getR());
      std::cout<<"]";

}


bool BinaryTree::search(int data,Node *root)
{
	if( root == NULL ) return false;
	if( root->getData() == data) return true;
	else if(root->getData() < data) return search(data,root->getR());
	else return search(data,root->getL());
}

