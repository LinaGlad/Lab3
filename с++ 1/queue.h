#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <iostream>

class Queue {
private:
    std::string* arr;
    int head;
    int tail;
    int length;

public:
    Queue(int length) {
        this->length = length;
        this->arr = new std::string[length + 1];
        this->head = 1;
        this->tail = 1;
    }

    ~Queue() {
        delete[] arr;
    }

    std::string QueuePush(const std::string& x) {
        if ((tail % length + 1) == head) {
            std::cout << "Queue overflow!" << std::endl;
            return "";
        }
        arr[tail] = x;
        if (tail == length) {
            tail = 1;
        }
        else {
            tail = tail + 1;
        }
        return x;  
    }

    std::string QueuePop() {
        if (head == tail) {
            std::cout << "Queue is empty!" << std::endl;
            return "";
        }
        else {
            std::string value = arr[head];  
            if (head == length) {
                head = 1;  
            }
            else {
                head = head + 1;
            }
            return value;  
        }
    }

    void QueueDisplay() {
        if (head == tail) {
            std::cout << "Queue is empty!" << std::endl;
            return;
        }

        std::cout << "Queue elements: ";
        if (head < tail) {
            for (int i = head; i < tail; i++) {
                std::cout << arr[i] << " ";
            }
        }
        else {
            for (int i = head; i <= length; i++) {
                std::cout << arr[i] << " ";
            }
            for (int i = 1; i < tail; i++) {
                std::cout << arr[i] << " ";
            }
        }
        std::cout << std::endl;
    }

    void setHead(int h) { head = h; }
    void setTail(int t) { tail = t; }
    
    int getHead() const { return head; }
    int getTail() const { return tail; }
    int getLength() const { return length; }
    std::string* getArray() { return arr; }
    const std::string* getArray() const { return arr; }
};

#endif
