//2_4. Строки. Напишите программу, печатающую набор строк в лексикографическом порядке. Строки разделяются символом перевода строки '\n'. Если последний символ в потоке ввода '\n', считать, что после него нет пустой строки. Максимальная длина строки 255 символов. Написать свою функцию сравнения строк.

#include <iostream>
#include "string"

template <class T>
void q(T*, int, bool(*compare)(T, T));

template <class T>
bool compare(T, T);

template <>
bool compare(std::string obj1, std::string obj2);

int main() {
    int count;
    std::cin >> count;
    
    //Массив строк
    std::string *array = new std::string[count];
    for (int i = 0; i < count; ++i) {
        std::cin >> array[i];
    }
    
    //Сортировка
    HeapSort(array, count, compare);
    
    //Вывод
    for (int i = 0; i < count; ++i) {
        std::cout << array[i] << std::endl;
    }
    return 0;
}

template <class T>
void siftDown(T* arr, int index, int count, bool(*compare)(T, T)) {
    //Индекс правого и левого сына
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    
    int indexOfLargest = index;
    
    //Находим индекс наибольшего элемента
    if (leftIndex < count && compare(arr[leftIndex], arr[index])) {
        indexOfLargest = leftIndex;
    }
    if (rightIndex < count && compare(arr[rightIndex], arr[indexOfLargest])) {
        indexOfLargest = rightIndex;
    }
    //Если он не равен начальному индекса - меняем местами и вызываем метод дальше
    if (indexOfLargest != index) {
        std::swap(arr[indexOfLargest], arr[index]);
        siftDown(arr, indexOfLargest, count, compare);
    }
}

template <class T>
void HeapSort(T *arr, int count, bool(*compare)(T, T)) {
    //Строим кучу
    for (int i = count / 2 - 1; i >= 0; --i) {
        siftDown(arr, i, count, compare);
    }
    //Упорядочиваем массив
    for (int i = count - 1; i >= 1; --i) {
        //Меняем местами первый и i элемент
        std::swap(arr[i], arr[0]);
        //Проталкиваем вниз i элемент
        siftDown(arr, 0, i, compare);
    }
}

template <class T>
bool compare(T obj1, T obj2) {
    return obj1 > obj2;
}

template <>
bool compare(std::string obj1, std::string obj2) {
    size_t minLenght = (obj1.length() < obj2.length() ? obj1.length() : obj2.length());
    for (size_t i = 0; i < minLenght; ++i) {
        if (obj1[i] != obj2[i]) {
            return obj1[i] > obj2[i];
        }
    }
    return obj1.length() != minLenght;
}