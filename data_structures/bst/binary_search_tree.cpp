#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
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
	void print_inorder(struct node** _node);
public:
	BST();
	void insert(myint e);
	bool find(const myint e);
	bool find_min(myint& min);
	bool find_max(myint& max);
	void print_inorder_traversal();
	void find_diameter();
	unsigned int find_diameter(struct node* n, unsigned int& d);
};


BST::BST()
{
	root = NULL;
}


struct node* BST:: create_node(myint ele)
{
	struct node *tmp = new struct node();
	//cout<<"\n **** New returned " << tmp;
	tmp->val = ele;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}


void BST::insert(const myint e)
{
	struct node* tmp = create_node(e);
	//cout<<"\n **** create_new returned " << tmp;
	if(NULL == root)
	{
		//cout<<"\n Inserted " << e <<" as root  ";;
		root = tmp;
		return ;
	}

	struct node *prev= NULL;
	struct node *cur= root;
	while(NULL != cur)
	{
		if (cur->val >  e)
		{
			prev = cur;
			cur = cur->left;
		} else
		{
			prev = cur;
			cur = cur->right;
		}
	}

	if(prev->val > e)
    {
		//cout<<"\n Inserted " << e <<" to the left of " << prev->val;
		prev->left = tmp;
    } else
	{
		//cout<<"\n Inserted " << e <<" to the right of " << prev->val;
		prev->right = tmp;
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

void BST::print_inorder(struct node** cur_node)
{
	if(*cur_node == NULL)
	{
		return;
	}
	print_inorder(&((*cur_node)->left));
	cout<<" " << (*cur_node)->val;
	print_inorder(&((*cur_node)->right));
}

void BST::print_inorder_traversal()
{
	cout<<"\nInorder--> ";
	return print_inorder(&root);
	cout<<"\n";
}


void BST::find_diameter()
{
	unsigned int d=0;
	find_diameter(root, d);
	cout<< d << endl;

}

unsigned int  BST::find_diameter(struct node* n, unsigned int& d)
{
	if(n == NULL)
		return 0;
	unsigned int l = find_diameter(n->left, d);
	unsigned int r = find_diameter(n->right, d);
	if(l+r+1 > d)
		d = 1+l+r;
	if(l>r)
		return 1+l;
	else
		return r+1;
}

int main()
{
	unsigned int T, N, buf;;
	cin >> T;
	for(unsigned int i=0; i<T; i++)
	{
		cin >> N;
		BST obj1;
		for(unsigned int i=0; i<N; i++)
		{
			cin >> buf;
			obj1.insert(buf);
		}
		obj1.find_diameter();
	}

	return 0;
}


/*
int main(int argc, char* argv[])
{
int val = 0;

#if 0
BST obj;
if(argc > 2)
{
	int i=1;
	while(i < argc)
	{
		obj.insert(atoi(argv[i]));
		i++;
	}
}
//1:- Print inorder traversal.
obj.print_inorder_traversal();
//2:- Print min.
val= -9999; obj.find_min(val); cout<<"\n Min = " << val;
//3:- Print max.
val= 9999; obj.find_max(val); cout<<"\n Max = " << val;
cout<<"\n";
#endif

#if 0
//--------------------------------------------------------------------------
BST obj2;

static const int arr[] = {5, 3, 4, 12, 10, 20, 0, 23};
vector<int> v (arr, arr + sizeof(arr) / sizeof(arr[0]) );
cout<<"\n Inserting in BST:- ";
for(int i=0; i<v.size(); i++) 
{ 
	cout<<" "<< v[i]; 
	obj2.insert(v[i]);
}
cout<<"\n";
//1:- Print inorder traversal.
obj2.print_inorder_traversal();
sort(v.begin(), v.end());
cout<<"\nSorted arr=";
for(int i=0; i<v.size() ; i++)
cout<<" " << v[i];

//2:- Print min.
val= -9999; obj2.find_min(val); cout<<"\nBST-Min = " << val;

//3:- Print max.
val= 9999; obj2.find_max(val); cout<<"\nBST-Max = " << val;

cout<<"\n";
//-------------------------------------------------------------------------------
#endif

return 0;
};
*/
