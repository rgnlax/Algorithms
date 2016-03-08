//5_2. Сортировка почти упорядоченной последовательности. Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

#include <iostream>
#include <vector>

template <class T>
void merge(T *a, size_t a_len, T *b, size_t b_len, T *c);
template <class T>
void mergeSort(T *a, int count);
template <class T>
void improvedSort(std::vector<T>& arr, int k);

int main() {
    int numbersCount, k;
    std::cin >> numbersCount >> k;
    
    std::vector<int>numbers;
    for (int i = 0; i < numbersCount; ++i) {
        int number;
        std::cin >> number;
        numbers.push_back(number);
    }
    
    improvedSort(numbers, k);
    
    for (int i = 0; i < numbersCount; ++i) {
        std::cout << numbers[i] << ' ';
    }
    return 0;
}

template <class T>
void merge(T *a, size_t a_len, T *b, size_t b_len, T *c) {
    int i = 0;
    int j = 0;
    
    for (; i < a_len and j < b_len;) {
        if (a[i] < b[j]) {
            c[i + j] = a[i];
            ++i;
        } else {
            c[i + j] = b[j];
            ++j;
        }
    }
    if (i == a_len) {
        for (; j < b_len; ++j) {
            c[i + j] = b[j];
        }
    } else if (j == b_len) {
        for (; i < a_len; ++i) {
            c[i + j] = a[i];
        }
    }
}

template <class T>
void mergeSort(T *a, int count) {
    //Создаем временный массив
    T * tempArray = new T[count];
    //Цикл по размерам массива для слияния
    for (int i = 1; i < count; i *= 2) {
        //offset - переменная хранящая расстояние до следующего массива для слияния
        int offset = 0;
        //Цикл до тех пор пока offset + i не превышает размер массива
        for (; offset + i < count; offset += i * 2) {
            merge(a + offset, i, a + offset + i, std::min(i, count - i - offset), tempArray + offset);
        }
        //Копируем остаток
        if (offset < count) {
            for (int i = offset; i < count; ++i) {
                tempArray[i] = a[i];
            }
        }
        for (int i = 0; i < count; ++i) {
            a[i] = tempArray[i];
        }
    }
    delete[] tempArray;
}

template <class T>
void improvedSort(std::vector<T>& arr, int k) {
    size_t size = arr.size();
    //Вначале сортируем первые k элементов
    mergeSort(&arr[0], k);
    //Затем цикл пока i меньше размера массива
    for (int i = k; i < size; i += k) {
        int minSize = std::min(k, (int)size - i);
        //Сортируем следующие k элеметов
        mergeSort(&arr[i], minSize);
        //Сливаем первые k и вторые k элементов
        T *mergedArray = new T[2*k];
        merge(&arr[i - k], k, &arr[i], minSize, mergedArray);
        for (int j = 0; j <  2*k; j++) {
            arr[i - k + j] = mergedArray[j];
        }
    }
}