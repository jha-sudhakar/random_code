#include <stack>
using namespace std; 

// Submitted code on hackerrank and leetcode

/* you only have to complete the function given below.  
Node is defined as  

struct node
{
int data;
node* left;
node* right;
};

*/

void Inorder(node *root)
{
	if(root == NULL)
		return;

	int prev_size=0, cur_size =1;;
	stack<node*> st;
	st.push(root);

	while(!st.empty())
	{
		prev_size = cur_size;
		cur_size = st.size();

		node* tmp = st.top();
		if(tmp->left != NULL && (prev_size <= cur_size))
		{
			st.push(tmp->left);
		} else
		{
			st.pop();
			cout << tmp->data << " ";
			if(tmp->right != NULL)
				st.push(tmp->right);
		}
	}
}

