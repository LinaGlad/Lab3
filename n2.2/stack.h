#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>

class Stack {
private:
  std::string *arr;
  int top;
  int length;

public:
  Stack(int length) {
    this->length = length;
    this->arr = new std::string[length];
    this->top = 0;
  }

  ~Stack() { delete[] arr; }

  std::string StackPush(const std::string &x) {
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
    } else {
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
  std::string *getArray() { return arr; }
  const std::string *getArray() const { return arr; }

  void serializeBinary(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(&length), sizeof(length));
    out.write(reinterpret_cast<const char *>(&top), sizeof(top));

    for (int i = 0; i < top; ++i) {
      size_t len = arr[i].size();
      out.write(reinterpret_cast<const char *>(&len), sizeof(len));
      out.write(arr[i].c_str(), len);
    }
  }

  void deserializeBinary(std::istream &in) {
    int newLength, newTop;
    if (!in.read(reinterpret_cast<char *>(&newLength), sizeof(newLength)))
      return;
    in.read(reinterpret_cast<char *>(&newTop), sizeof(newTop));

    if (newLength != length) {
      delete[] arr;
      length = newLength;
      arr = new std::string[length];
    }
    top = newTop;

    for (int i = 0; i < top; ++i) {
      size_t len;
      in.read(reinterpret_cast<char *>(&len), sizeof(len));
      std::string value(len, '\0');
      in.read(&value[0], len);
      arr[i] = value;
    }
  }

  void serializeText(std::ostream &out) const {
    out << length << " " << top << "\n";
    for (int i = 0; i < top; ++i) {
      out << arr[i] << "\n";
    }
  }

  void deserializeText(std::istream &in) {
    int newLength, newTop;
    if (!(in >> newLength >> newTop))
      return;
    in.ignore(); 

    if (newLength != length) {
      delete[] arr;
      length = newLength;
      arr = new std::string[length];
    }
    top = newTop;

    for (int i = 0; i < top; ++i) {
      std::getline(in, arr[i]);
    }
  }
};

#endif
