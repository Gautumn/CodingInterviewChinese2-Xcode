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

// 面试题46：把数字翻译成字符串
// 题目：给定一个数字，我们按照如下规则把它翻译为字符串：0翻译成"a"，1翻
// 译成"b"，……，11翻译成"l"，……，25翻译成"z"。一个数字可能有多个翻译。例
// 如12258有5种不同的翻译，它们分别是"bccfi"、"bwfi"、"bczi"、"mcfi"和
// "mzi"。请编程实现一个函数用来计算一个数字有多少种不同的翻译方法。

#include <string>
#include <iostream>

using namespace std;


#define Method 0





#if Method == 0


//int GetTranslationCount(string& str) {
//    int length = str.length();
//
//    int count = 0;
//    int* counts = new int[length];
//    for (int i = length - 1; i >= 0; i--) {
//        count = 0;
//
//        // 一个数字
//        if (i == length - 1)
//            count = 1;
//        else
//            count = counts[i + 1];
//
//        // 两个数字
//        if (i < length - 1) {
//            int n1 = str[i] - '0';
//            int n2 = str[i + 1] - '0';
//            int n = n1 * 10 + n2;
//            if (n >= 10 && n <= 25) {
//                if (i < length - 2)
//                    count += counts[i + 2];
//                else
//                    count += 1;
//            }
//        }
//
//        counts[i] = count;
//
//    }
//
//    int ret = counts[0];
//    delete[] counts;
//
//    return ret;
//}


// 递归方法，其实就是求满足要求的叶子节点的数目
//void GetTranslationCount(const char* str, int& count) {
//    if (str == nullptr)
//        return;
//
//    if (*str == '\0') {
//        count++;
//        return;
//    }
//
//    GetTranslationCount(str + 1, count);
//
//    if (strlen(str) >= 2) {
//        int n1 = str[0] - '0';
//        int n2 = str[1] - '0';
//        int n = n1 * 10 + n2;
//        if (n >= 10 && n <= 25)
//            GetTranslationCount(str + 2, count);
//    }
//}


// 和斐波那契数列很像
/*
 long long Fibonacci(unsigned int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
 
    return Fibonacci(n-1) + Fibonacci(n-2);
 }
 */
int GetTranslationCount(const char* str) {
    if (str == nullptr)
        return 0;

    if (*str == '\0') {
        return 1;
    }

    int r1 = 0, r2 = 0;
    r1 = GetTranslationCount(str + 1);

    if (strlen(str) >= 2) {
        int n1 = str[0] - '0';
        int n2 = str[1] - '0';
        int n = n1 * 10 + n2;
        if (n >= 10 && n <= 25)
            r2 = GetTranslationCount(str + 2);
    }
    return r1 + r2;
}

int GetTranslationCount(int number) {
    if (number < 0)
        return 0;
    
    int count = 0;
    string numString = to_string(number);
    count = GetTranslationCount(numString.c_str());
    printf("%d\n", count);
    return count;
}






#elif Method == 100
int GetTranslationCount(const string& number);

int GetTranslationCount(int number)
{
    if(number < 0)
        return 0;

    string numberInString = to_string(number);
    return GetTranslationCount(numberInString);
}

int GetTranslationCount(const string& number)
{
    int length = number.length();
    int* counts = new int[length];
    int count = 0;

    for(int i = length - 1; i >= 0; --i)
    {
        count = 0;
         if(i < length - 1)
               count = counts[i + 1];
         else
               count = 1;

        if(i < length - 1)
        {
            int digit1 = number[i] - '0';
            int digit2 = number[i + 1] - '0';
            int converted = digit1 * 10 + digit2;
            if(converted >= 10 && converted <= 25)
            {
                if(i < length - 2)
                    count += counts[i + 2];
                else
                    count += 1;
            }
        }

        counts[i] = count;
    }

    count = counts[0];
    delete[] counts;

    return count;
}

#endif

// ====================测试代码====================
void Test(const string& testName, int number, int expected)
{
    if(GetTranslationCount(number) == expected)
        cout << testName << " passed." << endl;
    else
        cout << testName << " FAILED." << endl;
}

void Test1()
{
    int number = 0;
    int expected = 1;
    Test("Test1", number, expected);
}

void Test2()
{
    int number = 10;
    int expected = 2;
    Test("Test2", number, expected);
}

void Test3()
{
    int number = 125;
    int expected = 3;
    Test("Test3", number, expected);
}

void Test4()
{
    int number = 126;
    int expected = 2;
    Test("Test4", number, expected);
}

void Test5()
{
    int number = 426;
    int expected = 1;
    Test("Test5", number, expected);
}

void Test6()
{
    int number = 100;
    int expected = 2;
    Test("Test6", number, expected);
}

void Test7()
{
    int number = 101;
    int expected = 2;
    Test("Test7", number, expected);
}

void Test8()
{
    int number = 12258;
    int expected = 5;
    Test("Test8", number, expected);
}

void Test9()
{
    int number = -100;
    int expected = 0;
    Test("Test9", number, expected);
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
    Test9();

    return 0;
}
