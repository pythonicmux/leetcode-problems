/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    struct lcaData {
        bool sawP = false;
        bool sawQ = false;
        TreeNode* lca = NULL;
    };
    
    /*
    The lowest common ancestor of p and q in a tree is the lowest node such 
    that both p and q are a child of the node.
    
    In that case, we can use one pass of DFS to find the LCA. 
    
    When we DFS down the tree, we go depth-first- therefore at some node x, 
    we're guaranteed that all children of x are explored before x. Then, 
    we just have to find the first x such that p and q are both seen after the DFS 
    returns at x.
    */
    lcaData findLca(TreeNode* root, TreeNode* p, TreeNode* q) {
        auto sol = lcaData();
        
        // If we've reached the bottom of the tree then we haven't 
        // seen p, q or found the LCA.
        if(root == NULL) {
            return sol;
        } 
        
        // Look at all children of root.
        auto left = findLca(root->left, p , q);
        auto right = findLca(root->right, p , q);
        
        // If we're at p or q then we've seen p or q at the root.
        if(root == p) sol.sawP = true;
        if(root == q) sol.sawQ = true;
        
        // If p or q was seen in the DFS (i.e. p or q is a child) then mark it as such.
        sol.sawP |= left.sawP;
        sol.sawQ |= left.sawQ;
        sol.sawP |= right.sawP;
        sol.sawQ |= right.sawQ;
        
        // First, we defer to the DFS calls to see if the LCA is a child of root. 
        // If none of the calls to the DFS returned the LCA but we've seen both p and q 
        // then root must be the LCA.
        if(left.lca) sol.lca = left.lca;
        else if(right.lca) sol.lca = right.lca;
        else if(sol.sawP && sol.sawQ) {
            sol.lca = root;
        }
        
        return sol;
    }
    
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return findLca(root, p, q).lca;
    }
};
