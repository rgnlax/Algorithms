//7_1. Быстрейшая сортировка.Дан массив целых чисел в диапазоне [0..10^9]. Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^7 элементов. Все значения массива являются элементами псевдо-рандомной последовательности. Необходимо отсортировать элементы массива за минимально время и вывести каждый десятый элемент отсортированной последовательности. Минимальный набор оптимизаций, который необходимо реализовать:
//1. Оптимизация ввода/вывода
//2. Оптимизация выбора опорного элемента
//3. Оптимизация Partition
//4. Оптимизация рекурсии
//5. Оптимизация концевой рекурсии



#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#define MAX_COUNT 25000000


template <class T>
size_t findPivotIndex(T *arr, size_t begin, size_t end) {
    //Рандомный индекс опорного элемента
    return begin + (rand() % (end - begin + 1));
}

template <class T>
T Partition(T* arr, size_t begin, size_t end) {
    //Реализация стратегии выбора опорного элемента - случайный
    size_t pivotIndex = findPivotIndex(arr, begin, end);
    std::swap(arr[begin], arr[pivotIndex]);
    T pivot = arr[begin];
    
    //Итераторы
    size_t i = begin + 1;
    size_t j = end;
    
    //Hoare partition
    while (true) {
        while (i <= end && arr[i] < pivot) {
            i++;
        }
        while (j >= begin && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            std::swap(arr[i], arr[j]);
            ++i;
            --j;
        } else {
            std::swap(arr[begin], arr[i - 1]);
            return i - 1;
        }
    }
}

inline bool scanInt(long *number) {
    //Нагугленный быстрый ввод
    long resultNumber = 0;
    long numberChar = getchar_unlocked();
    if (numberChar == EOF) {
        return false;
    }
    for(; numberChar > 47 && numberChar < 58 ; numberChar = getchar_unlocked()) {
        resultNumber = (resultNumber << 1) + (resultNumber << 3) + numberChar - 48;
    }
    *number = resultNumber;
    return true;
}

inline void print(long number) {
    //Нагугленный быстрый вывод
    int i = 0;
    char buffer[20];
    while(number > 0) {
        buffer[i++] = number % 10 + '0';
        number = number / 10;
    }
    --i;
    while(i >= 0) {
        putchar_unlocked(buffer[i--]);
    }
    putchar_unlocked(' ');
}

template <class T>
void sort(T*, size_t, size_t);

int main() {
    long *numbers = new long[MAX_COUNT];
    int count = 0;
    while (scanInt(&numbers[count])) {
        count++;
    }
    
    sort(numbers, 0, count - 1);
    
    for (int i = 9; i < count; i+=10) {
        print(numbers[i]);
    }
    delete[] numbers;
    return 0;
}

template <class T>
void selectionSort(T *array, size_t count) {
    for (int i = 0; i < count - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (array[j] < array[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(array[i], array[minIndex]);
    }
}


template <class T>
void sort(T *array, size_t begin, size_t end) {
    //Пока начальный индекс меньше конечного
    while (begin < end) {
        //Используем концевую рекурсию если размер массива - 40
        if (end - begin <= 40) {
            selectionSort(array + begin, end - begin + 1);
            break;
        }
        //Опорный элемент
        size_t pivot = Partition(array, begin, end);
        //Разделяй и сортируй
        if (pivot - begin > end - pivot) {
            sort(array, pivot + 1, end);
            end = pivot - 1;
        } else {
            sort(array, begin, pivot - 1);
            begin = pivot + 1;
        }
    }
}

