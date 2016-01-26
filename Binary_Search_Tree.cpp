#include <stdlib.h>
#include <iostream>

using namespace std;
typedef int myint;

struct node
{
myint val;
struct node* left;
struct node* right;
};

class BST
{

private:
	struct node* create_node(myint ele);

public:
	void insert(myint e);
	bool find(const myint e);
	bool find_min(myint& min);
	bool find_max(myint& max);
};

struct node* BST:: create_node(myint ele)
{
	struct node *tmp = new node();
	tmp->val = ele;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}


void BST::insert(myint e)
{


}


bool BST::find(const myint e)
{

	return true;
}

bool BST::find_min(myint& min)
{

return true;
}

bool BST::find_max(myint& max)
{

return true;
}


int main()
{


return 0;
};
