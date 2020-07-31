#ifndef LINKEDLISTCYCLE_H
#define LINKEDLISTCYCLE_H

/*给定一个链表，判断链表中是否有环。
 * 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 如果 pos 是 -1，则在该链表中没有环。
 *
 * 3 -> 2 -> 0 -> -4
 *      | <-  <-  |
 *
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    if(nullptr == head) return false;

    auto fast = head;
    auto slow = head;

    while(fast) {
        if(!fast->next) return false;
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast) return true;
    }
    return false;
}

#endif // LINKEDLISTCYCLE_H
