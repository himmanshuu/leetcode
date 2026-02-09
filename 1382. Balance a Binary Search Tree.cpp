/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> nodes;
    void preOrderTraversal(TreeNode *root){
        if(!root) return;
        preOrderTraversal(root->left);
        nodes.push_back(root);
        preOrderTraversal(root->right);
    }
    TreeNode* helper(int l, int r){
        if(l > r) return nullptr;
        // if(l == r){
        //     nodes[l]->left = nullptr; nodes[l]->right = nullptr;
        //     return nodes[l];
        // }
        int mid = (l+r) >> 1;
        // TreeNode* root = nodes[mid];
        nodes[mid]->left = helper(l, mid-1);
        nodes[mid]->right = helper(mid+1, r);
        return nodes[mid];
    }
    TreeNode* balanceBST(TreeNode* root) {
        preOrderTraversal(root);
        int n = nodes.size();
        // cout<<n<<endl;
        TreeNode* r = helper(0, n-1);
        return r ;
    }
};