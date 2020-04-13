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

// 面试题39：数组中出现次数超过一半的数字
// 题目：数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例
// 如输入一个长度为9的数组{1, 2, 3, 2, 2, 2, 5, 4, 2}。由于数字2在数组中
// 出现了5次，超过数组长度的一半，因此输出2。

#include <cstdio>
#include <stdlib.h>


#define Method 0


#if Method == 0

void Swap2(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int Partition2(int data[], int length, int start, int end) {
    if (data == nullptr || length <= 0 || start < 0 || end >= length  || end < start)
        throw ("Invalid input");
    
    int random = rand() % (end - start + 1) + start;
    Swap2(&data[random], &data[end]);
    
    int small = start - 1;
    for (int i = start; i < end; i++) {
        if (data[i] < data[end]) {
            small++;
            if (i != small)
                Swap2(&data[small], &data[i]);
        }
    }
    
    small++;
    Swap2(&data[small], &data[end]);
    
    return small;
}

bool g_bInputInvalid = false;

bool checkInvalidInput(int* numbers, int length) {
    g_bInputInvalid = false;
    if (numbers == nullptr || length <= 0)
        g_bInputInvalid = true;
    return g_bInputInvalid;
}

bool checkMoreThanHalf(int* numbers, int length, int target) {
    if (numbers == nullptr || length <= 0)
        return false;
    
    bool moreThanHalf = true;
    int times = 0;
    for (int i = 0; i < length; i++) {
        if (numbers[i] == target)
            times++;
    }
    
    if (times * 2 <= length) {
        g_bInputInvalid = true;
        moreThanHalf = false;
    }
    
    return moreThanHalf;
        
}

int MoreThanHalfNum_Solution1(int* numbers, int length) {

    if (checkInvalidInput(numbers, length))
        return 0;
    
    int start = 0;
    int end = length - 1;
    int middle = length >> 1;
    
    int index = Partition2(numbers, length, start, end);
    while (index != middle) {
        if (index > middle)
            end = index - 1;
        else if (index < middle)
            start = index + 1;
        
        index = Partition2(numbers, length, start, end);
    }
    
    if (!checkMoreThanHalf(numbers, length, numbers[middle]))
        return 0;
        
    return numbers[middle];
}

int MoreThanHalfNum_Solution2(int* numbers, int length) {

    if (checkInvalidInput(numbers, length))
        return 0;
    
    int result = 0;
    int times = 0;
    
    for (int i = 0; i < length; i++) {
        if (times == 0) {
            result = numbers[i];
            times = 1;
        }
        else if (numbers[i] == result)
            times++;
        else
            times--;
    }
    
    if (!checkMoreThanHalf(numbers, length, result))
        return 0;
    
    return result;
}

    
#elif Method == 100

#include "Array.h"

bool g_bInputInvalid = false;

bool CheckInvalidArray(int* numbers, int length)
{
    g_bInputInvalid = false;
    // 源代码可能有点儿问题，这里应该是 || 的关系
    if(numbers == nullptr && length <= 0)
        g_bInputInvalid = true;

    return g_bInputInvalid;
}

bool CheckMoreThanHalf(int* numbers, int length, int number)
{
    int times = 0;
    for(int i = 0; i < length; ++i)
    {
        if(numbers[i] == number)
            times++;
    }
 
    bool isMoreThanHalf = true;
    if(times * 2 <= length)
    {
        g_bInputInvalid = true;
        isMoreThanHalf = false;
    }

    return isMoreThanHalf;
}

// ====================方法1====================
/*
 使用快速排序的partition函数，这个函数会随机选出来一个数，确保左边的数比它小，右边的数比它大。
 因为题目中重复的数字超过了一半，排在中间的元素肯定就是那个重复的元素。
 
 例子1：4 个数，重复的数超过 2 个。4 / 2 = 2那么下标为 2 的时候就是那个重复的数
 1 2 2 2
 1 1 1 2
 
 例子2：5 个数，5 / 2 = 2，那么下标为 2 的数就是那个重复的数
 1 1 1 2 2
 
 需要改变原数组，时间复杂度 O(n)
 */
int MoreThanHalfNum_Solution1(int* numbers, int length)
{
    if(CheckInvalidArray(numbers, length))
        return 0;
 
    int middle = length >> 1;
    int start = 0;
    int end = length - 1;
    int index = Partition(numbers, length, start, end);
    while(index != middle)
    {
        if(index > middle)
        {
            end = index - 1;
            index = Partition(numbers, length, start, end);
        }
        else
        {
            start = index + 1;
            index = Partition(numbers, length, start, end);
        }
    }
 
    int result = numbers[middle];
    if(!CheckMoreThanHalf(numbers, length, result))
        result = 0;

    return result;
}

// ====================方法2====================
/*
 因为重复的元素超过一半，那么重复的元素个数减去不重复的个数肯定大于0
 
 不需要改变原数组，时间复杂度是O(n)
 */
int MoreThanHalfNum_Solution2(int* numbers, int length)
{
    if(CheckInvalidArray(numbers, length))
        return 0;
 
    int result = numbers[0];
    int times = 1;
    for(int i = 1; i < length; ++i)
    {
        if(times == 0)
        {
            result = numbers[i];
            times = 1;
        }
        else if(numbers[i] == result)
            times++;
        else
            times--;
    }
 
    if(!CheckMoreThanHalf(numbers, length, result))
        result = 0;
 
    return result;
}

#endif

// ====================测试代码====================
void Test(char* testName, int* numbers, int length, int expectedValue, bool expectedFlag)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);

    int* copy = new int[length];
    for(int i = 0; i < length; ++i)
        copy[i] = numbers[i];

    printf("Test for solution1: ");
    int result = MoreThanHalfNum_Solution1(numbers, length);
    if(result == expectedValue && g_bInputInvalid == expectedFlag)
        printf("Passed.\n");
    else
        printf("Failed.\n");

    printf("Test for solution2: ");
    result = MoreThanHalfNum_Solution2(copy, length);
    if(result == expectedValue && g_bInputInvalid == expectedFlag)
        printf("Passed.\n");
    else
        printf("Failed.\n");

    delete[] copy;
}

// 存在出现次数超过数组长度一半的数字
void Test1()
{
    int numbers[] = {1, 2, 3, 2, 2, 2, 5, 4, 2};
    Test("Test1", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 不存在出现次数超过数组长度一半的数字
void Test2()
{
    int numbers[] = {1, 2, 3, 2, 4, 2, 5, 2, 3};
    Test("Test2", numbers, sizeof(numbers) / sizeof(int), 0, true);
}

// 出现次数超过数组长度一半的数字都出现在数组的前半部分
void Test3()
{
    int numbers[] = {2, 2, 2, 2, 2, 1, 3, 4, 5};
    Test("Test3", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 出现次数超过数组长度一半的数字都出现在数组的后半部分
void Test4()
{
    int numbers[] = {1, 3, 4, 5, 2, 2, 2, 2, 2};
    Test("Test4", numbers, sizeof(numbers) / sizeof(int), 2, false);
}

// 输入空指针
void Test5()
{
   int numbers[] = {1};
   Test("Test5", numbers, 1, 1, false);
}

// 输入空指针
void Test6()
{
    Test("Test6", nullptr, 0, 0, true);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();

    return 0;
}

