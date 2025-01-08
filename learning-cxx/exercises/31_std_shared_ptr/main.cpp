#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 3, "");  // 初始时，use_count 应该是 3

    ptrs[0].reset();
    ASSERT(observer.use_count() == 2, "");  // ptrs[0] 释放后，use_count 应该是 2

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");  // ptrs[1] 释放后，use_count 仍然是 2

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 2, "");  // ptrs[2] 指向新对象，use_count 仍然是 2

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 4, "");  // ptrs[0], ptrs[1], ptrs[2] 和 shared 都指向同一个对象，use_count 应该是 4

    std::ignore = std::move(ptrs[0]);
    ptrs[1] = std::move(ptrs[1]);
    ptrs[1] = std::move(ptrs[2]);
    ASSERT(observer.use_count() == 2, "");  // ptrs[0] 和 ptrs[1] 释放后，use_count 应该是 2

    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");  // shared 指向 observer 指向的对象，use_count 应该是 3

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");  // ptrs 中的所有指针释放后，use_count 应该是 0

    shared = observer.lock();
    ASSERT(observer.use_count() == 0, "");  // shared 不再指向任何对象，use_count 应该是 0

    return 0;
}