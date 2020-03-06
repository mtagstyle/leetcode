/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <queue>

typedef struct QueueItem
{
    int       mOriginalValue;
    TreeNode* mOriginalNode;
    
} QueueItem_t;

bool operator < (const QueueItem_t& lhs, const QueueItem_t& rhs)
{
    return lhs.mOriginalValue < rhs.mOriginalValue;
}

bool hasGrandChildren(TreeNode* node)
{
    bool result = false;
    
    if( node->left        || 
        node->right       || 
        node->left->left  || 
        node->left->right || 
        node->right->left ||
        node->right->right )
    {
        result = true;
    }
    
    return result;
}

void DFS(TreeNode* current_node, std::priority_queue<QueueItem_t>& heap)
{
    heap.emplace(QueueItem_t({current_node->val, current_node}));
    if(current_node->right != nullptr)
    {
        DFS(current_node->right, heap);
    }
    if(current_node->left != nullptr)
    {
        DFS(current_node->left, heap);
    }
}

class Solution 
{
public:
    TreeNode* bstToGst(TreeNode* root) 
    {
        // First get an ordered priority queue of largest to smallest O(n), where n is the number of nodes
        std::priority_queue<QueueItem_t> heap;
        DFS(root, heap);
        
        // Start popping values off the heap, from largest->smallest O(n)
        int totalSum = 0;
        while(!heap.empty())
        {
            // Begin to add each item to a running sum and modify the current node with said value
            QueueItem_t item = heap.top();
            heap.pop();
            totalSum += item.mOriginalValue;
            
            item.mOriginalNode->val = totalSum;
        }
        
        // Overall complexity is O(n)
        return root;
    }
};
