#include <stdio.h>
#include <vector>
#include <list>
using namespace std;


#if 1
 // Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
#endif
class Solution
{
	public:
		vector<int> postorderTraversal(TreeNode* root)
		{
			vector<int> po;
			if(root == NULL)
				return po;
			list<TreeNode*> q;
			q.push_back(root);
			TreeNode* prev_node = NULL;
			while(q.size())
			{
				TreeNode* cur = q.front();
				if((cur->left == NULL && cur->right == NULL) ||
					((prev_node != NULL) && (prev_node == cur->left || prev_node == cur->right)))
				{
					q.pop_front();
					po.push_back(cur->val);
					prev_node = cur;
					continue;
				}

				if(NULL != cur->right)
				{
					q.push_front(cur->right);
				}

				if(NULL != cur->left)
				{
					q.push_front(cur->left);
				}
			}
			return po;
		}		
};
