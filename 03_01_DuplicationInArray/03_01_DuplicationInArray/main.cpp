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

// 面试题3（一）：找出数组中重复的数字
// 题目：在一个长度为n的数组里的所有数字都在0到n-1的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，
// 也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。例如，如果输入长度为7的数组{2, 3, 1, 0, 2, 5, 3}，
// 那么对应的输出是重复的数字2或者3。

#include <cstdio>


#define Method 2


#if Method == 0
// 用来测试
bool duplicate(int numbers[], int length, int* duplication) {
    return true;
}

#elif Method == 1

// 方法：使用哈希表
// 需要额外空间，不改变原数组，时间复杂度O(n), 空间复杂度O(N)
#include <set>
bool duplicate(int numbers[], int length, int* duplication) {
    std::set<int> myset;
    for (int i = 0; i < length; i++) {
        auto ret = myset.insert(numbers[i]);
        if (!ret.second) {
            *duplication = numbers[i];
            return true;
        }
    }
    return false;
}


#elif Method == 2
// 方法：排序
// 不需要额外空间，会改变原数组，时间复杂度O(nlogn), 空间复杂度O(1)

// 注意：这里没有使用std::sort是因为在数组作为函数参数传递的时候，会退化为指针
// 导致std::begin()无法知道数组的长度（无法通过sizeof(numbers) / sizeof(numbers[0])
#include <algorithm>    // std::swap()

// 注意：[左闭, 右闭]
int partition(int numbers[], int begin, int end) {
    int index;
    int small = begin - 1;
    for (index = begin; index < end; index++) {
        if (numbers[index] < numbers[end]) {
            small++;
            if (small != index)
                std::swap(numbers[small], numbers[index]);
        }
    }
    small++;
    std::swap(numbers[small], numbers[index]);
    
    return small;
}


void quickSort(int numbers[], int begin, int end) {
    if (numbers == nullptr || begin < 0 || end < 0 || begin >= end) return;
    
    int index = partition(numbers, begin, end);
    quickSort(numbers, begin, index - 1);
    quickSort(numbers, index + 1, end);
}


bool duplicate(int numbers[], int length, int* duplication) {
    quickSort(numbers, 0, length - 1);
    for (int i = 1; i < length; i++) {
        if (numbers[i] == numbers[i-1]) {
            *duplication = numbers[i];
            return true;
        }
    }
    
    return false;
}




#elif Method == 3

// 参数:
//        numbers:     一个整数数组
//        length:      数组的长度
//        duplication: (输出) 数组中的一个重复的数字
// 返回值:
//        true  - 输入有效，并且数组中存在重复的数字
//        false - 输入无效，或者数组中没有重复的数字
bool duplicate(int numbers[], int length, int* duplication)
{
    if(numbers == nullptr || length <= 0)
        return false;

    for(int i = 0; i < length; ++i)
    {
        if(numbers[i] < 0 || numbers[i] > length - 1)
            return false;
    }

    for(int i = 0; i < length; ++i)
    {
        while(numbers[i] != i)
        {
            if(numbers[i] == numbers[numbers[i]])
            {
                *duplication = numbers[i];
                return true;
            }

            // 交换numbers[i]和numbers[numbers[i]]
            int temp = numbers[i];
            numbers[i] = numbers[temp];
            numbers[temp] = temp;
        }
    }

    return false;
}

#endif


// ====================测试代码====================
bool contains(int array[], int length, int number)
{
    for(int i = 0; i < length; ++i)
    {
        if(array[i] == number)
            return true;
    }

    return false;
}

void test(char* testName, int numbers[], int lengthNumbers, int expected[], int expectedExpected, bool validArgument)
{
    printf("%s begins: ", testName);

    int duplication;
    bool validInput = duplicate(numbers, lengthNumbers, &duplication);

    if(validArgument == validInput)
    {
        if(validArgument)
        {
            if(contains(expected, expectedExpected, duplication))
                printf("Passed.\n");
            else
                printf("FAILED.\n");
        }
        else
            printf("Passed.\n");
    }
    else
        printf("FAILED.\n");
}

// 重复的数字是数组中最小的数字
void test1()
{
    int numbers[] = { 2, 1, 3, 1, 4 };
    int duplications[] = { 1 };
    test("Test1", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 重复的数字是数组中最大的数字
void test2()
{
    int numbers[] = { 2, 4, 3, 1, 4 };
    int duplications[] = { 4 };
    test("Test2", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 数组中存在多个重复的数字
void test3()
{
    int numbers[] = { 2, 4, 2, 1, 4 };
    int duplications[] = { 2, 4 };
    test("Test3", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), true);
}

// 没有重复的数字
void test4()
{
    int numbers[] = { 2, 1, 3, 0, 4 };
    int duplications[] = { -1 }; // not in use in the test function
    test("Test4", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// 没有重复的数字
void test5()
{
    int numbers[] = { 2, 1, 3, 5, 4 };
    int duplications[] = { -1 }; // not in use in the test function
    test("Test5", numbers, sizeof(numbers) / sizeof(int), duplications, sizeof(duplications) / sizeof(int), false);
}

// 无效的输入
void test6()
{
    int* numbers = nullptr;
    int duplications[] = { -1 }; // not in use in the test function
    test("Test6", numbers, 0, duplications, sizeof(duplications) / sizeof(int), false);
}

int main(void)
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}
