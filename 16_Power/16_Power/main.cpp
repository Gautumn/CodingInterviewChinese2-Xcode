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

// 面试题16：数值的整数次方
// 题目：实现函数double Power(double base, int exponent)，求base的exponent
// 次方。不得使用库函数，同时不需要考虑大数问题。

#include <iostream>
#include <cmath>


#define Method 3

#if Method == 0

bool g_InvalidInput = false;

bool equal(double num1, double num2);
double PowerCore(double base, unsigned int exponent);


double Power(double base, int exponent) {
    g_InvalidInput = false;
    
    if (equal(base, 0.0) && exponent < 0) {
        g_InvalidInput = true;
        return 0.0;
    }
    
    unsigned int absExponent = exponent < 0 ? (unsigned int)-exponent : (unsigned int)exponent;
    
    double result = PowerCore(base, absExponent);
    if (exponent < 0)
        result = 1.0 / result;
    
    return result;
}

// 循环方式
//double PowerCore(double base, unsigned int exponent) {
//    double result = 1.0;
//    for (int i = 1; i <= exponent; i++) {
//        result = base * result;
//    }
//    return result;
//}

// 递归方式，都是求平方，速度更快

double PowerCore(double base, unsigned int exponent) {
    if (exponent == 0) return 1.0;
    if (exponent == 1) return base;
    
    double result = PowerCore(base, exponent >> 1);
    result = result * result;
    if (exponent & 0x01)
        result = result * base;
    
    return result;
}

bool equal(double num1, double num2) {
    double ret = num1 - num2;
    if (ret > -0.000001 && ret < 0.000001)
        return true;
    return false;
}








#elif Method == 3

bool g_InvalidInput = false;
bool equal(double num1, double num2);
double PowerWithUnsignedExponent(double base, unsigned int exponent);

double Power(double base, int exponent)
{
    g_InvalidInput = false;

    if (equal(base, 0.0) && exponent < 0)
    {
        g_InvalidInput = true;
        return 0.0;
    }

    unsigned int absExponent = exponent < 0 ? (unsigned int)-exponent : (unsigned int)exponent;

    double result = PowerWithUnsignedExponent(base, absExponent);
    if (exponent < 0)
        result = 1.0 / result;

    return result;
}

/*
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    double result = 1.0;
    
    for (int i = 1; i <= exponent; ++i)
        result *= base;

    return result;
}
*/

/*
 求：2^4 = 16
    4 => 4*4 = 16
    |
    2 => 2*2 = 4
    |
    1 => 2

 求：2^5 = 32
    5 => 4*4*2 = 32
    |
    2 => 2*2 = 4
    |
    1 => 2

 从上面可以看出奇数只在第一次会出现，之后都是偶数。
 */
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
    if (exponent == 0) return 1.0;
    if (exponent == 1) return base;
    
    double result = PowerWithUnsignedExponent(base, exponent >> 1);
    result = result * result;
    if (exponent & 0x01)
        result = result * base;
    
    return result;
}

bool equal(double num1, double num2)
{
    double ret = num1 - num2;
    if (ret > -0.000001 && ret < 0.000001)
        return true;
    return false;
}

#endif

// ====================测试代码====================
void Test(const char* testName, double base, int exponent, double expectedResult, bool expectedFlag)
{
    double result = Power(base, exponent);
    if (equal(result, expectedResult) && g_InvalidInput == expectedFlag)
        std::cout << testName << " passed" << std::endl;
    else
        std::cout << testName << " FAILED" << std::endl;
}

int main(int argc, char* argv[])
{
    // 底数、指数都为正数
    Test("Test1", 2, 3, 8, false);

    // 底数为负数、指数为正数
    Test("Test2", -2, 3, -8, false);

    // 指数为负数
    Test("Test3", 2, -3, 0.125, false);

    // 指数为0
    Test("Test4", 2, 0, 1, false);

    // 底数、指数都为0
    Test("Test5", 0, 0, 1, false);

    // 底数为0、指数为正数
    Test("Test6", 0, 4, 0, false);

    // 底数为0、指数为负数
    Test("Test7", 0, -4, 0, true);

    return 0;
}

