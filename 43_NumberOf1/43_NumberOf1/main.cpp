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

// 面试题43：从1到n整数中1出现的次数
// 题目：输入一个整数n，求从1到n这n个整数的十进制表示中1出现的次数。例如
// 输入12，从1到12这些整数中包含1 的数字有1，10，11和12，1一共出现了5次。

#include <cstdio>
#include <cstring>
#include <cstdlib>



#define Method 0



#if Method == 0

/*
 方法一：
 最直接的方法遍历所有数字，然后算每个数字1的个数
 */
int NumbersOf1(int n) {
    int num = 0;
    while (n != 0) {
        
        if (n % 10 == 1)
            num++;
        
        n /= 10;
    }
    return num;
}

int NumberOf1Between1AndN_Solution1(unsigned int n) {
    int num = 0;
    for (int i = 1; i <= n; i++) {
        num += NumbersOf1(i);
    }
    return num;
}




/*
 方法二：直接计算
 。个位数
 。多位数
    首位 1 的个数：
    。首位 = 1。比如：“123”，那么1的个数是24个
    。首位 > 1。比如：“234", 那么1的个数是100 - 199 100个
    
    其它位 1 的个数：
    。比如”234“，分为035~134，135~234，就是2 * 2 * 10

    递归：去掉最高位，计算”34“
 
 */
int Pow10(int n) {
    int num = 1;
    for (int i = 0; i < n; i++)
        num *= 10;
    return num;
}
int NumbersOf1(char* str) {
    if (str == nullptr || *str < '0' || *str > '9' || *str == '\0')
        return 0;
    
    int first = str[0] - '0';
    int length = strlen(str);
    
    if (length == 1 && first == 0)
        return 0;
    if (length == 1 && first > 0)
        return 1;
    
    int numFirst = 0;
    if (first == 1)
        numFirst = atoi(str + 1) + 1;
    else if (first > 1)
        numFirst = Pow10(length - 1);
    
    int numOthers = first * (length - 1) * Pow10(length - 2);
    
    int numRecursive = NumbersOf1(str + 1);
    
    return numFirst + numOthers + numRecursive;
}

int NumberOf1Between1AndN_Solution2(unsigned int n) {
    if (n <= 0)
        return 0;
    
    char str[50];
    sprintf(str, "%d", n);
    
    return NumbersOf1(str);
}

#elif Method == 100
// ====================方法一====================
int NumberOf1(unsigned int n);

int NumberOf1Between1AndN_Solution1(unsigned int n)
{
    int number = 0;

    for(unsigned int i = 1; i <= n; ++ i)
        number += NumberOf1(i);

    return number;
}

int NumberOf1(unsigned int n)
{
    int number = 0;
    while(n)
    {
        if(n % 10 == 1)
            number ++;

        n = n / 10;
    }

    return number;
}

// ====================方法二====================
int NumberOf1(const char* strN);
int PowerBase10(unsigned int n);

int NumberOf1Between1AndN_Solution2(int n)
{
    if(n <= 0)
        return 0;

    char strN[50];
    sprintf(strN, "%d", n);

    return NumberOf1(strN);
}

int NumberOf1(const char* strN)
{
    if(!strN || *strN < '0' || *strN > '9' || *strN == '\0')
        return 0;

    int first = *strN - '0';
    unsigned int length = static_cast<unsigned int>(strlen(strN));

    if(length == 1 && first == 0)
        return 0;

    if(length == 1 && first > 0)
        return 1;

    // 假设strN是"21345"
    // numFirstDigit是数字10000-19999的第一个位中1的数目
    int numFirstDigit = 0;
    if(first > 1)
        numFirstDigit = PowerBase10(length - 1);
    else if(first == 1)
        numFirstDigit = atoi(strN + 1) + 1;

    // numOtherDigits是01346-21345除了第一位之外的数位中1的数目
    int numOtherDigits = first * (length - 1) * PowerBase10(length - 2);
    // numRecursive是1-1345中1的数目
    int numRecursive = NumberOf1(strN + 1);

    return numFirstDigit + numOtherDigits + numRecursive;
}

int PowerBase10(unsigned int n)
{
    int result = 1;
    for(unsigned int i = 0; i < n; ++ i)
        result *= 10;

    return result;
}

#endif

// ====================测试代码====================
void Test(const char* testName, int n, int expected)
{
    if(testName != nullptr)
        printf("%s begins: \n", testName);
    
    if(NumberOf1Between1AndN_Solution1(n) == expected)
        printf("Solution1 passed.\n");
    else
        printf("Solution1 failed.\n");
    
    if(NumberOf1Between1AndN_Solution2(n) == expected)
        printf("Solution2 passed.\n");
    else
        printf("Solution2 failed.\n");

    printf("\n");
}

void Test()
{
    Test("Test1", 1, 1);
    Test("Test2", 5, 1);
    Test("Test3", 10, 2);
    Test("Test4", 55, 16);
    Test("Test5", 99, 20);
    Test("Test6", 10000, 4001);
    Test("Test7", 21345, 18821);
    Test("Test8", 0, 0);
}

int main(int argc, char* argv[])
{
    Test();

    return 0;
}

