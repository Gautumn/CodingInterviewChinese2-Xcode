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

// 面试题18（一）：在O(1)时间删除链表结点
// 题目：给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该
// 结点。


#include <cstdio>
#include "List.h"



#define Method  0




#if Method == 0

void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted) {
    if (pListHead == nullptr || *pListHead == nullptr || pToBeDeleted == nullptr)
        return;
    
    // 被删除节点不是尾节点，采用拷贝
    // 注意：即使被删除的节点是头节点，这个方法也试用，因为这个办法没有改变头结点的值。
    if (pToBeDeleted->m_pNext != nullptr) {
        ListNode* pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pNext->m_nValue;
        pToBeDeleted->m_pNext  = pNext->m_pNext;
        
        delete pNext;
        pNext = nullptr;
    }
    // 被删除的是头节点，并且链表只有头结点一个节点
    else if (*pListHead == pToBeDeleted) {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        // 注意：pToBeDeleted只是头指针的一个拷贝，修改pToBeDeleted不代表修改了头指针。
        *pListHead = nullptr;
    }
    // 被删除的是链表的最后一个节点，发生退化，仍需遍历链表找到被删除节点的前一个节点。
    else {
        ListNode* pNode = *pListHead;
        
        // 无法知道该节点是否在当前链表中，为防止死循环，加入!=nullptr 判断
        while (pNode != nullptr && pNode->m_pNext != pToBeDeleted)
            pNode = pNode->m_pNext;
        pNode->m_pNext = nullptr;
        
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}













#elif Method == 3
// 分析：
/*
 我们遍历链表，找到该节点的前一个节点，时间复杂度是O(n)，显然不符合题目中O(1)的要求
 采用的办法是被删除的节点 拷贝 下一个节点的内容，然后删除下一个节点。（就是复制一个）
 
 当然如果被删除的节点是最后一个节点，因为其没有下一个节点，所以上面的办法是无效的。
 这种情况，就会发生退化，我们还是要遍历整个链表，进行删除。
 */
void DeleteNode(ListNode** pListHead, ListNode* pToBeDeleted) {
    if (pListHead == nullptr || *pListHead == nullptr || pToBeDeleted == nullptr)
        return;
    
    // 被删除节点不是尾节点，采用拷贝
    // 注意：即使被删除的节点是头节点，这个方法也试用，因为这个办法没有改变头结点的值。
    if (pToBeDeleted->m_pNext != nullptr) {
        ListNode* pNext = pToBeDeleted->m_pNext;
        pToBeDeleted->m_nValue = pNext->m_nValue;
        pToBeDeleted->m_pNext  = pNext->m_pNext;
        
        delete pNext;
        pNext = nullptr;
    }
    // 被删除的是头节点，并且链表只有头结点一个节点
    else if (*pListHead == pToBeDeleted) {
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
        // 注意：pToBeDeleted只是头指针的一个拷贝，修改pToBeDeleted不代表修改了头指针。
        *pListHead = nullptr;
    }
    // 被删除的是链表的最后一个节点，发生退化，仍需遍历链表找到被删除节点的前一个节点。
    else {
        ListNode* pNode = *pListHead;
        
        // 无法知道该节点是否在当前链表中，为防止死循环，加入!=nullptr 判断
        while (pNode != nullptr && pNode->m_pNext != pToBeDeleted)
            pNode = pNode->m_pNext;
        pNode->m_pNext = nullptr;
        
        delete pToBeDeleted;
        pToBeDeleted = nullptr;
    }
}


#endif

// ====================测试代码====================
void Test(ListNode* pListHead, ListNode* pNode)
{
    printf("The original list is: \n");
    PrintList(pListHead);

    printf("The node to be deleted is: \n");
    PrintListNode(pNode);

    DeleteNode(&pListHead, pNode);
    
    printf("The result list is: \n");
    PrintList(pListHead);
}

// 链表中有多个结点，删除中间的结点
void Test1()
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

    Test(pNode1, pNode3);

    DestroyList(pNode1);
}

// 链表中有多个结点，删除尾结点
void Test2()
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

    Test(pNode1, pNode5);

    DestroyList(pNode1);
}

// 链表中有多个结点，删除头结点
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

    Test(pNode1, pNode1);

    DestroyList(pNode1);
}

// 链表中只有一个结点，删除头结点
void Test4()
{
    ListNode* pNode1 = CreateListNode(1);

    Test(pNode1, pNode1);
}

// 链表为空
void Test5()
{
    Test(nullptr, nullptr);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();

    return 0;
}

