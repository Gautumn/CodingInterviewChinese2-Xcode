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

// 面试题41：数据流中的中位数
// 题目：如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么
// 中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，
// 那么中位数就是所有数值排序之后中间两个数的平均值。

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;


#define Method 0



#if Method == 0

/*
 思路：使用优先队列实现
 左边是最大堆，右边是最小堆。左边元素全部小于右边。
 
 */

#include <queue>

template <typename T>
class DynamicArray {
public:
    void Insert(T num) {
        if (((maxPQ.size() + minPQ.size()) & 0x01) == 0) {
            if (maxPQ.size() > 0 && num < maxPQ.top()) {
                maxPQ.push(num);
                
                num = maxPQ.top();
                maxPQ.pop();
            }
            minPQ.push(num);
        }
        else {
            if (minPQ.size() > 0 && num > minPQ.top()) {
                minPQ.push(num);
                
                num = minPQ.top();
                minPQ.pop();
            }
            maxPQ.push(num);
        }
    }
    
    const T GetMedian() {
        size_t size = maxPQ.size() + minPQ.size();
        if (size == 0)
            throw ("no member available.");
        
        if (size & 0x01) {
            return minPQ.top();
        }
        else {
            return (minPQ.top() + maxPQ.top()) / 2;
        }
    }

private:
    std::priority_queue<T, std::vector<T>, std::less<T>>    maxPQ;
    std::priority_queue<T, std::vector<T>, std::greater<T>> minPQ;
};




#elif Method == 100

template<typename T> class DynamicArray
{
public:
    void Insert(T num)
    {
        if(((min.size() + max.size()) & 1) == 0)
        {
            if(max.size() > 0 && num < max[0])
            {
                max.push_back(num);
                push_heap(max.begin(), max.end(), less<T>());

                num = max[0];

                pop_heap(max.begin(), max.end(), less<T>());
                max.pop_back();
            }

            min.push_back(num);
            push_heap(min.begin(), min.end(), greater<T>());
        }
        else
        {
            if(min.size() > 0 && min[0] < num)
            {
                min.push_back(num);
                push_heap(min.begin(), min.end(), greater<T>());

                num = min[0];

                pop_heap(min.begin(), min.end(), greater<T>());
                min.pop_back();
            }

            max.push_back(num);
            push_heap(max.begin(), max.end(), less<T>());
        }
    }

    T GetMedian()
    {
        int size = min.size() + max.size();
        if(size == 0)
            throw ("No numbers are available");

        T median = 0;
        if((size & 1) == 1)
            median = min[0];
        else
            median = (min[0] + max[0]) / 2;

        return median;
    }

private:
    vector<T> min;
    vector<T> max;
};

#endif

// ====================测试代码====================
void Test(char* testName, DynamicArray<double>& numbers, double expected)
{
    if(testName != nullptr)
        printf("%s begins: ", testName);

    if(abs(numbers.GetMedian() - expected) < 0.0000001)
        printf("Passed.\n");
    else
        printf("FAILED.\n");
}

int main(int argc, char* argv[])
{
    DynamicArray<double> numbers;

    printf("Test1 begins: ");
    try
    {
        numbers.GetMedian();
        printf("FAILED.\n");
    }
    catch(...)
    {
        printf("Passed.\n");
    }

    numbers.Insert(5);
    Test("Test2", numbers, 5);

    numbers.Insert(2);
    Test("Test3", numbers, 3.5);

    numbers.Insert(3);
    Test("Test4", numbers, 3);

    numbers.Insert(4);
    Test("Test6", numbers, 3.5);

    numbers.Insert(1);
    Test("Test5", numbers, 3);

    numbers.Insert(6);
    Test("Test7", numbers, 3.5);

    numbers.Insert(7);
    Test("Test8", numbers, 4);

    numbers.Insert(0);
    Test("Test9", numbers, 3.5);

    numbers.Insert(8);
    Test("Test10", numbers, 4);

    return 0;
}
