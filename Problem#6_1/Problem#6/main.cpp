//6_4. Скользящий максимум. Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некотрого окна (последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n log n) .Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n строк со значением каждого элемента. Затем вводится k  - размер окна. Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения окна.

#include <iostream>

struct Element {
    int value;
    int index;
    Element():value(0), index(0){}
    Element(int value, int index):value(value), index(index){}
};

class Heap {
    Element *buffer;
    int bufferSize;
    int realSize;
    void siftUp(int index);
    void siftDown(int index);
    void grow();
    
public:
    Heap():bufferSize(1), realSize(0) {
        buffer = new Element[bufferSize];
    }
    Heap(Element *elements, int count) {
        bufferSize = count;
        buffer = new Element[bufferSize];
        for (int i = 0; i < count; ++i) {
            buffer[i] = elements[i];
        }
        realSize = count;
        for (int i = count / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }
    ~Heap() {
        delete[] buffer;
    }
    Element showMax();
    Element extractMax();
    void addElement(Element element);
};

void Heap::grow() {
    int newBufferSize = 2 * bufferSize;
    Element *newBuffer = new Element[newBufferSize];
    for (int i = 0; i < realSize; ++i) {
        newBuffer[i] = buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
}

Element Heap::extractMax() {
    Element max = buffer[0];
    buffer[0] = buffer[--realSize];
    siftDown(0);
    return max;
}

void Heap::siftDown(int index) {
    int leftIndex = 2 * index + 1;
    int rightIndex = 2 * index + 2;
    
    int indexOfLargest = index;
    
    if (leftIndex < realSize && buffer[leftIndex].value > buffer[index].value) {
        indexOfLargest = leftIndex;
    }
    if (rightIndex < realSize && buffer[rightIndex].value > buffer[indexOfLargest].value) {
        indexOfLargest = rightIndex;
    }
    if (indexOfLargest != index) {
        std::swap(buffer[indexOfLargest], buffer[index]);
        siftDown(indexOfLargest);
    }
}

void Heap::siftUp(int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (buffer[parentIndex].value >= buffer[index].value) {
            return;
        }
        std::swap(buffer[parentIndex], buffer[index]);
        index = parentIndex;
    }
}

Element Heap::showMax() {
    return buffer[0];
}

void Heap::addElement(Element element) {
    if (bufferSize == realSize) {
        grow();
    }
    buffer[realSize++] = element;
    siftUp(realSize - 1);
}

void inputNumbers(Element *arrayOfElements, int numbersCount);

int main() {
    
    //freopen( "/Users/maksim/test.txt", "r", stdin );
    //freopen( "/Users/maksim/out.txt", "w", stdout );
    int numbersCount;
    std::cin >> numbersCount;
    
    Element *arrayOfElements = new Element[numbersCount];
    inputNumbers(arrayOfElements, numbersCount);
    
    int sectionWidth;
    std::cin >> sectionWidth;
    
    //Инициализируем массив под максимумы
    Element *maximums = new Element[numbersCount - sectionWidth + 1];
    
    //Создаем кучу
    Heap heap(arrayOfElements, sectionWidth - 1);
    
    for (int i = sectionWidth - 1; i < numbersCount; ++i) {
        //Добавляем в кучу элемент
        Element el = arrayOfElements[i];
        heap.addElement(el);
        //Если максимум вышел за границы окна - вытаскиваем его
        while (heap.showMax().index < i - sectionWidth + 1) {
            heap.extractMax();
        }
        maximums[i - sectionWidth + 1] = heap.showMax();
    }
    
    for (int i = 0; i < numbersCount - sectionWidth + 1; ++i) {
        std::cout << maximums[i].value;
        if (i != numbersCount - sectionWidth) {
            std::cout << ' ';
        }
    }
    delete[] maximums;
    delete[] arrayOfElements;
    return 0;
}

void inputNumbers(Element *arrayOfElements, int numbersCount) {
    for (int i = 0; i < numbersCount; ++i) {
        int value;
        std::cin >> value;
        Element el = Element(value, i);
        arrayOfElements[i] = el;
    }
}
