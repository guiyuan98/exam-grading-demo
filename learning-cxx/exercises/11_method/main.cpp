#include "../exercise.h"
#include <iostream>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 构造函数，初始化缓存
    Fibonacci() : cached(2) {
        cache[0] = 0;
        cache[1] = 1;
    }

    // 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        if (i < cached) {
            return cache[i];
        }
        for (int j = cached; j <= i; ++j) {
            cache[j] = cache[j - 1] + cache[j - 2];
        }
        cached = i + 1;
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体，使计算正确
    Fibonacci fib;
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}