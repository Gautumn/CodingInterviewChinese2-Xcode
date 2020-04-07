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

// 面试题31：栈的压入、弹出序列
// 题目：输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是
// 否为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1、2、3、4、
// 5是某栈的压栈序列，序列4、5、3、2、1是该压栈序列对应的一个弹出序列，但
// 4、3、5、1、2就不可能是该压栈序列的弹出序列。

#include <cstdio>
#include <stack>


#define Method 0


#if Method == 0
bool IsPopOrder(const int* pPush, const int* pPop, int nLength) {
    bool popOrder = false;
    
    if (pPush != nullptr && pPop != nullptr && nLength > 0) {
        const int* pPushNext = pPush;
        const int* pPopNext = pPop;
        std::stack<int> st;
        while (pPopNext - pPop < nLength) {
            while (st.empty() || st.top() != *pPopNext) {
                st.push(*pPushNext);
                pPushNext++;
                
                if (pPushNext - pPush >= nLength)
                    break;
            }
            
            if (st.top() != *pPopNext)
                break;
            
            st.pop();
            pPopNext++;
        }
        
        if (st.empty() && (pPopNext - pPop == nLength))
            popOrder = true;
    }
    
    return popOrder;
    
    return popOrder;
}



#elif Method == 3
/*
 如题：所有数字均不相等
 思路：需要一个栈，然后将序列压入到栈中，
 1. 不断将序列压入到栈中，当栈顶元素和弹出的序列相同的时候结束
 2. 将该元素弹出，同时修改制定的弹出顺序到下一个
 3. 继续1，2的操作
 
 当所有序列都压入到栈中，但弹出序列依然没有结束，表示不是弹出序列
 如果栈内元素空了，并且弹出序列结束，则是一个弹出序列
 */

bool IsPopOrder(const int* pPush, const int* pPop, int nLength)
{
    bool bPossible = false;

    if(pPush != nullptr && pPop != nullptr && nLength > 0)
    {
        // 注意使用const
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;

        std::stack<int> stackData;

        while(pNextPop - pPop < nLength)
        {
            // 当辅助栈的栈顶元素不是要弹出的元素
            // 先压入一些数字入栈
            while(stackData.empty() || stackData.top() != *pNextPop)
            {
                // 如果所有数字都压入辅助栈了，退出循环
                if(pNextPush - pPush == nLength)
                    break;

                stackData.push(*pNextPush);

                pNextPush ++;
            }

            if(stackData.top() != *pNextPop)
                break;

            stackData.pop();
            pNextPop ++;
        }

        if(stackData.empty() && pNextPop - pPop == nLength)
            bPossible = true;
    }

    return bPossible;
}

#endif

// ====================测试代码====================
void Test(const char* testName, const int* pPush, const int* pPop, int nLength, bool expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(IsPopOrder(pPush, pPop, nLength) == expected)
        printf("Passed.\n");
    else
        printf("failed.\n");
}

void Test1()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {4, 5, 3, 2, 1};
    
    Test("Test1", push, pop, nLength, true);
}

void Test2()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {3, 5, 4, 2, 1};
    
    Test("Test2", push, pop, nLength, true);
}

void Test3()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {4, 3, 5, 1, 2};
    
    Test("Test3", push, pop, nLength, false);
}

void Test4()
{
    const int nLength = 5;
    int push[nLength] = {1, 2, 3, 4, 5};
    int pop[nLength] = {3, 5, 4, 1, 2};
    
    Test("Test4", push, pop, nLength, false);
}

// push和pop序列只有一个数字
void Test5()
{
    const int nLength = 1;
    int push[nLength] = {1};
    int pop[nLength] = {2};

    Test("Test5", push, pop, nLength, false);
}

void Test6()
{
    const int nLength = 1;
    int push[nLength] = {1};
    int pop[nLength] = {1};

    Test("Test6", push, pop, nLength, true);
}

void Test7()
{
    Test("Test7", nullptr, nullptr, 0, false);
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

