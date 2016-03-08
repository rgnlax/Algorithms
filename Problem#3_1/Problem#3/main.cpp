//3_2. Дан массив целых чисел А[0..n-1]). Известно, что на интервале [0, m] значения массива строго возрастают, а на интервале [m, n-1] строго убывают. Найти m за O(log m).

#include <iostream>
#define NOT_FOUND -1

void inputNumbers(int **, int);
int descendingPointIndex(int *const, int, int, int);
int searchIndex(int *const, int);


int main() {
    
    int numbersCount;
    std::cin >> numbersCount;
    
    int *arrayOfNumbers;
    inputNumbers(&arrayOfNumbers, numbersCount);
    
    int index = searchIndex(arrayOfNumbers, numbersCount);
    std::cout << index;
    
    delete[] arrayOfNumbers;
    return 0;
}

int descendingPointIndex(int *const arrayOfNumbers, int count, int firstIndex, int lastIndex) {
    int middleIndex = (lastIndex - firstIndex) / 2 + firstIndex;
   
    //Если элемент больше правого и больше левого - возвращаем
    if (arrayOfNumbers[middleIndex] > arrayOfNumbers[middleIndex + 1] &&
        arrayOfNumbers[middleIndex] > arrayOfNumbers[middleIndex - 1])
        return middleIndex;
    //Если элемент больше левого и меньше правого - смещаемся вправо
    if (arrayOfNumbers[middleIndex] > arrayOfNumbers[middleIndex - 1] &&
        arrayOfNumbers[middleIndex] < arrayOfNumbers[middleIndex + 1])
        return descendingPointIndex(arrayOfNumbers, count, middleIndex, lastIndex);
    //Если элемент больше правого и меньше левого смещаемся влево
    if (arrayOfNumbers[middleIndex] > arrayOfNumbers[middleIndex + 1] &&
        arrayOfNumbers[middleIndex] < arrayOfNumbers[middleIndex - 1])
        return descendingPointIndex(arrayOfNumbers, count, firstIndex, middleIndex);
  
    return NOT_FOUND;
}

int searchIndex(int *const arrayOfNumbers, int count) {
   
    //Если массив сразу убывает вернуть 0
    if (arrayOfNumbers[0] > arrayOfNumbers[1]) {
        return 0;
    }
    //Устанавливаем начальную точку 0
    int prevousIndex = 0;
    //Конечная точка - 1, каждый раз увеличиваем в два раза
    for (int nextIndex = 1;; nextIndex *= 2) {
        
        //Если длина массива 2 - вернуть индекс максимального
        if (count == 2) {
            return arrayOfNumbers[prevousIndex] > arrayOfNumbers[nextIndex] ? prevousIndex: nextIndex;
        }
        //Если предыдущий индекс равен концу массива - возвращаем его
        if (prevousIndex == count - 1) {
            return prevousIndex;
        }
        //Если следующий индекс выходит за границы устанавливаем его в конец массива
        nextIndex = (nextIndex < count - 1) ? nextIndex : count - 1;
        //Если найден интервал перелома - ищем индекс элемента
        if (arrayOfNumbers[nextIndex] < arrayOfNumbers[nextIndex - 1]) {
            return descendingPointIndex(arrayOfNumbers, count, prevousIndex, nextIndex);
        }
        prevousIndex = nextIndex;
    }
    return NOT_FOUND;
}

void inputNumbers(int **arrayOfNumbers, int numbersCount) {
    *arrayOfNumbers = new int[numbersCount];
    for (int i = 0; i < numbersCount; ++i) {
        std::cin >> (*arrayOfNumbers)[i];
    }
}


