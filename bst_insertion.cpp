/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

void DFSInsertion(TreeNode* current_node, int& val)
{
    // LHS
    if(val < current_node->val)
    {
        if(current_node->left == nullptr)
        {
            TreeNode* new_node = new TreeNode();
            new_node->val = val;
            current_node->left = new_node;
        }
        else
        {
            DFSInsertion(current_node->left, val);
        }
    }
    
    // RHS
    if(val > current_node->val)
    {
        if(current_node->right == nullptr)
        {
            TreeNode* new_node = new TreeNode();
            new_node->val = val;
            current_node->right = new_node;
        }
        else
        {
            DFSInsertion(current_node->right, val);
        }
    }
}

class Solution 
{
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) 
    {
        DFSInsertion(root, val);
        
        return root;
    }
};
