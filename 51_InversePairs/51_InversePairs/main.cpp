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

// 面试题51：数组中的逆序对
// 题目：在数组中的两个数字如果前面一个数字大于后面的数字，则这两个数字组
// 成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

#include <cstdio>






#define Method 0




#if Method == 0

int InversePairsCore(int* data, int* aux, int start, int end);
int Merge(int* data, int* aux, int start, int mid, int end);

int InversePairs(int* data, int length) {
    if (data == nullptr || length <= 0)
        return 0;
    int* aux = new int[length];
    for (int i = 0; i < length; i++)
        aux[i] = data[i];
    
    int count = InversePairsCore(data, aux, 0, length - 1);
    printf("count: %d\n", count);
    delete[] aux;
    return count;
}

int InversePairsCore(int* data, int* aux, int start, int end) {
    if (start >= end)
        return 0;
    
    int mid = start + (end - start) / 2;
    int left = InversePairsCore(aux, data, start, mid);
    int right = InversePairsCore(aux, data, mid + 1, end);
    int middle = Merge(data, aux, start, mid, end);
    
    return left + middle + right;
}

int Merge(int* data, int* aux, int start, int mid, int end) {
    int count = 0;
    
    int i = mid;
    int j = end;
    for (int k = end; k >= start; k--) {
        if      (i < start)         data[k] = aux[j--];
        else if (j < mid + 1)       data[k] = aux[i--];
        else if (aux[i] > aux[j])   {data[k] = aux[i--]; count += j - mid;} // 这里写错了，应该是count += xxx.
        else                        data[k] = aux[j--];
    }
    return count;
}



#elif Method == 100
int InversePairsCore(int* data, int* copy, int start, int end);

int InversePairs(int* data, int length)
{
    if(data == nullptr || length < 0)
        return 0;

    int* copy = new int[length];
    for(int i = 0; i < length; ++i)
        copy[i] = data[i];

    int count = InversePairsCore(data, copy, 0, length - 1);
    
    printf("\nData:");
    for (int i = 0; i < length; i++) {
        printf("%d\t", data[i]);
    }
    printf("\n");
    
    printf("Copy:");
    for (int i = 0; i < length; i++) {
        printf("%d\t", copy[i]);
    }
    printf("\n");
    
    delete[] copy;

    return count;
}

int InversePairsCore(int* data, int* copy, int start, int end)
{
    if(start == end)
    {
        copy[start] = data[start];
        return 0;
    }

    int length = (end - start) / 2;

    int left = InversePairsCore(copy, data, start, start + length);
    int right = InversePairsCore(copy, data, start + length + 1, end);

    // i初始化为前半段最后一个数字的下标
    int i = start + length;
    // j初始化为后半段最后一个数字的下标
    int j = end;
    int indexCopy = end;
    int count = 0;
    while(i >= start && j >= start + length + 1)
    {
        if(copy[i] > copy[j])
        {
            data[indexCopy--] = copy[i--];
            count += j - start - length;
        }
        else
        {
            data[indexCopy--] = copy[j--];
        }
    }

    for(; i >= start; --i)
        data[indexCopy--] = copy[i];

    for(; j >= start + length + 1; --j)8
        data[indexCopy--] = copy[j];

    return left + right + count;
}


//int InversePairsCore(int* data, int* copy, int start, int end)
//{
//    if(start == end)
//    {
//        copy[start] = data[start];
//        return 0;
//    }
//
//    int length = (end - start) / 2;
//
//    int left = InversePairsCore(copy, data, start, start + length);
//    int right = InversePairsCore(copy, data, start + length + 1, end);
//
//    // i初始化为前半段最后一个数字的下标
//    int i = start + length;
//    // j初始化为后半段最后一个数字的下标
//    int j = end;
//    int indexCopy = end;
//    int count = 0;
//    while(i >= start && j >= start + length + 1)
//    {
//        if(data[i] > data[j])
//        {
//            copy[indexCopy--] = data[i--];
//            count += j - start - length;
//        }
//        else
//        {
//            copy[indexCopy--] = data[j--];
//        }
//    }
//
//    for(; i >= start; --i)
//        copy[indexCopy--] = data[i];
//
//    for(; j >= start + length + 1; --j)
//        copy[indexCopy--] = data[j];
//
//    return left + right + count;
//}

#endif

// ====================测试代码====================
void Test(char* testName, int* data, int length, int expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(InversePairs(data, length) == expected)
        printf("Passed.\n");
    else
        printf("Failed.\n");
}

void Test1()
{
    int data[] = { 1, 2, 3, 4, 7, 6, 5 };
    int expected = 3;

    Test("Test1", data, sizeof(data) / sizeof(int), expected);
}

// 递减排序数组
void Test2()
{
    int data[] = { 6, 5, 4, 3, 2, 1 };
    int expected = 15;

    Test("Test2", data, sizeof(data) / sizeof(int), expected);
}

// 递增排序数组
void Test3()
{
    int data[] = { 1, 2, 3, 4, 5, 6 };
    int expected = 0;

    Test("Test3", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有一个数字
void Test4()
{
    int data[] = { 1 };
    int expected = 0;

    Test("Test4", data, sizeof(data) / sizeof(int), expected);
}


// 数组中只有两个数字，递增排序
void Test5()
{
    int data[] = { 1, 2 };
    int expected = 0;

    Test("Test5", data, sizeof(data) / sizeof(int), expected);
}

// 数组中只有两个数字，递减排序
void Test6()
{
    int data[] = { 2, 1 };
    int expected = 1;

    Test("Test6", data, sizeof(data) / sizeof(int), expected);
}

// 数组中有相等的数字
void Test7()
{
    int data[] = { 1, 2, 1, 2, 1 };
    int expected = 3;

    Test("Test7", data, sizeof(data) / sizeof(int), expected);
}

void Test8()
{
    int expected = 0;

    Test("Test8", nullptr, 0, expected);
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
    Test8();

    return 0;
}

