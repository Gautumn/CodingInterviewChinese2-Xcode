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

// 面试题29：顺时针打印矩阵
// 题目：输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字。

#include <cstdio>




#define Method 0


#if Method == 0
void PrintNumber(int num);
void PrintMatrixCycle(int** numbers, int columns, int rows, int start);
void PrintMatrixClockwisely(int** numbers, int columns, int rows) {
    if (numbers == nullptr || *numbers == nullptr || columns <= 0 || rows <= 0)
        return;
    
    int start = 0;
    while (start * 2 < rows && start * 2 < columns) {
        PrintMatrixCycle(numbers, columns, rows, start);
        start++;
    }
}

void PrintMatrixCycle(int** numbers, int columns, int rows, int start) {
    int endX = columns - 1 - start;
    int endY = rows - 1 - start;
    
    // 从左到右
    for (int i = start; i <= endX; i++) {
        int num = numbers[start][i];
        PrintNumber(num);
    }
    
    // 从上到下
    if (endY > start) {
        for (int i = start + 1; i <= endY; i++) {
            int num = numbers[i][endX];
            PrintNumber(num);
        }
    }
    
    // 从右到左
    if (endY > start && endX > start) {
        for (int i = endX - 1; i >= start; i--) {
            int num = numbers[endY][i];
            PrintNumber(num);
        }
    }
    
    // 从下到上
    if (endX > start && start < endY - 1) {
        for (int i = endY - 1; i >= start + 1; i--) {
            int num = numbers[i][start];
            PrintNumber(num);
        }
    }
    
    printf("\n");
}

void PrintNumber(int num) {
    printf("%d\t", num);
}


#elif Method == 1
/*
 题目要求是从外向里顺时针打印矩阵，那么就来看一下怎么一圈一圈的打印
 1. 首先我们需要知道每一圈开始的坐标，该坐标的最大值就是最后需要打印的一圈的开始值
 2. 知道开始坐标之后（就知道了结束坐标cols - 1 - start）就可以开打了，然后图并不都是标准的，可能存在各种情况
    1）从左到右打印一行，这个肯定可以打印
    2）从上到下打印一行，有条件
    3）从右到左打印一行，有条件
    4）从下到上打印一行，有条件
 */
void PrintMatrixInCircle(int** numbers, int columns, int rows, int start);
void printNumber(int number);

void PrintMatrixClockwisely(int** numbers, int columns, int rows)
{
    if(numbers == nullptr || columns <= 0 || rows <= 0)
        return;

    int start = 0;

    while(columns > start * 2 && rows > start * 2)
    {
        PrintMatrixInCircle(numbers, columns, rows, start);

        ++start;
    }
}

void PrintMatrixInCircle(int** numbers, int columns, int rows, int start)
{
    int endX = columns - 1 - start;
    int endY = rows - 1 - start;

    // 从左到右打印一行
    for(int i = start; i <= endX; ++i)
    {
        int number = numbers[start][i];
        printNumber(number);
    }

    // 从上到下打印一列
    if(start < endY)
    {
        for(int i = start + 1; i <= endY; ++i)
        {
            int number = numbers[i][endX];
            printNumber(number);
        }
    }

    // 从右到左打印一行
    if(start < endX && start < endY)
    {
        for(int i = endX - 1; i >= start; --i)
        {
            int number = numbers[endY][i];
            printNumber(number);
        }
    }

    // 从下到上打印一行
    if(start < endX && start < endY - 1)
    {
        for(int i = endY - 1; i >= start + 1; --i)
        {
            int number = numbers[i][start];
            printNumber(number);
        }
    }
}

void printNumber(int number)
{
    printf("%d\t", number);
}

#endif

// ====================测试代码====================
void Test(int columns, int rows)
{
    printf("Test Begin: %d columns, %d rows.\n", columns, rows);

    if(columns < 1 || rows < 1)
        return;

    int** numbers = new int*[rows];
    for(int i = 0; i < rows; ++i)
    {
        numbers[i] = new int[columns];
        for(int j = 0; j < columns; ++j)
        {
            numbers[i][j] = i * columns + j + 1;
        }
    }

    PrintMatrixClockwisely(numbers, columns, rows);
    printf("\n");

    for(int i = 0; i < rows; ++i)
        delete[] (int*)numbers[i];

    delete[] numbers;
}

int main(int argc, char* argv[])
{
    /*
    1
    */
    Test(1, 1);

    /*
    1    2
    3    4
    */
    Test(2, 2);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    */
    Test(4, 4);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    21   22   23   24   25
    */
    Test(5, 5);

    /*
    1
    2
    3
    4
    5
    */
    Test(1, 5);

    /*
    1    2
    3    4
    5    6
    7    8
    9    10
    */
    Test(2, 5);

    /*
    1    2    3
    4    5    6
    7    8    9
    10   11   12
    13   14   15
    */
    Test(3, 5);

    /*
    1    2    3    4
    5    6    7    8
    9    10   11   12
    13   14   15   16
    17   18   19   20
    */
    Test(4, 5);

    /*
    1    2    3    4    5
    */
    Test(5, 1);

    /*
    1    2    3    4    5
    6    7    8    9    10
    */
    Test(5, 2);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14    15
    */
    Test(5, 3);

    /*
    1    2    3    4    5
    6    7    8    9    10
    11   12   13   14   15
    16   17   18   19   20
    */
    Test(5, 4);

    return 0;
}

