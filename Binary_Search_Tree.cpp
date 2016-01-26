#include <stdlib.h>
#include <iostream>
#include <stdio.h>

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
	struct node* root;
	struct node* create_node(myint ele);
	void print_inorder();
public:
	BST();
	void insert(myint e);
	bool find(const myint e);
	bool find_min(myint& min);
	bool find_max(myint& max);
	void print_inorder_traversal();
};


BST::BST()
{
	root = NULL;
}


struct node* BST:: create_node(myint ele)
{
	struct node *tmp = new node();
	tmp->val = ele;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}


void BST::insert(const myint e)
{
	struct node* tmp = create_node(e);
	if(NULL == root)
	{
		root = tmp;
		return ;
	}

	struct node **cur= &root;
	while(NULL != *cur)
	{
		if(*cur == NULL)
		{
			*cur == tmp;
			return ;
		} else if ((*cur)-> val >  e)
		{
			cur = &((*cur)->left);
		} else
		{
			cur = &((*cur)->right);
		}
	}
}


bool BST::find(const myint e)
{
	struct node *cur= root;
    while(NULL != cur)
    {
        if(cur->val == e)
        {
            return true;
        } else if (cur->val >  e)
        {
            cur = cur->left;
        } else
        {
            cur = cur->right;
        }
    }
	return false;
}

bool BST::find_min(myint& min)
{
	if(NULL == root)
	{
		return false;
	}

    struct node *cur= root, *prev= NULL;
    while(NULL != cur)
    {
		prev = cur;    
        cur = cur->left;
    }
	min = prev->val;
	return true;

}

bool BST::find_max(myint& max)
{
    if(NULL == root)
    {
        return false;
    }

    struct node *cur= root, *prev= NULL;
    while(NULL != cur)
    {
        prev = cur;
        cur = cur->right;
    }
    max = prev->val;

	return true;
}

void BST::print_inorder(struct node* cur_node)
{
	if(cur_node == NULL)
	{
		return;
	}
	print_inorder(cur_node->left);
	cout<<"\b " << cur_node->val;
	print_inorder(cur_node->right);
}

void BST::print_inorder_traversal()
{
	cout<<"\nInorder--> ";
	return print_inorder(root);
	cout<<"\n
}


int main(int argc, char* argv[])
{

BST obj;
if(argc > 2)
{
	int i=1;
	while(i < argc)
	{
		obj.inser(atoi(argv[i]);
	}
}

//1:- Print inorder traversal.
obj.print_inorder_traversal();

//2:- Print min.
int val= -9999; obj.find_min(val); cout<<"\n Min = " << val;

//3:- Print max.
int val= 9999; obj.find_max(val); cout<<"\n Max = " << val;

cout<<"\n";
return 0;
};
