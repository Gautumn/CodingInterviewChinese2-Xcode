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

// 面试题50（二）：字符流中第一个只出现一次的字符
// 题目：请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从
// 字符流中只读出前两个字符"go"时，第一个只出现一次的字符是'g'。当从该字
// 符流中读出前六个字符"google"时，第一个只出现一次的字符是'l'。

#include <cstdio>
#include <vector>
#include <limits>

using namespace std;



#define Method 0


#if Method == 0


class CharStatistics {
public:
    CharStatistics() : index(0) {
        for (int i = 0; i < TableSize; i++)
            indexTable[i] = -1;
    }
    
    void Insert(char ch) {
        if (indexTable[ch] == -1)
            indexTable[ch] = index;
        else if (indexTable[ch] >= 0)
            indexTable[ch] = -2;
        
        index++;
    }
    
    char FirstAppearingOnce(void) {
        if (index == 0)
            return '\0';
        
        char ch = '\0';
        int minIndex = INT_MAX;
        for (int i = 0; i < TableSize; i++) {
            if (indexTable[i] >= 0 && indexTable[i] < minIndex) {
                ch = i;
                minIndex = indexTable[i];
            }
        }
        
        return ch;
    }
private:
    static const int TableSize = 256;
    
    int indexTable[TableSize];
    int index;
};






#elif Method == 100
/*
 思路：用一个数组标记字符出现的下标，数组取值
 >= 0 : 出现一次，值为下标
 == -1：没出现过
 == -2：出现了多次
 */
class CharStatistics
{
public:
    CharStatistics() : index(0)
    {
        for(int i = 0; i < 256; ++i)
            occurrence[i] = -1;
    }

    void Insert(char ch)
    {
        if(occurrence[ch] == -1)
            occurrence[ch] = index;
        else if(occurrence[ch] >= 0)
            occurrence[ch] = -2;

        index++;
    }

    char FirstAppearingOnce()
    {
        char ch = '\0';
        int minIndex = numeric_limits<int>::max();
        for(int i = 0; i < 256; ++i)
        {
            if(occurrence[i] >= 0 && occurrence[i] < minIndex)
            {
                ch = (char) i;
                minIndex = occurrence[i];
            }
        }

        return ch;
    }

private:
    // occurrence[i]: A character with ASCII value i;
    // occurrence[i] = -1: The character has not found;
    // occurrence[i] = -2: The character has been found for mutlple times
    // occurrence[i] >= 0: The character has been found only once
    int occurrence[256];
    int index;
};

#endif

// ====================测试代码====================
void Test(const char* testName, CharStatistics chars, char expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(chars.FirstAppearingOnce() == expected)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    CharStatistics chars;

    Test("Test1", chars, '\0');

    chars.Insert('g');
    Test("Test2", chars, 'g');

    chars.Insert('o');
    Test("Test3", chars, 'g');

    chars.Insert('o');
    Test("Test4", chars, 'g');

    chars.Insert('g');
    Test("Test5", chars, '\0');

    chars.Insert('l');
    Test("Test6", chars, 'l');

    chars.Insert('e');
    Test("Test7", chars, 'l');

    return 0;
}

