#include <iostream>
#include <cassert>
#include "solution.h"

int main() {
    assert(!isEven(5));
    assert(isEven(6));

    auto queue = FIFO<int>();
    queue.append(5);
    int temp = 6;
    queue.append(temp);
    int ans1 = queue.pop();
    int ans2 = queue.pop();
    assert(ans1 == 5 && ans2 == 6);

    auto queue2 = FIFO2<int>();
    queue2.append(5);
    queue2.append(temp);
    ans1 = queue2.pop();
    ans2 = queue2.pop();
    assert(ans1 == 5 && ans2 == 6);

    const size_t length = 5;
    int arr[length] {8, 10, 2, 4, 0};
    merge_sort(arr, 0, length-1);
    int sorted_array[length] {0, 2, 4, 8, 10};
    for (size_t i = 0; i<length; ++i) {
        assert(arr[i] == sorted_array[i]);
    }
    return 0;
}
