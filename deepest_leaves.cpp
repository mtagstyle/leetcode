/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

int BFS(queue<TreeNode*>& q)
{
    queue<TreeNode*> tmp_q;
    
    int sum = 0;
    // Keep popping items off of the current level
    while(!q.empty())
    {
        TreeNode* tmp = q.front();
        
        sum += tmp->val;

        if(tmp->left != nullptr)
        {
            tmp_q.push(tmp->left);
        }
        
        if(tmp->right != nullptr)
        {
            tmp_q.push(tmp->right);
        }
        
        q.pop();
    }
    
    // If there are no items on the next level, it must mean we are at the deepest
    if(tmp_q.empty())
        return sum;
    else
        return BFS(tmp_q);
}

int BFS(TreeNode* root)
{
    queue<TreeNode*> q;
    q.push(root);
    return BFS(q);
}

class Solution 
{
public:
    int deepestLeavesSum(TreeNode* root) 
    {
        // Do a BFS and add all of the leaves on the last level of the BFS
        return BFS(root);
    }
};
