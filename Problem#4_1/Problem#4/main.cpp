//4_3. Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
#include <iostream>
#define EMPTY_STACK -1
///////Класс стек
class Stack {
    
private:
    int mBufferSize;
    int *mBuffer;
    void grow();
    
public:
    int mTopIndex;
    Stack():mBufferSize(1), mTopIndex(-1) {
        mBuffer = new int[mBufferSize];
    };
    
    ~Stack() {
        delete[] mBuffer;
    }
    
    int pop();
    void push(int element);
};

int Stack::pop() {
    if (mTopIndex == -1) {
        return EMPTY_STACK;
    }
    return mBuffer[mTopIndex--];
}

void Stack::push (int element) {
    if (mTopIndex + 1 == mBufferSize) {
        grow();
    }
    mBuffer[++mTopIndex] = element;
}

void Stack::grow() {
    int newBufferSize = 2 * mBufferSize;
    int *newBuffer = new int[newBufferSize];
    for (int i = 0; i <= mTopIndex; ++i) {
        newBuffer[i]= mBuffer[i];
    }
    delete[] mBuffer;
    mBuffer = newBuffer;
    mBufferSize = newBufferSize;
}
///////////////////////////////////////////////

//////////////////Очередь//////////////////////
class Queue {

private:
    Stack *firstStack;
    Stack *secondStack;
    void restack(Stack *fromStack, Stack *toStack) {
        while (fromStack->mTopIndex > -1) {
            toStack->push(fromStack->pop());
        }
    }
   
public:
    Queue() {
        firstStack = new Stack();
        secondStack = new Stack();
    }
    
    ~Queue() {
        delete firstStack;
        delete secondStack;
    }
    
    void enqueue(int element);
    int dequeue();

};

void Queue::enqueue(int element) {
    firstStack->push(element);
}

int Queue::dequeue() {
    if (secondStack->mTopIndex == -1) {
        restack(firstStack, secondStack);
    }
    return secondStack->pop();
}
/////////////////////////////////////////////////
bool commandTreatment(int, int, Queue&);

int main(int argc, const char * argv[]) {
    
    Queue q;
    
    int commandCount;
    std::cin >> commandCount;
    
    bool matched = true;
    
    for (int i = 0; i < commandCount; ++i) {
        int commandNumber, commandValue;
        std::cin >> commandNumber >> commandValue;
        matched = commandTreatment(commandNumber, commandValue, q);
        
    }
    
    std::cout << (matched ? "YES" : "NO");
    
    return 0;
}

bool commandTreatment(int commandNumber, int value, Queue& q) {
    
    if (commandNumber == 2) {
        return q.dequeue() == value;
    }
    if (commandNumber == 3) {
        q.enqueue(value);
    }
    return true;
    
}


