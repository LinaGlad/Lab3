#ifndef ARRAY_H
#define ARRAY_H

#include <fstream>
#include <iostream>
#include <string>

class Array {
private:
  std::string *arr;
  int length;
  int size;

public:
  Array(int length) {
    this->length = length;
    this->size = 0;
    this->arr = new std::string[length];
  }

  ~Array() { delete[] arr; }

  void addByIndex(int index, const std::string &value) {
    if (index < 0 || index > size) {
      std::cout << "Invalid index!" << std::endl;
    } else if (size >= length) {
      std::cout << "Array is full!" << std::endl;
    } else {
      for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
      }
      arr[index] = value;
      size++;
    }
  }

  void addToEnd(const std::string &value) {
    if (size >= length) {
      std::cout << "Array is full!" << std::endl;
    } else {
      arr[size] = value;
      size++;
    }
  }

  void getByIndex(int index) {
    if (index < 0 || index >= size) {
      std::cout << "Invalid index!" << std::endl;
    } else {
      std::cout << arr[index] << std::endl;
    }
  }

  std::string deleteByIndex(int index) {
    if (index < 0 || index >= size) {
      std::cout << "Invalid index!" << std::endl;
      return "";
    } else {
      std::string deletedValue = arr[index];
      for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
      }
      size--;
      return deletedValue;
    }
  }

  void replaceByIndex(int index, const std::string &value) {
    if (index < 0 || index >= size) {
      std::cout << "Invalid index!" << std::endl;
    } else {
      arr[index] = value;
    }
  }

  void getLength() { std::cout << "Size: " << size << std::endl; }

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
  void setElementAt(int index, const std::string &value) {
    if (index >= 0 && index < length)
      arr[index] = value;
  }
  void setSize(int newSize) {
    if (newSize >= 0 && newSize <= length)
      size = newSize;
  }

  void serializeBinary(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(&length), sizeof(length));
    out.write(reinterpret_cast<const char *>(&size), sizeof(size));
    for (int i = 0; i < size; ++i) {
      size_t len = arr[i].size();
      out.write(reinterpret_cast<const char *>(&len), sizeof(len));
      out.write(arr[i].c_str(), len);
    }
  }

  void deserializeBinary(std::istream &in) {
    int newLength, newSize;
    in.read(reinterpret_cast<char *>(&newLength), sizeof(newLength));
    in.read(reinterpret_cast<char *>(&newSize), sizeof(newSize));

    if (newLength != length) {
      delete[] arr;
      length = newLength;
      arr = new std::string[length];
    }
    size = newSize;

    for (int i = 0; i < size; ++i) {
      size_t len;
      in.read(reinterpret_cast<char *>(&len), sizeof(len));
      std::string value(len, '\0');
      in.read(&value[0], len);
      arr[i] = value;
    }
  }

  void serializeText(std::ostream &out) const {
    out << length << " " << size << "\n";
    for (int i = 0; i < size; ++i) {
      out << arr[i] << "\n";
    }
  }

  void deserializeText(std::istream &in) {
    int newLength, newSize;
    in >> newLength >> newSize;
    in.ignore(); 

    if (newLength != length) {
      delete[] arr;
      length = newLength;
      arr = new std::string[length];
    }
    size = newSize;

    for (int i = 0; i < size; ++i) {
      std::getline(in, arr[i]);
    }
  }
};

#endif
