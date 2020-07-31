#ifndef BINARYTREETRAVERSAL_H
#define BINARYTREETRAVERSAL_H

/*
 * 二叉树的后序遍历
 * 给定一个二叉树，返回它的 后序 遍历。
 * 前序: 根左右的遍历方式
 * 后序: 左右根的遍历方式
 */

#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>
#include <queue>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 将前序遍历的模型，进行修改，使其成根右左，再最后加上reverse进行反转，得到左右根，即使后序遍历
std::vector<int> postorderTraversal(TreeNode* root) {
    std::vector<int> ret;
    std::stack<TreeNode*> stk;
    TreeNode* cur = root;
    while(cur || stk.size()) {
        while(cur) {
            stk.push(cur);
            ret.push_back(cur->val); //根
            cur = cur->right; //右
        }
        cur = stk.top();
        stk.pop();
        cur = cur->left; //左
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

std::vector<int> ret;
std::vector<int> postorder_recursion(TreeNode* root) {
    if(root) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        ret.push_back(root->val);
    }
    return ret;
}


/*
 * 给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
 * 示例：
 * 二叉树：[3,9,20,null,null,15,7],
 *  3
 * / \
 *9  20
 *  /  \
 * 15   7
 * 返回其层次遍历结果：
 * [
 *   [3],
 *   [9,20],
 *   [15,7]
 * ]
 */

std::vector<std::vector<int>> levelOrder(TreeNode* root) {
    std::vector <std::vector <int>> ret;
    if (!root) return ret;

    std::queue <TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int currentLevelSize = q.size();
        ret.push_back(std::vector <int> ());
        for (int i = 1; i <= currentLevelSize; ++i) {
            auto node = q.front(); q.pop();
            ret.back().push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }

    return ret;
}



#endif // BINARYTREETRAVERSAL_H
