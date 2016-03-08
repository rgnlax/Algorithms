//Во всех вариантах данной задачи необходимо реализовать указанный алгоритм сортировки массива целых чисел. Количество чисел в массиве определяется окончанием стандартного потока ввода и заранее не известно.

#include <iostream>
#include <vector>

void selectionSort(int *array, size_t count);

int main() {
    std::vector<int> arr;
    //Ввод данных в массив
    while(true) {
        int number;
        std::cin >> number;
        if(std::cin.fail()) { break; }
        arr.push_back(number);
    }
    //Сортировка
    selectionSort(&arr[0], arr.size());
    
    //Вывод
    for(size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    
    return 0;
}

void selectionSort(int *array, size_t count) {
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