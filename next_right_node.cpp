/*
A solution for the problem "Populating next right pointers in each node II", at
https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/

The problem involves connecting each node in an arbitrary binary tree to 
its next right node. This problem gave me a lot of trouble the first time 
I saw it in an interview, and it's a classic question, especially when 
done iteratively and with constant memory. 

Without constant memory, the solution is trivial- connecting each node 
to its right looks a lot like a BFS walk of the tree. Indeed, one modified BFS on the tree with a queue would solve the problem with linear memory.

However, with constant memory, we're tasked with doing the BFS walk without a queue and only with some pointers. The key to solving this problem in constant memory is to remember that at each level the current node is on, the level before is completely connected with next pointers!

This way we can find the next node by keeping a second "parent" pointer on the level above the level of our current node and we can find the next node by looking at the children of the parent pointer. We can travel across the pointers to do our BFS walk.

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

class Solution {
public:
    /*
    We connect all nodes to their next right node by following 
    the BFS path down the tree.
    
    We keep track of the current node in the tree and node->next's parent 
    as we go down the tree, so that we can connect the current node 
    to its next on the same level, as node->next will the be child of some node 
    to the right of the parent of the node (or the parent).
    
    The invariant that allows this program to work is that at level n, 
    all nodes in level n-1 will be connected, allowing us to find the parent 
    of the next node for the node we are on.
    */
    Node* connect(Node* root) {
        if(root == NULL) return root;
        
        // The current node we are on; we start at root.
        Node* curr = root;
        // The parent of curr->next; if it is NULL we have reached 
        // the end of the level, like at root (the initial level).
        Node* right_parent = NULL;
        
        // We need to keep track of the first node in the next level 
        // as we can only go right when traversing the tree. Initially, 
        // it must be the leftmost child of root.
        Node* next_level_start = NULL; 
        
        // We need the start of the last level to know what the 
        // value of right_parent is when curr goes to the next level.
        // In this case, if we go into the second level, our last level's 
        // start is root.
        Node* last_level_start = root;
        
        
        while(curr != NULL) {
            /*
            if(right_parent == NULL) {
                printf("curr is %d, parent is NULL\n", curr->val);
            } else {
                printf("curr is %d, parent is %d\n", curr->val, right_parent->val);
            }
            */
            
            // If there has been no start of the next level found, 
            // update it if there is a node on the next level.
            if (next_level_start == NULL) {
                if(curr->left) next_level_start = curr->left;
                else if(curr->right) next_level_start = curr->right;
            }
            
            // If there is no right parent then we have reached the end of the 
            // current level and we go to the next level.
            if(right_parent == NULL) {
                curr->next = NULL;
                curr = next_level_start;
                right_parent = last_level_start;
                
                last_level_start = next_level_start;
                next_level_start = NULL;
                continue;
            }
            
            // If there is a parent to curr->next we must figure out 
            // if curr->next is the parent's left, right or if we must go 
            // to parent->next to find curr->next.
            
            if(right_parent->left == curr) {
                // If curr is the left child of the parent then we connect it to the 
                // right if possible or try the next node to the right of the parent.
                if(right_parent->right != NULL) {
                    curr->next = right_parent->right; 
                    curr = curr->next;
                    right_parent = right_parent->next;
                } else {
                    right_parent = right_parent->next;
                }
            } else if(right_parent->right == curr) {
                // If curr is the right child of the parent node 
                // then we move the parent node to the right to find curr->next   
                right_parent = right_parent->next;
            } else {
                // If right_parent does not have curr as a child then 
                // we can assume that its leftmost child (if it exists) 
                // is curr->next. 
                if(right_parent->left != NULL) {
                    curr->next = right_parent->left;
                    curr = curr->next;
                } else if(right_parent->right != NULL) {
                    curr->next = right_parent->right;
                    curr = curr->next;
                    right_parent = right_parent->next;
                } else {
                    // If right_parent has no children then 
                    // we try the next parent to the right.
                    right_parent = right_parent->next;
                }
            }
        }
        
        return root;
    }
};
