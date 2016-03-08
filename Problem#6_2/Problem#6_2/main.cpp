//6_3. Binary MSD для long long. Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).


#include <iostream>
#include <vector>

#define digit(number, offset) ((number >> offset) & 1)


template <class T>
void binaryQuickSort(std::vector<T>&arr, int left, int right, int offset);

int main() {
    int numbersCount;
    std::cin >> numbersCount;
    
    std::vector<long long> numbers;
    for (int i = 0; i < numbersCount; ++i) {
        long long number;
        std::cin >> number;
        numbers.push_back(number);
    }
    
    binaryQuickSort(numbers, 0, numbersCount - 1, 63);
    
    for (int i = 0; i < numbersCount; ++i) {
        std::cout << numbers[i] << ' ';
    }
    return 0;
}

template <class T>
void binaryQuickSort(std::vector<T>&arr, int left, int right, int offset) {
    //итератор для нулевый разрядов
    int i = left;
    //итератор для единичных разрядов
    int j = right;
    //Если правая граница меньше левой или сдвиг меньше 0  - то выходим
    if (right <= left || offset < 0) {
        return;
    }
    //Пока правый итератор не равен левому
    while (j != i) {
        //Идем от начала и ищем все числа где число в текущем разряде = 0
        while (digit(arr[i], offset) == 0 && (i < j)) {
            i++;
        }
        //Идем с конца и ищем все числа где число в текущем разряде = 1
        while (digit(arr[j], offset) == 1 && (j > i)) {
            j--;
        }
        //Затем свапаем i и j элемент
        std::swap(arr[i], arr[j]);
    }
    //Смещаем левый итератор при условии
    if (digit(arr[right], offset) == 0) {
        j++;
    }
    //рекурсивные вызовы для массивов 
    binaryQuickSort(arr, left, j - 1, offset - 1);
    binaryQuickSort(arr, j, right, offset - 1);
}




