#ifndef INVERTBINARYTREE_H
#define INVERTBINARYTREE_H

/* 翻转一棵二叉树。
 * 示例：
 * 输入：
 *      4
 *    /   \
 *   2     7
 *  / \   / \
 * 1   3 6   9
 * 输出：
 *      4
 *    /   \
 *   7     2
 *  / \   / \
 * 9   6 3   1
 *
 */

#include <algorithm>
#include <utility>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* invertTree(TreeNode* root) {
    if(!root) return nullptr;

    root->left = invertTree(root->left);
    root->right = invertTree(root->right);
    std::swap(root->left, root->right);

    return root;
}


#endif // INVERTBINARYTREE_H
