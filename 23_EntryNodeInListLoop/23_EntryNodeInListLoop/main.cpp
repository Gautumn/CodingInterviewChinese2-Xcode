/*******************************************************************
Copyright(c) 2016, Harry He
All rights reserved.

Distributed under the BSD license.
(See accompanying file LICENSE.txt at
https://github.com/zhedahht/CodingInterviewChinese2/blob/master/LICENSE.txt)
*******************************************************************/

//==================================================================
// 《剑指Offer——名企面试官精讲典型编程题》代码
// 作者：何海涛
//==================================================================

// 面试题23：链表中环的入口结点
// 题目：一个链表中包含环，如何找出环的入口结点？例如，在图3.8的链表中，
// 环的入口结点是结点3。

#include <cstdio>
#include "List.h"


#define Method 2


#if Method == 0




ListNode* MeetingNode(ListNode* pHead) {
    if (pHead == nullptr) return nullptr;
    
    ListNode* pSlow = pHead;
    ListNode* pFast = pHead->m_pNext;
    if (pFast == nullptr) return nullptr;
    
    while (pFast != nullptr && pSlow != nullptr) {
        // 相遇
        if (pSlow == pFast) return pFast;
        
        // 走一步
        pSlow = pSlow->m_pNext;
        
        // 走两步
        pFast = pFast->m_pNext;
        if (pFast != nullptr)
            pFast = pFast->m_pNext;
    }
    
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead) {
    if (pHead == nullptr) return nullptr;
    
    // 判断链表中是否存在环
    ListNode* meetingNode = MeetingNode(pHead);
    if (meetingNode == nullptr) return nullptr;
    
    // 找环中有几个节点
    int nodesInLoop = 1;
    ListNode* pNode = meetingNode;
    while (pNode->m_pNext != meetingNode) {
        nodesInLoop++;
        pNode = pNode->m_pNext;
    }
    
    // 找环的入口
    ListNode* pFast = pHead;
    for (int i = 0; i < nodesInLoop; i++) {
        pFast = pFast->m_pNext;
    }
    ListNode* pSlow = pHead;
    while (pSlow != pFast) {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
    }
    
    return pFast;
}


#elif Method == 2
/*
思路：
1. 判断当前链表是否有环，采用的办法是：用一快，一慢两个指针，
   1）当快速的和慢速的相遇的时候表示有环
   2）当快速的走到空了，还没有相遇表示无环
2. 有环的情况下，我们看一下这个环里有几个节点 --- 用 n 表示，因为上一步返回的两个指针相遇的节点肯定在环中。
3. 基本信息都掌握了，那么我们可以知道环的入口在哪里了。
   1）先用一个指针前进 n 个节点
   2）在用另一个指针从头节点开始，然后两个指针一起移动，直到两个指针相遇
   3）相遇的节点就是换的入口节点

例子：
          ----------------
          |              |
          V              |
1 -> 2 -> 3 -> 4 -> 5 -> 6

   上图中，我们知道环中有 4 个节点，然后用两个指针前后相遇的办法找到环的入口
   
          ----------------
          |              |
          V              |
1 -> 2 -> 3 -> 4 -> 5 -> 6
^                   ^
|                   |
P2                  P1

*/
ListNode* MeetingNode(ListNode* pHead) {
    if (pHead == nullptr) return nullptr;
    
    ListNode* pSlow = pHead;
    ListNode* pFast = pHead->m_pNext;
    if (pFast == nullptr) return nullptr;
    
    while (pFast != nullptr && pSlow != nullptr) {
        // 相遇
        if (pSlow == pFast) return pFast;
        
        // 走一步
        pSlow = pSlow->m_pNext;
        
        // 走两步
        pFast = pFast->m_pNext;
        if (pFast != nullptr)
            pFast = pFast->m_pNext;
    }
    
    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead) {
    if (pHead == nullptr) return nullptr;
    
    // 判断链表中是否存在环
    ListNode* meetingNode = MeetingNode(pHead);
    if (meetingNode == nullptr) return nullptr;
    
    // 找环中有几个节点
    int nodesInLoop = 1;
    ListNode* pNode = meetingNode;
    while (pNode->m_pNext != meetingNode) {
        nodesInLoop++;
        pNode = pNode->m_pNext;
    }
    
    // 找环的入口
    ListNode* pFast = pHead;
    for (int i = 0; i < nodesInLoop; i++) {
        pFast = pFast->m_pNext;
    }
    ListNode* pSlow = pHead;
    while (pSlow != pFast) {
        pSlow = pSlow->m_pNext;
        pFast = pFast->m_pNext;
    }
    
    return pFast;
}



#elif Method == 3

ListNode* MeetingNode(ListNode* pHead)
{
    if(pHead == nullptr)
        return nullptr;

    ListNode* pSlow = pHead->m_pNext;
    if(pSlow == nullptr)
        return nullptr;

    ListNode* pFast = pSlow->m_pNext;
    while(pFast != nullptr && pSlow != nullptr)
    {
        if(pFast == pSlow)
            return pFast;

        pSlow = pSlow->m_pNext;

        pFast = pFast->m_pNext;
        if(pFast != nullptr)
            pFast = pFast->m_pNext;
    }

    return nullptr;
}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
    ListNode* meetingNode = MeetingNode(pHead);
    if(meetingNode == nullptr)
        return nullptr;

    // 得到环中结点的数目
    int nodesInLoop = 1;
    ListNode* pNode1 = meetingNode;
    while(pNode1->m_pNext != meetingNode)
    {
        pNode1 = pNode1->m_pNext;
        ++nodesInLoop;
    }

    // 先移动pNode1，次数为环中结点的数目
    pNode1 = pHead;
    for(int i = 0; i < nodesInLoop; ++i)
        pNode1 = pNode1->m_pNext;

    // 再移动pNode1和pNode2
    ListNode* pNode2 = pHead;
    while(pNode1 != pNode2)
    {
        pNode1 = pNode1->m_pNext;
        pNode2 = pNode2->m_pNext;
    }

    return pNode1;
}

#endif

// ==================== Test Code ====================
void Test(char* testName, ListNode* pHead, ListNode* entryNode)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(EntryNodeOfLoop(pHead) == entryNode)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

// A list has a node, without a loop
void Test1()
{
    ListNode* pNode1 = CreateListNode(1);

    Test("Test1", pNode1, nullptr);

    DestroyList(pNode1);
}

// A list has a node, with a loop
void Test2()
{
    ListNode* pNode1 = CreateListNode(1);
    ConnectListNodes(pNode1, pNode1);

    Test("Test2", pNode1, pNode1);

    delete pNode1;
    pNode1 = nullptr;
}

// A list has multiple nodes, with a loop
void Test3()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode3);

    Test("Test3", pNode1, pNode3);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, with a loop
void Test4()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode1);

    Test("Test4", pNode1, pNode1);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, with a loop
void Test5()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);
    ConnectListNodes(pNode5, pNode5);

    Test("Test5", pNode1, pNode5);

    delete pNode1;
    pNode1 = nullptr;
    delete pNode2;
    pNode2 = nullptr;
    delete pNode3;
    pNode3 = nullptr;
    delete pNode4;
    pNode4 = nullptr;
    delete pNode5;
    pNode5 = nullptr;
}

// A list has multiple nodes, without a loop
void Test6()
{
    ListNode* pNode1 = CreateListNode(1);
    ListNode* pNode2 = CreateListNode(2);
    ListNode* pNode3 = CreateListNode(3);
    ListNode* pNode4 = CreateListNode(4);
    ListNode* pNode5 = CreateListNode(5);

    ConnectListNodes(pNode1, pNode2);
    ConnectListNodes(pNode2, pNode3);
    ConnectListNodes(pNode3, pNode4);
    ConnectListNodes(pNode4, pNode5);

    Test("Test6", pNode1, nullptr);

    DestroyList(pNode1);
}

// Empty list
void Test7()
{
    Test("Test7", nullptr, nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}
