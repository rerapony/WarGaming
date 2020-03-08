# coding=utf-8


# Это решение должно работать намного быстрее на больших числах, т.к. проверяет только последний бит,
# и компьютеру не нужно делать операции деления и вычитания.
def is_even(value):
    return (value & 1) == 0


# Всё понятно, использует принцип связного списка, удаление и добавление за О(1)
class FIFO:
    class Node:
        def __init__(self, data):
            self.data = data
            self.next = None

    def __init__(self):
        self.first = None
        self.last = None

    def append(self, data):
        node = self.Node(data)
        if self.first is None:
            self.first = node
        else:
            self.last.next = node
        self.last = node

    def pop(self):
        if self.first is None:
            raise IndexError
        node = self.first
        self.first = node.next
        return node.data


# Более удобная имплементация, т.к. использует встроенные списки, но удаление-добавление за O(n)
class FIFO2:
    def __init__(self):
        self.data = []

    def append(self, data):
        self.data.append(data)

    def pop(self):
        return self.data.pop(0)


# QuickSort дает O(N^2) в худшем случае, может плохо себя вести в случае отсортированного массива
# MergeSort дает O(logN) во всех, но занимает много места в памяти
# HeapSort дает O(logN), но не стабилен
# Insertion Sort дает O(n) для отсортированного массива, но O(n^2) для отсортированного в обратном порядке
# Реализуем MergeSort - мы не знаем какой будет вход и хотим хорошую сортировку на всех входах,
# про память в задаче ничего не сказано, у MergeSort меньшая константа, можно распаралеллить, стабильная

def merge_sort(arr, l, r):
    if l < r:
        m = (l + r) // 2
        merge_sort(arr, l, m)
        merge_sort(arr, m + 1, r)
        merge(arr, l, m, r)


def merge(arr, l, m, r):
    left_arr = arr[l:m + 1]
    right_arr = arr[m + 1:r + 1]

    i = j = 0
    k = l

    while i < len(left_arr) and j < len(right_arr):
        if left_arr[i] <= right_arr[j]:
            arr[k] = left_arr[i]
            i += 1
        else:
            arr[k] = right_arr[j]
            j += 1

        k += 1

    while i < len(left_arr):
        arr[k] = left_arr[i]
        i += 1
        k += 1

    while j < len(right_arr):
        arr[k] = right_arr[j]
        j += 1
        k += 1


if __name__ == '__main__':
    assert not is_even(5) and is_even(6)

    q = FIFO()
    q.append(5)
    q.append(6)
    assert q.pop() == 5
    assert q.pop() == 6

    q = FIFO2()
    q.append(5)
    q.append(6)
    assert q.pop() == 5
    assert q.pop() == 6

    arr = [8, 10, 2, 4, 0]
    sorted_arr = [0, 2, 4, 8, 10]
    merge_sort(arr, 0, len(arr)-1)
    for i in range(len(arr)):
        assert arr[i] == sorted_arr[i]