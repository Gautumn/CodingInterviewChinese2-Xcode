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

// 面试题40：最小的k个数
// 题目：输入n个整数，找出其中最小的k个数。例如输入4、5、1、6、2、7、3、8
// 这8个数字，则最小的4个数字是1、2、3、4。

#include <cstdio>

#include <set>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

#define Method 0



#if Method == 0

/*
 >>> 方法一： 使用快速排序的Partition 方法
 思路：当partiton返回的索引值是k-1时，则表示区间[0, k-1] = k 是最小的K个，
 时间复杂度O(n) 但需要修改原数组
 */
#include <stdlib.h>
int Random1(int start, int end) {
    return rand() % (end - start + 1) + start;
}

void Swap1(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition1(int* data, int length, int start, int end) {
    if (data == nullptr || length <= 0 || start < 0 || end < 0 || end >= length)
        throw ("Invalid input");
    
    int index = Random1(start, end);
    Swap1(&data[index], &data[end]);
    
    int small = start - 1;
    for (int index = start; index < end; index++) {
        if (data[index] < data[end]) {
            small++;
            if (small != index)
                Swap1(&data[small], &data[index]);
        }
    }
    small++;
    Swap1(&data[small], &data[end]);
    
    return small;
}

void GetLeastNumbers_Solution1(int* input, int n, int* output, int k) {
    if (input == nullptr || n <= 0 || output == nullptr || k <= 0 || k > n)
        return;
    
    int start = 0;
    int end = n - 1;
    int index = Partition1(input, n, start, end);
    while (index != k - 1) {
        
        if (index > k - 1) {
            end = index - 1;
        }
        else {
            start = index + 1;
        }

        index = Partition1(input, n, start, end);
    }
    
    for (int i = 0; i < k; i++)
        output[i] = input[i];
    
}



/*
 >>> 方法二：使用 红黑树，multiset
 
 关于multiset中的比较函数，该函数希望谁在前面就返回true
 比如：
 > greater<int>(a, b)，当 a > b 的时候该函数返回true，所以在 multiset 中大数放在前面
 > less<int>(a, b), 同理，就是小数放在前面
 
The expression comp(a,b), where comp is an object of this type and a and b are key values,
shall return true if a is considered to go before b in the strict weak ordering the function defines.
*/

#include <set>

typedef std::multiset<int, std::greater<int>>  intMultiset;

typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

void GetLeastNumbers_Solution2(const vector<int>& data, intMultiset& output, int k) {
    if (k < 1 || data.size() < k)
        return;
    
    for (const auto n : data) {
        if (output.size() < k)
            output.insert(n);
        else if (n < *output.begin()) {
            output.erase(output.begin());   // 不用 erase(*output.begin()) 是因为可能删了多个。
            output.insert(n);
        }
    }
}


/*
>>> 方法三：使用priority_queue
 
 题目要求是求最小的K个数，那么使用最大堆，当放入的数比堆顶小的时候，放入该数然后从堆顶弹出最大的

关于priority_queue中的比较函数，含义和set的相同，但实际上有些许不同

重点在于这句话：从尾部弹出，实际上被认为是优先队列的头
Elements are popped from the "back" of the specific container, which is known as the top of the priority queue.

比如：
> less<int>(a, b),默认，最大堆，小数在前面，但是由于实现方式的原因，当我们取top()的时候，实际上是容器的”back“
   1，2，3，4，5
   less保证这些数在容器（vector)中是这样排列的，但是由于是从尾部弹出，实际上top确实（5），反而是最大堆。
> greater<int>(a, b)，当 a > b 的时候该函数返回true，所以在 multiset 中大数放在前面

*/

#include <queue> // std::priority_queue
#include <vector>
#include <functional> // std::less

typedef std::priority_queue<int> intPriorityQueue;

void GetLeastNumbers_Solution3(const vector<int>& data, intPriorityQueue& output, int k) {
    if (k < 1 || data.size() < k)
        return;
    
    for (const auto n : data) {
        if (output.size() < k)
            output.push(n);
        else if (n < output.top()) {
            output.pop();
            output.push(n);
        }
    }
}






#elif Method == 100

#include "Array.h"
// ====================方法1====================
void GetLeastNumbers_Solution1(int* input, int n, int* output, int k)
{
    if(input == nullptr || output == nullptr || k > n || n <= 0 || k <= 0)
        return;

    int start = 0;
    int end = n - 1;
    int index = Partition(input, n, start, end);
    while(index != k - 1)
    {
        if(index > k - 1)
        {
            end = index - 1;
            index = Partition(input, n, start, end);
        }
        else
        {
            start = index + 1;
            index = Partition(input, n, start, end);
        }
    }

    for(int i = 0; i < k; ++i)
        output[i] = input[i];
}

// ====================方法2====================

typedef multiset<int, std::greater<int> >            intSet;
typedef multiset<int, std::greater<int> >::iterator  setIterator;

void GetLeastNumbers_Solution2(const vector<int>& data, intSet& leastNumbers, int k)
{
    leastNumbers.clear();

    if(k < 1 || data.size() < k)
        return;

    vector<int>::const_iterator iter = data.begin();
    for(; iter != data.end(); ++ iter)
    {
        if((leastNumbers.size()) < k)
            leastNumbers.insert(*iter);

        else
        {
            setIterator iterGreatest = leastNumbers.begin();

            if(*iter < *(leastNumbers.begin()))
            {
                leastNumbers.erase(iterGreatest);
                leastNumbers.insert(*iter);
            }
        }
    }
}

#endif

// ====================测试代码====================
void Test(const char* testName, int* data, int n, int* expectedResult, int k)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    vector<int> vectorData;
    for(int i = 0; i < n; ++ i)
        vectorData.push_back(data[i]);

    if(expectedResult == nullptr)
        printf("The input is invalid, we don't expect any result.\n");
    else
    {
        printf("Expected result: \n");
        for(int i = 0; i < k; ++ i)
            printf("%d\t", expectedResult[i]);
        printf("\n");
    }

    printf("Result for solution1:\n");
    int* output = new int[k];
    GetLeastNumbers_Solution1(data, n, output, k);
    if(expectedResult != nullptr)
    {
        for(int i = 0; i < k; ++ i)
            printf("%d\t", output[i]);
        printf("\n");
    }

    delete[] output;

    printf("Result for solution2:\n");
    intSet leastNumbers;
    GetLeastNumbers_Solution2(vectorData, leastNumbers, k);
    for(setIterator iter = leastNumbers.begin(); iter != leastNumbers.end(); ++iter)
        printf("%d\t", *iter);
    printf("\n");
    
#if Method == 0
    printf("Result for solution3:\n");
    intPriorityQueue pq;
    GetLeastNumbers_Solution3(vectorData, pq, k);
    while (!pq.empty()) {
        printf("%d\t", pq.top());
        pq.pop();
    }
#endif
    
    
    printf("\n\n");
}

// k小于数组的长度
void Test1()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4};
    Test("Test1", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于数组的长度
void Test2()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Test("Test2", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k大于数组的长度
void Test3()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test3", data, sizeof(data) / sizeof(int), expected, 10);
}

// k等于1
void Test4()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int expected[] = {1};
    Test("Test4", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// k等于0
void Test5()
{
    int data[] = {4, 5, 1, 6, 2, 7, 3, 8};
    int* expected = nullptr;
    Test("Test5", data, sizeof(data) / sizeof(int), expected, 0);
}

// 数组中有相同的数字
void Test6()
{
    int data[] = {4, 5, 1, 6, 2, 7, 2, 8};
    int expected[] = {1, 2};
    Test("Test6", data, sizeof(data) / sizeof(int), expected, sizeof(expected) / sizeof(int));
}

// 输入空指针
void Test7()
{
    int* expected = nullptr;
    Test("Test7", nullptr, 0, expected, 0);
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

