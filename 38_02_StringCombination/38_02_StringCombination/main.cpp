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

// 面试题38：字符串的组合
// 题目：输入三个字符a、b、c，则它们的组合有a、b、c、ab、ac、bc、abc。
// 当交换字符串的两个字符时，虽然能够得到两个不同的排列，却是同一个组合。比如ab和aba是不同的排列，但只算一种组合。

#include <cstdio>
#include <cstring>
#include <vector>
#define Method 100



#if Method == 0






#elif Method == 100

/*
 思路：输入字符是：a、b、c，那么我们分别求只有1个的组合，2个的组合和3个的组合
 1. 2个的组合
    1）首先拿出来a，然后在从生下的里面拿出来1个，我们拿出b。此时不需要再拿了，打印：a b
    2) 弹出b，再拿出来一个c。此时不需要再拿了，打印：a c
    3）弹出c，再去拿，发现已经没有了
    4）弹出a，还需要再拿2个，拿出来b，放入
    5）还需要在拿一个，我们拿到c，放入。此时不需要再拿了，打印：b c
    6）弹出c，再拿一个发现没有了
    7）弹出b，还需要拿2个，拿出来c，放入
    8）再去拿发现已经没有了，结束。
 
    Combination(a, 2)
        push(a)
        Combination(b, 1)
            push(b)
            Combination(c, 0)           => 打印 a b
            pop(b)
            Combination(c, 1)
                push(c)
                Combination('\0', 0)    => 打印 a c
                pop(c)
                Combination('\0', 1)    => 没有了，直接返回
        pop(a)
        Combination(b, 2)
            push(b)
            Combination(c, 1)
                push(c)
                Combination('\0', 0)    => 打印 b c
                pop(c)
                Combination('\0', 1)    => 没有了，直接返回
            pop(b)
            Combination(c, 2)
                push(c)
                Combination('\0', 1)    => 没有了，直接返回
                pop(c)
                Combination('\0', 2)    => 没有了，直接返回
    
 */
void Combination(char* pStr, int number, std::vector<char>& combination);

void Combination(char* pStr) {
    if (pStr == nullptr) return;
    
    int length = strlen(pStr);
    std::vector<char> combination;
    
    for (int i = 1; i <= length; i++) {
        Combination(pStr, i, combination);
    }
}

void Combination(char* pStr, int number, std::vector<char>& combination) {
    if (number == 0) {
        for (auto& c : combination) {
            printf("%c\t", c);
        }
        printf("\n");
        return;
    }
    
    if (*pStr == '\0') return;
    
    combination.push_back(*pStr);
    Combination(pStr + 1, number - 1, combination);
    
    // 不要了，再从剩下的里面重新拿。
    combination.pop_back();
    Combination(pStr + 1, number, combination);
}

#endif

// ====================测试代码====================
void Test(char* pStr)
{
    if(pStr == nullptr)
        printf("Test for nullptr begins:\n");
    else
        printf("Test for %s begins:\n", pStr);

    Combination(pStr);

    printf("\n");
}

int main(int argc, char* argv[])
{
    Test(nullptr);

    char string1[] = "";
    Test(string1);

    char string2[] = "a";
    Test(string2);

    char string3[] = "ab";
    Test(string3);

    char string4[] = "abc";
    Test(string4);

    return 0;
}

