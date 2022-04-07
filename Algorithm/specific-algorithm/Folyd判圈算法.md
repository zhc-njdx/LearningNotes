### Folyd判圈算法



#### 1、概述

Folyd Cycle Detection Algorithm，可以在有限状态机、迭代函数或者链表上判断是否存在环，以及判断环的起点和长度的算法



#### 2、过程

##### 1）判断是否有环

> 如果存在环，那么兔子一定能和乌龟相遇，且兔子比乌龟多跑的距离为环长度的整数倍

使用快慢指针，快指针每次2个步，慢指针每次1步。**当快慢指针相遇时，则说明链表中存在环；**如果快指针直接走到终点，则不存在环。



##### 2）求环的长度

第一次相遇，快慢指针都在环上，下一次相遇时，快指针比慢指针刚好多走一圈。

**所以只需要统计快慢指针在这两次相遇之间走过的路程差，即为环的长度。**



##### 3）求环的起点

设链表起点到环的起点的距离为m，环的长度为n，相遇点距离环的入口为k，相遇时满指针走过的距离为i。

则有下面式子

慢指针：i = m + a * n + k

快指针：2 * i = m + b * n + k

相减可得：i = (b-a)*n，即 i 是环长度的整数倍

**此时，将其中一个指针(假设为慢指针)放回链表起点，两个指针都每次走一步，再次相遇时（走了m步），一定在环的起点。**

由于环的起点位置是两者相遇的最早位置，只需要说明快指针走了m步后会出现在环的起点位置即可。走了m步后，快指针共走了 2 * i + m 步，由于 i 为环长度的倍数，所以快指针应该在环的起点位置，与慢指针相遇。



代码以leetcode141题(判断是否存在环)为例

```cpp
bool hasCycle(ListNode *head){
    ListNode* slow = head;
    ListNode* quick = head;
    while (true){
        if (slow == nullptr || quick == nullptr){
            return false;
        }

        slow = slow->next;
        quick = quick->next;
        if (quick != nullptr){
            quick = quick->next;
        } else {
            return false;
        }

        if (slow == quick){
            return true;
        }
    }
}
```

