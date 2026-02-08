#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

class Queue {
private:
  std::string *arr;
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

  ~Queue() { delete[] arr; }

  std::string QueuePush(const std::string &x) {
    if ((tail % length + 1) == head) {
      std::cout << "Queue overflow!" << std::endl;
      return "";
    }
    arr[tail] = x;
    if (tail == length) {
      tail = 1;
    } else {
      tail = tail + 1;
    }
    return x;
  }

  std::string QueuePop() {
    if (head == tail) {
      std::cout << "Queue is empty!" << std::endl;
      return "";
    } else {
      std::string value = arr[head];
      if (head == length) {
        head = 1;
      } else {
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
    } else {
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
  std::string *getArray() { return arr; }
  const std::string *getArray() const { return arr; }

  void serializeBinary(std::ostream &out) const {
    out.write(reinterpret_cast<const char *>(&length), sizeof(length));
    out.write(reinterpret_cast<const char *>(&head), sizeof(head));
    out.write(reinterpret_cast<const char *>(&tail), sizeof(tail));

    for (int i = 1; i <= length; ++i) {
      size_t len = arr[i].size();
      out.write(reinterpret_cast<const char *>(&len), sizeof(len));
      out.write(arr[i].c_str(), len);
    }
  }

  void deserializeBinary(std::istream &in) {
    int newLength, newHead, newTail;
    if (!in.read(reinterpret_cast<char *>(&newLength), sizeof(newLength)))
      return;
    in.read(reinterpret_cast<char *>(&newHead), sizeof(newHead));
    in.read(reinterpret_cast<char *>(&newTail), sizeof(newTail));

    if (newLength != length) {
      delete[] arr;
      length = newLength;
      arr = new std::string[length + 1];
    }
    head = newHead;
    tail = newTail;

    for (int i = 1; i <= length; ++i) {
      size_t len;
      in.read(reinterpret_cast<char *>(&len), sizeof(len));
      std::string value(len, '\0');
      in.read(&value[0], len);
      arr[i] = value;
    }
  }

  void serializeText(std::ostream &out) const {
    out << length << " " << head << " " << tail << "\n";
    for (int i = 1; i <= length; ++i) {
      out << arr[i] << "\n";
    }
  }

  void deserializeText(std::istream &in) {
    int newLength, newHead, newTail;
    if (!(in >> newLength >> newHead >> newTail))
      return;
    in.ignore();

    if (newLength != length) {
      delete[] arr;
      length = newLength;
      arr = new std::string[length + 1];
    }
    head = newHead;
    tail = newTail;

    for (int i = 1; i <= length; ++i) {
      std::getline(in, arr[i]);
    }
  }
};

#endif
