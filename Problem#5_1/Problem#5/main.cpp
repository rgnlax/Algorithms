//
//  main.cpp
//  Problem#5
//
//  Created by Maxim Pedchenko on 14.03.15.
//  Copyright (c) 2015 MP. All rights reserved.
//

#include <iostream>
#include <cstring>

#define EMPTY_STACK -1
#define MAX_WORD_LEN 1024

//Шаблонный класс стек
template <class T>
class Stack {
    
private:
    int mBufferSize;
    T *mBuffer;
    void grow();
    
public:
    int mTopIndex;
    Stack():mBufferSize(1), mTopIndex(-1) {
        mBuffer = new T[mBufferSize];
    };
    
    ~Stack() {
        delete[] mBuffer;
    }
    
    T pop();
    void push(T element);
    T showTop();
};

template <class T>
T Stack<T>::pop() {
    if (mTopIndex == -1) {
        return EMPTY_STACK;
    }
    return mBuffer[mTopIndex--];
}

template <class T>
void Stack<T>::push (T element) {
    if (mTopIndex + 1 == mBufferSize) {
        grow();
    }
    mBuffer[++mTopIndex] = element;
}

template <class T>
T Stack<T>::showTop() {
    if (mTopIndex == -1) {
        return EMPTY_STACK;
    }
    return mBuffer[mTopIndex];
}


template <class T>
void Stack<T>::grow() {
    int newBufferSize = 2 * mBufferSize;
    T *newBuffer = new T[newBufferSize];
    for (int i = 0; i <= mTopIndex; ++i) {
        newBuffer[i]= mBuffer[i];
    }
    delete[] mBuffer;
    mBuffer = newBuffer;
    mBufferSize = newBufferSize;
}

//Класс слова
class Word {
    char *buffer;
    
public:
    int lenght;
    Word():lenght(0){
        buffer = new char[MAX_WORD_LEN];
    }
    ~Word() {
        delete[] buffer;
    }
    char getAt(int index) {
        return buffer[index];
    }
    void append(char symbol){
        buffer[lenght++] = symbol;
    }
    friend std::ostream& operator<<(std::ostream& os, const Word& obj) {
        os << obj.buffer;
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Word& obj) {
        is >> obj.buffer;
        obj.lenght = (int)strlen(obj.buffer);
        return is;
    }
    friend bool operator==(const Word& first, const Word& second){
        if (first.lenght != second.lenght) {
            return false;
        }
        bool matched = true;
        for (int i = 0; i < first.lenght; ++i) {
            matched = first.buffer[i] == second.buffer[i];
            if (!matched) {
                break;
            }
        }
        return matched;
    }
};

bool checkAnagramms(Word&, Word&);

int main() {
    Word firstWord, secondWord;
    std::cin >> firstWord >> secondWord;
    
    bool isPossible = checkAnagramms(firstWord, secondWord);
    std::cout << (isPossible ? "YES" : "NO");
    return 0;
}

bool checkAnagramms(Word& firstWord, Word& secondWord) {
    Stack<char> stack;
    int checkingIndex = 0;
    Word resultAnagramm;
    for (int i = 0; i < firstWord.lenght; ++i) {
        //Выпушиваем из стека элементы если подходят
        while (stack.showTop() == secondWord.getAt(checkingIndex)) {
            resultAnagramm.append(stack.pop());
            checkingIndex++;
        }
        //Если совпадает очередная буква первого слова с буквой второго - добавить в выходное слово
        if (firstWord.getAt(i) == secondWord.getAt(checkingIndex)) {
            resultAnagramm.append(firstWord.getAt(i));
            checkingIndex++;
        //Если не совпадает - запушиваем в стек
        } else {
            stack.push(firstWord.getAt(i));
        }
    }
    //По окончанию цилка выпушить все из стека в выходное слово
    while (stack.mTopIndex != EMPTY_STACK) {
        resultAnagramm.append(stack.pop());
    }
    return secondWord == resultAnagramm;
}


