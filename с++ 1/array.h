#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <iostream>

class Array {
private:
    std::string* arr;
    int length;    
    int size;      

public:
    Array(int length) {
        this->length = length;
        this->size = 0;
        this->arr = new std::string[length];
    }

    ~Array() {
        delete[] arr;
    }

    void addByIndex(int index, const std::string& value) {
        if (index < 0 || index > size) {
            std::cout << "Invalid index!" << std::endl;
        }
        else if (size >= length) {
            std::cout << "Array is full!" << std::endl;
        }
        else {
            for (int i = size; i > index; i--) {
                arr[i] = arr[i - 1];
            }
            arr[index] = value;
            size++;
        }
    }

    void addToEnd(const std::string& value) {
        if (size >= length) {
            std::cout << "Array is full!" << std::endl;
        }
        else {
            arr[size] = value;
            size++;
        }
    }

    void getByIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!" << std::endl;
        }
        else {
            std::cout << arr[index] << std::endl;
        }
    }

    std::string deleteByIndex(int index) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!" << std::endl;
            return "";
        }
        else {
            std::string deletedValue = arr[index];
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
            return deletedValue;
        }
    }

    void replaceByIndex(int index, const std::string& value) {
        if (index < 0 || index >= size) {
            std::cout << "Invalid index!" << std::endl;
        }
        else {
            arr[index] = value;
        }
    }

    void getLength() {
        std::cout << "Size: " << size << std::endl;
    }

    void displayAll() {
        for (int i = 0; i < size; i++) {
            std::cout << i << ": " << arr[i] << std::endl;
        }
    }

    int getLengthValue() const { return length; }
    int getSizeValue() const { return size; }
    std::string getElementAt(int index) const { 
        return (index >= 0 && index < size) ? arr[index] : ""; 
    }
    void setElementAt(int index, const std::string& value) {
        if (index >= 0 && index < length) arr[index] = value;
    }
    void setSize(int newSize) { 
        if (newSize >= 0 && newSize <= length) size = newSize; 
    }
};

#endif
