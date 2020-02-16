
#include <unordered_map>

class NodeCopyFactory
{
public:
    NodeCopyFactory():
        mObjectTable()
    {
    }
    
    // Lookup for this should be O(1) since we are using an unordered map, which has lookup time of O(1)
    Node* getCopy(const Node* original)
    {
        Node* ret = nullptr;
        
        if(original != nullptr)
        {
            auto it = mObjectTable.find(original);

            // Object has not been cloned yet
            if( it == mObjectTable.end())
            {
                ret = new Node(0);
                mObjectTable[original] = ret;
            }
            // Otherwise, return the reference to it
            else
            {
                ret = it->second;
            }
        }

        return ret;
    }
    
private:
    std::unordered_map<const Node*, Node*> mObjectTable;
};

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution 
{
public:
    Node* copyRandomList(Node* head) 
    {
        // We need a data structure that tracks association between the old address and the new address, lets call this
        // The "object table"
        NodeCopyFactory object_table;

        Node* current_node_original = head;
        Node* current_node_copy     = nullptr;
        Node* copied_head           = object_table.getCopy(head);

        // For each node until the end - O(n)
        while(current_node_original != nullptr)
        {
            // Copy, or obtain reference to the original
            current_node_copy = object_table.getCopy(current_node_original);
        
            // Copy the value attribute
            current_node_copy->val = current_node_original->val;
            
            // Copy, or obtain reference to next
            current_node_copy->next = object_table.getCopy(current_node_original->next);
                        
            // Copy, or obtain reference to random
            current_node_copy->random = object_table.getCopy(current_node_original->random);

            // Move on
            current_node_original = current_node_original->next;
        }

        return copied_head;
    }
};
