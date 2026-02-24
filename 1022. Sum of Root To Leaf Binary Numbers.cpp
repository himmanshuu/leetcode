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
    int sumRootToLeaf(TreeNode* root) {
        queue<pair<TreeNode*,int>> q;
        q.push({root, root->val});
        int result = 0;
        while(!q.empty()){
            auto [node, prev] = q.front();
            q.pop();
            if(!node->left && !node->right){
                result += prev;
            }
            if(node->left){
                int val = (prev << 1) + node->left->val;     
                q.push({node->left, val});
            }

            if(node->right){
                int val = (prev << 1) + node->right->val;
                q.push({node->right, val});
            } 
        }
        return result;
    }
};