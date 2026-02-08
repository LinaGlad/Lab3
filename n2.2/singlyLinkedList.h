#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <string>

class SinglyLinkedList {
private:
  struct SinglyNode {
    std::string key;
    SinglyNode *next;
  };

  struct ForwardList {
    SinglyNode *head;
  };

  ForwardList *list;

public:
  SinglyLinkedList() {
    list = new ForwardList;
    list->head = nullptr;
  }

  ~SinglyLinkedList() {
    Clear();
    delete list;
  }

  void Clear() {
    while (list->head != nullptr) {
      SinglyNode *temp = list->head;
      list->head = list->head->next;
      delete temp;
    }
  }

  void AddAfter(SinglyNode *ptr, const std::string &value) {
    SinglyNode *newNode = new SinglyNode;
    newNode->key = value;
    newNode->next = ptr->next;
    ptr->next = newNode;
  }

  void AddHead(const std::string &value) {
    SinglyNode *newNode = new SinglyNode{value, list->head};
    list->head = newNode;
  }

  void AddTail(SinglyNode *ptr, const std::string &value) {
    SinglyNode *newNode = new SinglyNode;
    newNode->key = value;
    newNode->next = nullptr;
    ptr->next = newNode;
  }

  std::string DeleteAfter(SinglyNode *ptr) {
    if (ptr == nullptr || ptr->next == nullptr)
      return "";
    SinglyNode *deleteNode = ptr->next;
    std::string deletedValue = deleteNode->key;
    ptr->next = deleteNode->next;
    delete deleteNode;
    return deletedValue;
  }

  std::string DeleteHead() {
    if (list->head == nullptr)
      return "";
    SinglyNode *deleteNode = list->head;
    std::string deletedValue = deleteNode->key;
    list->head = list->head->next;
    delete deleteNode;
    return deletedValue;
  }

  void DisplayRecursive(SinglyNode *node) {
    if (node == nullptr)
      return;
    std::cout << node->key << " ";
    DisplayRecursive(node->next);
  }

  SinglyNode *FindByValue(const std::string &value, int *position) {
    SinglyNode *current = list->head;
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
    int position = 0;
    SinglyNode *ptr = FindByValue(element, &position);
    if (ptr != nullptr) {
      if (position == 0) {
        AddHead(value);
      } else {
        SinglyNode *current = list->head;
        for (int i = 1; i < position; i++) {
          current = current->next;
        }
        AddAfter(current, value);
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
    }
  }

  void AddElementAfter(const std::string &value, const std::string &element) {
    SinglyNode *ptr = FindByValue(element, nullptr);
    if (ptr != nullptr) {
      AddAfter(ptr, value);
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
    }
  }

  void AddElementAtTail(const std::string &value) {
    if (list->head == nullptr) {
      AddHead(value);
      return;
    }

    SinglyNode *current = list->head;
    while (current->next != nullptr) {
      current = current->next;
    }
    AddTail(current, value);
  }

  std::string DeleteElementBefore(const std::string &element) {
    int position = 0;
    SinglyNode *ptr = FindByValue(element, &position);
    if (ptr != nullptr) {
      if (position == 0) {
        std::cout << "No values before the first element" << std::endl;
        return "";
      } else if (position == 1) {
        return DeleteHead();
      } else {
        SinglyNode *current = list->head;
        for (int i = 1; i < position - 1; i++) {
          current = current->next;
        }
        return DeleteAfter(current);
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
      return "";
    }
  }

  std::string DeleteElementAfter(const std::string &element) {
    SinglyNode *ptr = FindByValue(element, nullptr);
    if (ptr != nullptr) {
      if (ptr->next != nullptr) {
        return DeleteAfter(ptr);
      } else {
        std::cout << "No element after " << element << " to delete."
                  << std::endl;
        return "";
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
      return "";
    }
  }

  std::string DeleteElementAtHead() {
    if (list->head == nullptr) {
      std::cout << "List is empty!" << std::endl;
      return "";
    }
    return DeleteHead();
  }

  std::string DeleteElementAtTail() {
    if (list->head == nullptr) {
      std::cout << "List is empty!" << std::endl;
      return "";
    }

    if (list->head->next == nullptr) {
      return DeleteHead();
    }

    SinglyNode *current = list->head;
    while (current->next->next != nullptr) {
      current = current->next;
    }
    return DeleteAfter(current);
  }

  std::string DeleteElementByValue(const std::string &element) {
    int position = 0;
    SinglyNode *ptr = FindByValue(element, &position);
    if (ptr != nullptr) {
      if (position == 0) {
        return DeleteHead();
      } else {
        SinglyNode *current = list->head;
        for (int i = 1; i < position; i++) {
          current = current->next;
        }
        return DeleteAfter(current);
      }
    } else {
      std::cout << "Element " << element << " not found in the list."
                << std::endl;
      return "";
    }
  }

  void DisplayList() {
    std::cout << "List (iterative): ";
    SinglyNode *current = list->head;
    while (current != nullptr) {
      std::cout << current->key << " ";
      current = current->next;
    }
    std::cout << std::endl;

    std::cout << "List (recursive): ";
    DisplayRecursive(list->head);
    std::cout << std::endl;
  }

  bool SearchElement(const std::string &value) {
    int position = 0;
    SinglyNode *found = FindByValue(value, &position);
    return (found != nullptr);
  }

  SinglyNode *getHead() const { return list->head; }

  int GetSize() const {
    int count = 0;
    SinglyNode *current = list->head;
    while (current != nullptr) {
      count++;
      current = current->next;
    }
    return count;
  }

  void serializeBinary(std::ostream &out) const {
    int count = GetSize();

    out.write(reinterpret_cast<const char *>(&count), sizeof(count));

    SinglyNode *current = list->head;
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
    in.read(reinterpret_cast<char *>(&count), sizeof(count));

    for (int i = 0; i < count; ++i) {
      size_t len = 0;
      in.read(reinterpret_cast<char *>(&len), sizeof(len));

      std::string value(len, '\0');
      in.read(&value[0], len);

      AddElementAtTail(value);
    }
  }

  void serializeText(std::ostream &out) const {
    int count = GetSize();
    out << count << "\n";

    SinglyNode *current = list->head;
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
      std::string value;
      std::getline(in, value);
      AddElementAtTail(value);
    }
  }
};

#endif
