//Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n). 4_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.


#include <iostream>
#include <vector>
#include <cstdlib>

template <class T>
T Partition(std::vector<T>&, int, int);
template <class T>
T findKOrderStatistic(std::vector<T>& arr, int k);

int main() {
    int numberCount, k;
    std::cin >> numberCount >> k;
    std::vector<int> array;
    for (int i = 0; i < numberCount; ++i) {
        int number;
        std::cin >> number;
        array.push_back(number);
    }
    std::cout << findKOrderStatistic(array, k);
    return 0;
}

template <class T>
T Partition(std::vector<T>& arr, int begin, int end) {
    //Реализация стратегии выбора опорного элемента "случайный элемент"
    int pivot = begin + (rand() % ( end - begin + 1));
    std::swap(arr[begin], arr[pivot]);
    
    //Итераторы с конца
    int i = end;
    int j = end;
    
    //Пока итератор указывающий на последний непроверенный элемент не указывает на начало
    while (j > begin) {
        //Если опорный элемент меньше чем текущий - свап
        if (arr[begin] < arr[j]) {
            std::swap(arr[j], arr[i]);
            j--;
            i--;
        } else {
            j--;
        }
    }
    //вернуть опорный элемент
    std::swap(arr[i], arr[begin]);
    return i;
}

template <class T>
T findKOrderStatistic(std::vector<T>& arr, int k) {
    //Левая и правая граница массива
    int left = 0, right = arr.size() - 1;
    while (true) {
        //Находим позицию опорного элемента
        int mid = Partition(arr, left, right);
        
        //Если она равна k - выводим
        if (mid == k) {
            return arr[mid];
        }
        //Сужаем границы массива
        else if (k < mid) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
}
