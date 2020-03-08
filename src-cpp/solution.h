#pragma once


// Это решение должно работать намного быстрее на больших числах, т.к. проверяет только последний бит,
// и компьютеру не нужно делать операции деления и вычитания.
bool isEven(int value) {
    return (value & 1) == 0;
}

// На базе односвязного списка, добавление и удаление за О(1)
template <typename T>
struct FIFO {
public:
    struct Node {
        explicit Node(const T& data): data(data), next(nullptr) {}

        explicit Node(T&& data): data(std::move(data)), next(nullptr) {}

        T data;
        Node* next;
    };

    FIFO(): first(nullptr), last(nullptr) {}

    void append(T&& data)
    {
        Node* node = new Node(std::forward<T>(data));

        if (first == nullptr) {
            first = node;
        } else {
            last->next = node;
        }
        last = node;
    }

    void append(T& data) {
        append(std::move(data));
    }

    T pop() {
        if (first != nullptr) {
            if (first->next != nullptr) {
                Node *node = first;
                first = node->next;
                T data = std::move(node->data);
                delete node;
                return data;
            } else {
                Node *node = first;
                T data = std::move(node->data);
                delete node;
                first = last = nullptr;
                return data;
            }
        }

        throw std::out_of_range("FIFO is empty\n");
    }

    ~FIFO() {
        while (first != nullptr)
            pop();
    }

private:
    Node* first;
    Node* last;
};


// реализовано на массиве - pop() за O(n), append() за O(1), но нет указателей
// и может быть в каком-то смысле проще для понимания
// для простоты
template <typename T>
class FIFO2 {
public:
    explicit FIFO2(size_t new_capacity): first(0), last(0), capacity(new_capacity), arr(new T[new_capacity]){}
    FIFO2(): first(0), last(0), arr(new T[capacity]) {}

    void append(T&& data) {
        if (last == capacity)
            throw std::out_of_range("FIFO is full\n");
        arr[last] = data;
        last++;

    }

    void append(T& data) {
        append(std::move(data));
    }

    T pop() {
        if (last == first)
            throw std::out_of_range("FIFO is empty\n");

        T data = std::move(arr[0]);
        for (size_t i = 0; i < last-1; ++i) {
            arr[i] = std::move(arr[i+1]);
        }
        last--;
        return data;
    }

    ~FIFO2() {
        delete[] arr;
    }

private:
    size_t first, last;
    size_t capacity = 20;
    T* arr;
};


/* QuickSort дает O(N^2) в худшем случае, может плохо себя вести в случае отсортированного массива
 * MergeSort дает O(logN) во всех, но занимает много места в памяти
 * HeapSort дает O(logN), но не стабилен
 * Insertion Sort дает O(n) для отсортированного массива, но O(n^2) для отсортированного в обратном порядке
 * Реализуем MergeSort - мы не знаем какой будет вход и хотим хорошую сортировку на всех входах,
 * про память в задаче ничего не сказано, у MergeSort меньшая константа, можно распаралеллить, стабильная */

template <typename T>
void merge(T arr[], size_t l, size_t m, size_t r)
{
    size_t i, j, k;
    size_t size_left = m - l + 1;
    size_t size_right =  r - m;

    T L[size_left], R[size_right];

    for (i = 0; i < size_left; ++i)
        L[i] = std::move(arr[l + i]);
    for (j = 0; j < size_right; ++j)
        R[j] = std::move(arr[m + 1 + j]);

    i = j = 0;
    k = l;

    while (i < size_left && j < size_right)
    {
        if (L[i] <= R[j])
        {
            arr[k] = std::move(L[i]);
            i++;
        }
        else
        {
            arr[k] = std::move(R[j]);
            j++;
        }
        k++;
    }

    while (i < size_left)
    {
        arr[k] = std::move(L[i]);
        i++;
        k++;
    }

    while (j < size_right)
    {
        arr[k] = std::move(R[j]);
        j++;
        k++;
    }
}

template <typename T>
void merge_sort(T arr[], size_t l, size_t r) {
    if (l < r) {
        size_t m = (l + r) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge<T>(arr, l, m, r);
    }
}
