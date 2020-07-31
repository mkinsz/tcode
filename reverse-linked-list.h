#ifndef REVERSELINKEDLIST_H
#define REVERSELINKEDLIST_H

/**
 * 反转一个单链表。
 * 示例:
 * 输入: 1->2->3->4->5->NULL
 * 输出: 5->4->3->2->1->NULL
 * 进阶: 你可以迭代或递归地反转链表。你能否用两种方法解决这道题？
 */

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 迭代
ListNode* reverse(ListNode* head) {
    ListNode* cur = nullptr, * pre = head;
    while(pre) {
        ListNode* tmp = pre->next;
        pre->next = cur;
        cur = pre;
        pre = tmp;
    }
    return cur;
}

// 递归
ListNode* recursion(ListNode* head) {
    if(!head || !head->next) return head;

    auto p = recursion(head->next);
    head->next->next = head;
    head->next = nullptr;
    return p;
}


#endif // REVERSELINKEDLIST_H
