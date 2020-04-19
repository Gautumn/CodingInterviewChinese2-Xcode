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

// 面试题60：n个骰子的点数
// 题目：把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s
// 的所有可能的值出现的概率。

#include <cstdio>
#include <math.h>

int g_maxValue = 6;

#define Method 0



#if Method == 0


void PrintProbability(int number, int currNum, int sum, int* pTimes) {
    if (currNum == 1) {
        pTimes[sum - number]++;
        return;
    }
    
    for (int i = 1; i <= g_maxValue; i++)
        PrintProbability(number, currNum - 1, sum + i, pTimes);
}

void PrintProbability(int number, int* pTimes) {
    for (int i = 1; i <= g_maxValue; i++) {
        PrintProbability(number, number, i, pTimes);
    }
}


void PrintProbability_Solution1(int number) {
    if (number <= 0) return;
    
    int min = 1 * number;
    int max = g_maxValue * number;
    int* pTimes = new int[max - min + 1];
    for (int i = min; i <= max; i++)
        pTimes[i - min] = 0;
    
    PrintProbability(number, pTimes);
    
    int total = pow(g_maxValue, number);
    for (int i = min; i <= max; i++) {
        double ratio = (double)pTimes[i - min] / total;
        printf("%d: %e\n", i, ratio);
    }
    delete[] pTimes;
}


void PrintProbability_Solution2(int number) {
    if (number <= 0) return;
    
    

    int min = 1 * number;
    int max = g_maxValue * number;
    
    // 存储所有可能出现的值的次数，所以出现的最小的是 1
    // 第一次取值：1 ~ 6
    // 第二次取值：2 ~ 12
    int* pTimes[2];
    pTimes[0] = new int[max + 1];
    pTimes[1] = new int[max + 1];
    for (int i = 0; i < max + 1; i++) {
        pTimes[0][i] = 0;
        pTimes[1][i] = 0;
    }
    
    
    // 第一次
    int flag = 0;
    for (int i = 1; i <= g_maxValue; i++)
        pTimes[flag][i] = 1;
    
    // 第二次 -> 第 number 次
    for (int k = 2; k <= number; k++) {
        for (int i = 0; i < k; i++)
            pTimes[1 - flag][i] = 0;
        
        for (int i = k; i <= g_maxValue * k; i++) {
            pTimes[1 - flag][i] = 0;
            for (int j = 1; j <= i && j <= g_maxValue; j++)
                pTimes[1 - flag][i] += pTimes[flag][i - j];
        }
        flag = 1 - flag;
    }
    
    
    int total = pow(g_maxValue, number);
    for (int i = min; i <= max; i++) {
        double ratio = (double)pTimes[flag][i] / total;
        printf("%d: %e\n", i, ratio);
    }
    
    delete[] pTimes[0];
    delete[] pTimes[1];
    
    
    
}



#elif Method == 100
// ====================方法一====================
/*
 全排列
 */
void Probability(int number, int* pProbabilities);
void Probability(int original, int current, int sum, int* pProbabilities);

void PrintProbability_Solution1(int number)
{
    if(number < 1)
        return;
 
    int maxSum = number * g_maxValue;
    int* pProbabilities = new int[maxSum - number + 1];
    for(int i = number; i <= maxSum; ++i)
        pProbabilities[i - number] = 0;
 
    Probability(number, pProbabilities);
 
    int total = pow((double)g_maxValue, number);
    for(int i = number; i <= maxSum; ++i)
    {
        double ratio = (double)pProbabilities[i - number] / total;
        printf("%d: %e\n", i, ratio);
    }
 
    delete[] pProbabilities;
}
 
void Probability(int number, int* pProbabilities)
{
    for(int i = 1; i <= g_maxValue; ++i)
        Probability(number, number, i, pProbabilities);
}
 
void Probability(int original, int current, int sum,
                 int* pProbabilities)
{
    if(current == 1)
    {
        pProbabilities[sum - original]++;
    }
    else
    {
        for(int i = 1; i <= g_maxValue; ++i)
        {
            Probability(original, current - 1, i + sum, pProbabilities);
        }
    }
}

// ====================方法二====================
void PrintProbability_Solution2(int number)
{
    if(number < 1)
        return;

    int* pProbabilities[2];
    pProbabilities[0] = new int[g_maxValue * number + 1];
    pProbabilities[1] = new int[g_maxValue * number + 1];
    for(int i = 0; i < g_maxValue * number + 1; ++i)
    {
        pProbabilities[0][i] = 0;
        pProbabilities[1][i] = 0;
    }
 
    int flag = 0;
    for (int i = 1; i <= g_maxValue; ++i)
        pProbabilities[flag][i] = 1;
    
    for (int k = 2; k <= number; ++k)
    {
        for(int i = 0; i < k; ++i)
            pProbabilities[1 - flag][i] = 0;

        for (int i = k; i <= g_maxValue * k; ++i)
        {
            pProbabilities[1 - flag][i] = 0;
            for(int j = 1; j <= i && j <= g_maxValue; ++j)
                pProbabilities[1 - flag][i] += pProbabilities[flag][i - j];
        }
 
        flag = 1 - flag;
    }
 
    double total = pow((double)g_maxValue, number);
    for(int i = number; i <= g_maxValue * number; ++i)
    {
        double ratio = (double)pProbabilities[flag][i] / total;
        printf("%d: %e\n", i, ratio);
    }
 
    delete[] pProbabilities[0];
    delete[] pProbabilities[1];
}

#endif

// ====================测试代码====================
void Test(int n)
{
    printf("Test for %d begins:\n", n);
    
    printf("Test for solution1\n");
    PrintProbability_Solution1(n);

    printf("Test for solution2\n");
    PrintProbability_Solution2(n);

    printf("\n");
}

int main(int argc, char* argv[])
{
    Test(1);
    Test(2);
    Test(3);
    Test(4);
    
    Test(11);

    Test(0);

    return 0;
}

