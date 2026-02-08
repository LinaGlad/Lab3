#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include <string>
#include <vector>

class DoubleLinkedList {
private:
  struct DoubleNode {
    std::string key;
    DoubleNode *next;
    DoubleNode *prev;
  };

  struct DoubleList {
    DoubleNode *head;
    DoubleNode *tail;
  };

  DoubleList *list;

public:
  DoubleLinkedList() {
    list = new DoubleList;
    list->head = nullptr;
    list->tail = nullptr;
  }

  ~DoubleLinkedList() {
    Clear();
    delete list;
  }

  void Clear() {
    while (list->head != nullptr) {
      DoubleNode *temp = list->head;
      list->head = list->head->next;
      delete temp;
    }
    list->tail = nullptr;
  }

  void AddAfter(DoubleNode *ptr, const std::string &value) {
    DoubleNode *newNode = new DoubleNode;
    newNode->key = value;
    newNode->next = ptr->next;
    newNode->prev = ptr;

    if (ptr->next != nullptr) {
      ptr->next->prev = newNode;
    }
    ptr->next = newNode;
  }

  void AddBefore(DoubleNode *ptr, const std::string &value) {
    DoubleNode *newNode = new DoubleNode;
    newNode->key = value;
    newNode->prev = ptr->prev;
    newNode->next = ptr;

    if (ptr->prev != nullptr) {
      ptr->prev->next = newNode;
    }
    ptr->prev = newNode;
  }

  void AddHead(const std::string &value) {
    DoubleNode *newNode = new DoubleNode;
    newNode->key = value;
    newNode->next = list->head;
    newNode->prev = nullptr;

    if (list->head != nullptr) {
      list->head->prev = newNode;
    } else {
      list->tail = newNode;
    }
    list->head = newNode;
  }

  void AddTail(const std::string &value) {
    DoubleNode *newNode = new DoubleNode;
    newNode->key = value;
    newNode->next = nullptr;
    newNode->prev = list->tail;

    if (list->tail != nullptr) {
      list->tail->next = newNode;
    } else {
      list->head = newNode;
    }
    list->tail = newNode;
  }

  std::string DeleteNode(DoubleNode *ptr) {
    if (ptr == nullptr)
      return "";

    std::string deletedValue = ptr->key;

    if (ptr == list->head) {
      list->head = ptr->next;
    }
    if (ptr == list->tail) {
      list->tail = ptr->prev;
    }

    if (ptr->prev != nullptr) {
      ptr->prev->next = ptr->next;
    }
    if (ptr->next != nullptr) {
      ptr->next->prev = ptr->prev;
    }

    delete ptr;
    return deletedValue;
  }

  std::string DeleteHead() {
    if (list->head == nullptr)
      return "";

    DoubleNode *deleteNode = list->head;
    std::string deletedValue = deleteNode->key;

    list->head = list->head->next;

    if (list->head != nullptr) {
      list->head->prev = nullptr;
    } else {
      list->tail = nullptr;
    }

    delete deleteNode;
    return deletedValue;
  }

  std::string DeleteTail() {
    if (list->tail == nullptr)
      return "";

    DoubleNode *deleteNode = list->tail;
    std::string deletedValue = deleteNode->key;

    list->tail = list->tail->prev;

    if (list->tail != nullptr) {
      list->tail->next = nullptr;
    } else {
      list->head = nullptr;
    }

    delete deleteNode;
    return deletedValue;
  }

  void DisplayForward(DoubleNode *node) {
    if (node == nullptr)
      return;
    std::cout << node->key << " ";
    DisplayForward(node->next);
  }

  void DisplayBackward(DoubleNode *node) {
    if (node == nullptr)
      return;
    std::cout << node->key << " ";
    DisplayBackward(node->prev);
  }

  DoubleNode *FindByValue(const std::string &value, int *position = nullptr) {
    DoubleNode *current = list->head;
    int pos = 0;

    while (current != nullptr) {
      if (current->key == value) {
        if (position != nullptr) {
          *position = pos;
        }
        return current;
      }
      current = current->next;
      pos++;
    }

    if (position != nullptr) {
      *position = -1;
    }
    return nullptr;
  }

  void AddElementBefore(const std::string &value, const std::string &element) {
    DoubleNode *ptr = FindByValue(element);
    if (ptr != nullptr) {
      if (ptr == list->head) {
        AddHead(value);
      } else {
        AddBefore(ptr, value);
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
    }
  }

  void AddElementAfter(const std::string &value, const std::string &element) {
    DoubleNode *ptr = FindByValue(element);
    if (ptr != nullptr) {
      if (ptr == list->tail) {
        AddTail(value);
      } else {
        AddAfter(ptr, value);
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
    }
  }

  std::string DeleteElementBefore(const std::string &element) {
    DoubleNode *ptr = FindByValue(element);
    if (ptr != nullptr) {
      if (ptr->prev == list->head) {
        return DeleteHead();
      } else if (ptr != nullptr && ptr->prev != nullptr) {
        return DeleteNode(ptr->prev);
      } else if (ptr != nullptr && ptr->prev == nullptr) {
        std::cout << "No values before the first element" << std::endl;
        return "";
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
      return "";
    }
    return "";
  }

  std::string DeleteElementAfter(const std::string &element) {
    DoubleNode *ptr = FindByValue(element);
    if (ptr != nullptr) {
      if (ptr->next == list->tail) {
        return DeleteTail();
      } else if (ptr != nullptr && ptr->next != nullptr) {
        return DeleteNode(ptr->next);
      } else if (ptr != nullptr && ptr->next == nullptr) {
        std::cout << "No element after " << element << " to delete."
                  << std::endl;
        return "";
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
      return "";
    }
    return "";
  }

  std::string DeleteElementAtHead() {
    if (list->head == nullptr) {
      std::cout << "List is empty!" << std::endl;
      return "";
    }
    return DeleteHead();
  }

  std::string DeleteElementAtTail() {
    if (list->tail == nullptr) {
      std::cout << "List is empty!" << std::endl;
      return "";
    }
    return DeleteTail();
  }

  std::string DeleteElementByValue(const std::string &element) {
    DoubleNode *ptr = FindByValue(element);
    if (ptr != nullptr) {
      if (ptr == list->head) {
        return DeleteHead();
      } else if (ptr == list->tail) {
        return DeleteTail();
      } else {
        return DeleteNode(ptr);
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
      return "";
    }
  }

  void DisplayList() {
    std::cout << "List forward: ";
    DisplayForward(list->head);
    std::cout << std::endl;

    std::cout << "List backward: ";
    DisplayBackward(list->tail);
    std::cout << std::endl;
  }

  bool SearchElement(const std::string &value) {
    int position = 0;
    DoubleNode *found = FindByValue(value, &position);
    return (found != nullptr);
  }

  std::vector<std::string> getAllElements() const {
    std::vector<std::string> elements;
    DoubleNode *current = list->head;
    while (current != nullptr) {
      elements.push_back(current->key);
      current = current->next;
    }
    return elements;
  }

  DoubleNode *getHead() const { return list->head; }
  DoubleNode *getTail() const { return list->tail; }

  int GetSize() const {
    int count = 0;
    DoubleNode *current = list->head;
    while (current != nullptr) {
      count++;
      current = current->next;
    }
    return count;
  }

  void serializeBinary(std::ostream &out) const {
    int count = GetSize();
    out.write(reinterpret_cast<const char *>(&count), sizeof(count));

    DoubleNode *current = list->head;
    while (current != nullptr) {
      size_t len = current->key.size();
      out.write(reinterpret_cast<const char *>(&len), sizeof(len));
      out.write(current->key.c_str(), len);
      current = current->next;
    }
  }

  void deserializeBinary(std::istream &in) {
    Clear();
    int count = 0;
    if (!in.read(reinterpret_cast<char *>(&count), sizeof(count)))
      return;

    for (int i = 0; i < count; ++i) {
      size_t len;
      in.read(reinterpret_cast<char *>(&len), sizeof(len));
      std::string value(len, '\0');
      in.read(&value[0], len);
      AddTail(value); 
    }
  }

  void serializeText(std::ostream &out) const {
    int count = GetSize();
    out << count << "\n";
    DoubleNode *current = list->head;
    while (current != nullptr) {
      out << current->key << "\n";
      current = current->next;
    }
  }

  void deserializeText(std::istream &in) {
    Clear();
    int count = 0;
    if (!(in >> count))
      return;
    in.ignore(); 

    for (int i = 0; i < count; ++i) {
      std::string line;
      if (std::getline(in, line)) {
        AddTail(line);
      }
    }
  }
};

#endif
