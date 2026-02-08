#ifndef STACK_H
#define STACK_H

#include <string>
#include <iostream>

class Stack {
private:
    std::string* arr;
    int top;
    int length;

public:
    Stack(int length) {
        this->length = length;
        this->arr = new std::string[length];
        this->top = 0;
    }

    ~Stack() {
        delete[] arr;
    }

    std::string StackPush(const std::string& x) {
        if (top >= length) {
            std::cout << "Stack overflow!" << std::endl;
            return "";
        }
        arr[top] = x;
        top = top + 1;
        return x;  
    }

    std::string StackPop() {
        if (top == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return "";
        }
        else {
            top = top - 1;
            return arr[top];  
        }
    }

    void StackDisplay() {
        if (top == 0) {
            std::cout << "Stack is empty!" << std::endl;
            return;
        }

        std::cout << "Stack elements (from top to bottom): ";
        for (int i = top - 1; i >= 0; i--) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

    void setTop(int t) { top = t; }
    
    int getTop() const { return top; }
    int getLength() const { return length; }
    std::string* getArray() { return arr; }
    const std::string* getArray() const { return arr; }
};

#endif
