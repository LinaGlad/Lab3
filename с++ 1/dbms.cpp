#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "array.h"
#include "stack.h"
#include "queue.h"
#include "singlyLinkedList.h"
#include "doubleLinkedList.h"
#include "tree.h"
#include "HashTable.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

// Глобальное хранилище массивов
map<string, Array*> arrays;
map<string, SinglyLinkedList*> singlyLists;
map<string, DoubleLinkedList*> doubleLists;
map<string, Stack*> stacks;
map<string, Queue*> queues;
map<string, Tree*> trees;
map<string, HashTable*> hashtables;

// Функции для работы с JSON (ОБНОВЛЕННЫЕ)
json serializeArray(const Array* arr) {
    json j;
    j["length"] = arr->getLengthValue();
    j["size"] = arr->getSizeValue();
    j["elements"] = json::array();
    for (int i = 0; i < arr->getSizeValue(); i++) {
        j["elements"].push_back(arr->getElementAt(i));
    }
    return j;
}

Array* deserializeArray(const json& j) {
    Array* arr = new Array(j["length"]);
    arr->setSize(j["size"]);
    for (int i = 0; i < arr->getSizeValue(); i++) {
        arr->setElementAt(i, j["elements"][i]);
    }
    return arr;
}

// Функции для работы с JSON (ОБНОВЛЕННЫЕ)
json serializeSinglyList(const SinglyLinkedList* list) {
    json j;
    j["elements"] = json::array();
    
    // Нужно добавить метод getHead() в класс
    auto current = list->getHead(); 
    while (current != nullptr) {
        j["elements"].push_back(current->key);
        current = current->next;
    }
    return j;
}

SinglyLinkedList* deserializeSinglyList(const json& j) {
    SinglyLinkedList* list = new SinglyLinkedList();
    
    if (j["elements"].is_array() && !j["elements"].empty()) {
        for (const auto& element : j["elements"]) {
            list->AddElementAtTail(element);
        }
    }
    return list;
}

// Функции для работы с JSON (ОБНОВЛЕННЫЕ)
json serializeDoubleList(const DoubleLinkedList* list) {
    json j;
    j["elements"] = list->getAllElements();
    return j;
}

DoubleLinkedList* deserializeDoubleList(const json& j) {
    DoubleLinkedList* list = new DoubleLinkedList();
    if (j.contains("elements") && j["elements"].is_array()) {
        for (const auto& element : j["elements"]) {
            list->AddTail(element);
        }
    }
    return list;
}

// Функции для работы с JSON для стека
json serializeStack(const Stack* stack) {
    json j;
    j["length"] = stack->getLength();
    j["top"] = stack->getTop();
    j["elements"] = json::array();
    
    // Сохраняем все элементы массива
    const std::string* arr = stack->getArray();
    for (int i = 0; i < stack->getLength(); i++) {
        j["elements"].push_back(arr[i]);
    }
    return j;
}

Stack* deserializeStack(const json& j) {
    Stack* stack = new Stack(j["length"]);
    stack->setTop(j["top"]);
    
    // Восстанавливаем элементы массива
    std::string* arr = stack->getArray();
    for (int i = 0; i < stack->getLength(); i++) {
        arr[i] = j["elements"][i];
    }
    return stack;
}

// Функции для работы с JSON для очереди
json serializeQueue(const Queue* queue) {
    json j;
    j["length"] = queue->getLength();
    j["head"] = queue->getHead();
    j["tail"] = queue->getTail();
    j["elements"] = json::array();
    
    // Сохраняем все элементы массива
    const std::string* arr = queue->getArray();
    for (int i = 0; i <= queue->getLength(); i++) {
        j["elements"].push_back(arr[i]);
    }
    return j;
}

Queue* deserializeQueue(const json& j) {
    Queue* queue = new Queue(j["length"]);
    queue->setHead(j["head"]);
    queue->setTail(j["tail"]);
    
    // Восстанавливаем элементы массива
    std::string* arr = queue->getArray();
    for (int i = 0; i <= queue->getLength(); i++) {
        arr[i] = j["elements"][i];
    }
    return queue;
}

// Функции для работы с JSON для дерева
json serializeTree(const Tree* tree) {
    if (tree == nullptr) {
        return nullptr;
    }
    
    // Используем существующий метод serializeRecursive
    std::vector<int> elements;
    tree->serializeRecursive(tree->getRoot(), elements);
    
    json j;
    j["elements"] = elements;
    return j;
}

Tree* deserializeTree(const json& j) {
    Tree* tree = new Tree();
    if (!j.is_null() && j.contains("elements") && j["elements"].is_array()) {
        std::vector<int> elements = j["elements"];
        // Просто вставляем элементы в том порядке, в котором они сохранены
        for (int elem : elements) {
            tree->insert(elem);  // Используем обычную вставку BST
        }
    }
    return tree;
}

// Функции для работы с JSON для хэш-таблиц
json serializeHashTable(const HashTable* ht) {
    json j;
    j["capacity"] = ht->get_capacity();
    j["size"] = ht->get_size();
    j["elements"] = json::array();
    
    auto elements = ht->get_all_elements();
    for (const auto& elem : elements) {
        json element;
        element["key"] = elem.first;
        element["value"] = elem.second;
        j["elements"].push_back(element);
    }
    return j;
}

HashTable* deserializeHashTable(const json& j) {
    size_t capacity = j["capacity"];
    HashTable* ht = new HashTable(capacity);
    
    if (j.contains("elements") && j["elements"].is_array()) {
        for (const auto& element : j["elements"]) {
            ht->insert(element["key"], element["value"]);
        }
    }
    return ht;
}

void saveToFile(const string& filename) {
    json data;
    
    // Сохраняем массивы
    json arraysJson;
    for (const auto& pair : arrays) {
        arraysJson[pair.first] = serializeArray(pair.second);
    }
    data["arrays"] = arraysJson;
    
    // Сохраняем односвязные списки
    json singlyListsJson;
    for (const auto& pair : singlyLists) {
        singlyListsJson[pair.first] = serializeSinglyList(pair.second);
    }
    data["singly_lists"] = singlyListsJson;
    
    // Сохраняем двусвязные списки
    json doubleListsJson;
    for (const auto& pair : doubleLists) {
        doubleListsJson[pair.first] = serializeDoubleList(pair.second);
    }
    data["double_lists"] = doubleListsJson;
    
    // Сохраняем стеки
    json stacksJson;
    for (const auto& pair : stacks) {
        stacksJson[pair.first] = serializeStack(pair.second);
    }
    data["stacks"] = stacksJson;
    
    // Сохраняем очереди
    json queuesJson;
    for (const auto& pair : queues) {
        queuesJson[pair.first] = serializeQueue(pair.second);
    }
    data["queues"] = queuesJson;
    
        // Сохраняем деревья
    json treesJson;
    for (const auto& pair : trees) {
        treesJson[pair.first] = serializeTree(pair.second);
    }
    data["trees"] = treesJson;
    
    json hashtablesJson;
for (const auto& pair : hashtables) {
    hashtablesJson[pair.first] = serializeHashTable(pair.second);
}
data["hashtables"] = hashtablesJson;

    ofstream file(filename);
    if (file.is_open()) {
        file << data.dump(4);
        file.close();
    }
}

void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    
    json data;
    try {
        file >> data;
        file.close();
    } catch (const exception& e) {
        cerr << "Error reading file: " << e.what() << endl;
        return;
    }
    
    // Очищаем текущие данные
    for (auto& pair : arrays) {
    delete pair.second;  // деструктор сам удалит массив
    }
    arrays.clear();
    
    for (auto& pair : singlyLists) {
    delete pair.second;  // деструктор сам очистит список
    }
    singlyLists.clear();
    
    for (auto& pair : doubleLists) {
    delete pair.second;  // деструктор сам очистит список
    }
    doubleLists.clear();
    
    for (auto& pair : stacks) {
    delete pair.second;  // деструктор сам удалит массив
    }
    stacks.clear();
    
    for (auto& pair : queues) {
    delete pair.second;  // деструктор сам удалит массив
    }
    queues.clear();
    
    for (auto& pair : trees) {
    delete pair.second;  // деструктор сам очистит дерево
    }
    
    // Очищаем хэш-таблицы
for (auto& pair : hashtables) {
    delete pair.second;
}
hashtables.clear();

    // Загружаем данные
    if (data.contains("arrays")) {
        for (auto& element : data["arrays"].items()) {
            arrays[element.key()] = deserializeArray(element.value());
        }
    }
    
    if (data.contains("singly_lists")) {
        for (auto& element : data["singly_lists"].items()) {
            singlyLists[element.key()] = deserializeSinglyList(element.value());
        }
    }
    
    if (data.contains("double_lists")) {
        for (auto& element : data["double_lists"].items()) {
            doubleLists[element.key()] = deserializeDoubleList(element.value());
        }
    }
    
    if (data.contains("stacks")) {
        for (auto& element : data["stacks"].items()) {
            stacks[element.key()] = deserializeStack(element.value());
        }
    }
    
    if (data.contains("queues")) {
        for (auto& element : data["queues"].items()) {
            queues[element.key()] = deserializeQueue(element.value());
        }
    }
    
    if (data.contains("trees")) {
        for (auto& element : data["trees"].items()) {
            if (!element.value().is_null()) {  // Проверяем что дерево не null
                trees[element.key()] = deserializeTree(element.value());
            } else {
                trees[element.key()] = nullptr;  // Сохраняем пустое дерево
            }
        }
    }
    
    // Загружаем хэш-таблицы
if (data.contains("hashtables")) {
    for (auto& element : data["hashtables"].items()) {
        hashtables[element.key()] = deserializeHashTable(element.value());
    }
}

}

void saveToBinaryFile(const string& filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) {
        cerr << "Error: Cannot open binary file for writing" << endl;
        return;
    }
    
    // Сохраняем количество структур каждого типа
    size_t count;
    
    // 1. Массивы
    count = arrays.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : arrays) {
        // Сохраняем имя
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем данные массива
        int length = pair.second->getLengthValue();
        int size = pair.second->getSizeValue();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        
        for (int i = 0; i < size; i++) {
            string value = pair.second->getElementAt(i);
            size_t val_len = value.size();
            file.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));
            file.write(value.c_str(), val_len);
        }
    }
    
    // 2. Хэш-таблицы
    count = hashtables.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : hashtables) {
        // Сохраняем имя
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем данные хэш-таблицы
        size_t capacity = pair.second->get_capacity();
        size_t size = pair.second->get_size();
        file.write(reinterpret_cast<const char*>(&capacity), sizeof(capacity));
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        
        auto elements = pair.second->get_all_elements();
        for (const auto& elem : elements) {
            // Ключ
            size_t key_len = elem.first.size();
            file.write(reinterpret_cast<const char*>(&key_len), sizeof(key_len));
            file.write(elem.first.c_str(), key_len);
            
            // Значение
            int value = elem.second;
            file.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }
    
    // 3. Стеки
    count = stacks.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : stacks) {
        // Сохраняем имя
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем данные стека
        int length = pair.second->getLength();
        int top = pair.second->getTop();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(reinterpret_cast<const char*>(&top), sizeof(top));
        
        const string* arr = pair.second->getArray();
        for (int i = 0; i < length; i++) {
            size_t val_len = arr[i].size();
            file.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));
            file.write(arr[i].c_str(), val_len);
        }
        }
    
    // 4. Очереди
    count = queues.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : queues) {
        // Сохраняем имя
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем данные очереди
        int length = pair.second->getLength();
        int head = pair.second->getHead();
        int tail = pair.second->getTail();
        file.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file.write(reinterpret_cast<const char*>(&head), sizeof(head));
        file.write(reinterpret_cast<const char*>(&tail), sizeof(tail));
        
        const string* arr = pair.second->getArray();
        for (int i = 0; i <= length; i++) {
            size_t val_len = arr[i].size();
            file.write(reinterpret_cast<const char*>(&val_len), sizeof(val_len));
            file.write(arr[i].c_str(), val_len);
        }
        }
    
    // 5. Односвязные списки
    count = singlyLists.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : singlyLists) {
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем элементы списка
        auto current = pair.second->getHead();
        vector<string> elements;
        while (current != nullptr) {
            elements.push_back(current->key);
            current = current->next;
        }
        
        size_t size = elements.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& elem : elements) {
            size_t elem_len = elem.size();
            file.write(reinterpret_cast<const char*>(&elem_len), sizeof(elem_len));
            file.write(elem.c_str(), elem_len);
        }
        }
    
    // 6. Двусвязные списки
    count = doubleLists.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : doubleLists) {
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем элементы списка
        auto elements = pair.second->getAllElements();
        size_t size = elements.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (const auto& elem : elements) {
            size_t elem_len = elem.size();
            file.write(reinterpret_cast<const char*>(&elem_len), sizeof(elem_len));
            file.write(elem.c_str(), elem_len);
        }
       }
    
    // 7. Деревья
    count = trees.size();
    file.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& pair : trees) {
        if (pair.second == nullptr) continue;
        
        size_t name_len = pair.first.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(pair.first.c_str(), name_len);
        
        // Сохраняем элементы дерева
        vector<int> elements;
        pair.second->serializeRecursive(pair.second->getRoot(), elements);
        
        size_t size = elements.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));
        for (int elem : elements) {
            file.write(reinterpret_cast<const char*>(&elem), sizeof(elem));
        }
        }
    
    file.close();
}

void loadFromBinaryFile(const string& filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        return;
    }
    
    // Очищаем текущие данные
    for (auto& pair : arrays) delete pair.second;
    arrays.clear();
    
    for (auto& pair : singlyLists) delete pair.second;
    singlyLists.clear();
    
    for (auto& pair : doubleLists) delete pair.second;
    doubleLists.clear();
    
    for (auto& pair : stacks) delete pair.second;
    stacks.clear();
    
    for (auto& pair : queues) delete pair.second;
    queues.clear();
    
    for (auto& pair : trees) delete pair.second;
    trees.clear();
    
    for (auto& pair : hashtables) delete pair.second;
    hashtables.clear();
    
    
    try {
        size_t count;
        
        // 1. Загружаем массивы
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем данные массива
            int length, size;
            file.read(reinterpret_cast<char*>(&length), sizeof(length));
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            
            Array* arr = new Array(length);
            arr->setSize(size);
            
            for (int j = 0; j < size; j++) {
                size_t val_len;
                file.read(reinterpret_cast<char*>(&val_len), sizeof(val_len));
                string value(val_len, ' ');
                file.read(&value[0], val_len);
                arr->setElementAt(j, value);
            }
            
            arrays[name] = arr;
           }
        
        // 2. Загружаем хэш-таблицы
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем данные хэш-таблицы
            size_t capacity, size;
            file.read(reinterpret_cast<char*>(&capacity), sizeof(capacity));
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            
            HashTable* ht = new HashTable(capacity);
            
            for (size_t j = 0; j < size; j++) {
                // Ключ
                size_t key_len;
                file.read(reinterpret_cast<char*>(&key_len), sizeof(key_len));
                string key(key_len, ' ');
                file.read(&key[0], key_len);
                
                // Значение
                int value;
                file.read(reinterpret_cast<char*>(&value), sizeof(value));
                
                ht->insert(key, value);
            }
            
            hashtables[name] = ht;
        }
        
        // 3. Загружаем стеки
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем данные стека
            int length, top;
            file.read(reinterpret_cast<char*>(&length), sizeof(length));
            file.read(reinterpret_cast<char*>(&top), sizeof(top));
            
            Stack* stack = new Stack(length);
            stack->setTop(top);
            
            string* arr = stack->getArray();
            for (int j = 0; j < length; j++) {
                size_t val_len;
                file.read(reinterpret_cast<char*>(&val_len), sizeof(val_len));
                string value(val_len, ' ');
                file.read(&value[0], val_len);
                arr[j] = value;
            }
            
            stacks[name] = stack;
        }
        
        // 4. Загружаем очереди
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем данные очереди
            int length, head, tail;
            file.read(reinterpret_cast<char*>(&length), sizeof(length));
            file.read(reinterpret_cast<char*>(&head), sizeof(head));
            file.read(reinterpret_cast<char*>(&tail), sizeof(tail));
            
            Queue* queue = new Queue(length);
            queue->setHead(head);
            queue->setTail(tail);
            
            string* arr = queue->getArray();
            for (int j = 0; j <= length; j++) {
                size_t val_len;
                file.read(reinterpret_cast<char*>(&val_len), sizeof(val_len));
                string value(val_len, ' ');
                file.read(&value[0], val_len);
                arr[j] = value;
            }
            
            queues[name] = queue;
        }
        
        // 5. Загружаем односвязные списки
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем элементы списка
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            
            SinglyLinkedList* list = new SinglyLinkedList();
            for (size_t j = 0; j < size; j++) {
                size_t elem_len;
                file.read(reinterpret_cast<char*>(&elem_len), sizeof(elem_len));
                string element(elem_len, ' ');
                file.read(&element[0], elem_len);
                list->AddElementAtTail(element);
            }
            
            singlyLists[name] = list;
        }
        
        // 6. Загружаем двусвязные списки
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем элементы списка
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            
            DoubleLinkedList* list = new DoubleLinkedList();
            for (size_t j = 0; j < size; j++) {
                size_t elem_len;
                file.read(reinterpret_cast<char*>(&elem_len), sizeof(elem_len));
                string element(elem_len, ' ');
                file.read(&element[0], elem_len);
                list->AddTail(element);
            }
            
            doubleLists[name] = list;
        }
        
        // 7. Загружаем деревья
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (size_t i = 0; i < count; i++) {
            // Читаем имя
            size_t name_len;
            file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));
            string name(name_len, ' ');
            file.read(&name[0], name_len);
            
            // Читаем элементы дерева
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            
            Tree* tree = new Tree();
            for (size_t j = 0; j < size; j++) {
                int value;
                file.read(reinterpret_cast<char*>(&value), sizeof(value));
                tree->insert(value);
            }
            
            trees[name] = tree;
        }
        
        file.close();
        
    } catch (const exception& e) {
        cerr << "Error reading binary file: " << e.what() << endl;
        file.close();
    }
}

void printUsage() {
    cout << "Usage:" << endl;
    cout << "  ./dbms --file <json_file> --query '<command>'    # Work with JSON files" << endl;
    cout << "  ./dbms --binary <bin_file> --query '<command>'   # Work with binary files" << endl;
    cout << endl;
    cout << "Examples:" << endl;
    cout << "  ./dbms --file data.json --query 'MCREATE arr 3'" << endl;
    cout << "  ./dbms --binary data.bin --query 'HINSERT ht key 100'" << endl;
    cout << "  ./dbms --file data.json --query 'PRINT arr'" << endl;
    cout << "  ./dbms --binary data.bin --query 'PRINT ht'" << endl;
    cout << endl;
    cout << "Universal Commands:" << endl;
    cout << "  PRINT <name>                          - Display any data structure" << endl;
    cout << endl;
    cout << "Array Commands (M):" << endl;
    cout << "  MCREATE <array> <length>               - Create new array" << endl;
    cout << "  MPUSH_BY_INDEX <array> <index> <value> - Add element by index" << endl;
    cout << "  MPUSH_END <array> <value>              - Add element to end" << endl;
    cout << "  MGET_BY_INDEX <array> <index>          - Get element by index" << endl;
    cout << "  MGET <array>                           - Display all array elements" << endl;
    cout << "  MDEL_BY_INDEX <array> <index>          - Delete element by index" << endl;
    cout << "  MREPLACE <array> <index> <value>       - Replace element by index" << endl;
    cout << "  MLENGTH <array>                        - Get array length" << endl;
    cout << endl;
    cout << "Singly List Commands (F):" << endl;
    cout << "  FPUSH_BEFORE <list> <target> <value>   - Add before element" << endl;
    cout << "  FPUSH_AFTER <list> <target> <value>    - Add after element" << endl;
    cout << "  FPUSH_HEAD <list> <value>              - Add to head" << endl;
    cout << "  FPUSH_TAIL <list> <value>              - Add to tail" << endl;
    cout << "  FDEL_BEFORE <list> <target>            - Delete before element" << endl;
    cout << "  FDEL_AFTER <list> <target>             - Delete after element" << endl;
    cout << "  FDEL_HEAD <list>                       - Delete from head" << endl;
    cout << "  FDEL_TAIL <list>                       - Delete from tail" << endl;
    cout << "  FDEL_BY_VALUE <list> <value>           - Delete by value" << endl;
    cout << "  FGET <list>                            - Display list" << endl;
    cout << "  FSEARCH <list> <value>                 - Search element" << endl;
    cout << endl;
    cout << "Double List Commands (L):" << endl;
    cout << "  LPUSH_BEFORE <list> <target> <value>   - Add before element" << endl;
    cout << "  LPUSH_AFTER <list> <target> <value>    - Add after element" << endl;
    cout << "  LPUSH_HEAD <list> <value>              - Add to head" << endl;
    cout << "  LPUSH_TAIL <list> <value>              - Add to tail" << endl;
    cout << "  LDEL_BEFORE <list> <target>            - Delete before element" << endl;
    cout << "  LDEL_AFTER <list> <target>             - Delete after element" << endl;
    cout << "  LDEL_HEAD <list>                       - Delete from head" << endl;
    cout << "  LDEL_TAIL <list>                       - Delete from tail" << endl;
    cout << "  LDEL_BY_VALUE <list> <value>           - Delete by value" << endl;
    cout << "  LGET <list>                            - Display list (forward & backward)" << endl;
    cout << "  LSEARCH <list> <value>                 - Search element" << endl;
    cout << endl;
    cout << "Stack Commands (S):" << endl;
    cout << "  SPUSH <stack> <value>                  - Push element to stack" << endl;
    cout << "  SPOP <stack>                           - Pop element from stack" << endl;
    cout << "  SGET <stack>                           - Display stack" << endl;
    cout << endl;
    cout << "Queue Commands (Q):" << endl;
    cout << "  QPUSH <queue> <value>                  - Push element to queue" << endl;
    cout << "  QPOP <queue>                           - Pop element from queue" << endl;
    cout << "  QGET <queue>                           - Display queue" << endl;
    cout << endl;
    cout << "Tree Commands (T):" << endl;
    cout << "  TINSERT <tree> <value>                 - Insert element into tree" << endl;
    cout << "  TGET <tree>                            - Display tree (all traversals)" << endl;
    cout << "  TSEARCH <tree> <value>                 - Search element in tree" << endl;
    cout << "  TISFULL <tree>                         - Check if Full Binary Tree" << endl;    
    cout << "HashTable Commands (H):" << endl;
    cout << "  HINSERT <table> <key> <value>          - Insert key-value pair" << endl;
    cout << "  HGET <table>                           - Display all elements" << endl;
    cout << "  HSEARCH <table> <key>                  - Search for key" << endl;
    cout << "  HREMOVE <table> <key>                  - Remove key" << endl;
    cout << endl;
}

vector<string> split(const string& str) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Функция для универсального вывода любой структуры
void processPrintCommand(const vector<string>& tokens) {
    if (tokens.size() != 2) {
        cout << "Invalid PRINT command! Usage: PRINT <name>" << endl;
        return;
    }
    
    string name = tokens[1];
    
    // Проверяем массивы
    if (arrays.find(name) != arrays.end()) {
        cout << "Array '" << name << "':" << endl;
        arrays[name]->displayAll();
        return;
    }
    
    // Проверяем односвязные списки
    if (singlyLists.find(name) != singlyLists.end()) {
        cout << "Singly Linked List '" << name << "':" << endl;
        singlyLists[name]->DisplayList();
        return;
    }
    
    // Проверяем двусвязные списки
    if (doubleLists.find(name) != doubleLists.end()) {
    cout << "Double Linked List '" << name << "':" << endl;
    doubleLists[name]->DisplayList();  // ← ИСПРАВЛЕНО
    return;
    }
    
    // Проверяем стеки
    if (stacks.find(name) != stacks.end()) {
    cout << "Stack '" << name << "':" << endl;
    stacks[name]->StackDisplay();  // ← ИСПРАВЛЕНО
    return;
    }
    
    // Проверяем очереди
    if (queues.find(name) != queues.end()) {
    cout << "Queue '" << name << "':" << endl;
    queues[name]->QueueDisplay();  // ← ИСПРАВЛЕНО (добавлено ->)
    return;
    }
    
    // Проверяем деревья
    if (trees.find(name) != trees.end()) {
    if (trees[name] == nullptr || trees[name]->getRoot() == nullptr) {
        cout << "Tree '" << name << "' is empty" << endl;
    } else {
        cout << "Tree '" << name << "':" << endl;
        cout << "Inorder recursive: ";
        trees[name]->printInOrderRecursive(trees[name]->getRoot());
        cout << endl;
        
        cout << "Inorder iterative: ";
        trees[name]->printInOrderIterative(trees[name]->getRoot());
        
        cout << "Preorder: ";
        trees[name]->printPreOrderRecursive(trees[name]->getRoot());
        cout << endl;

        cout << "Postorder: ";
        trees[name]->printPostOrderRecursive(trees[name]->getRoot());
        cout << endl;

        cout << "Level order: ";
        trees[name]->printLevelOrderRecursive(trees[name]->getRoot());
    }
    return;
}
    if (hashtables.find(name) != hashtables.end()) {
        cout << "Hash Table '" << name << "':" << endl;
        hashtables[name]->print_all();
        return;
    }
    cout << "Structure '" << name << "' not found!" << endl;
}

void processArrayCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "MCREATE" && tokens.size() == 3) {
        string name = tokens[1];
        int length = stoi(tokens[2]);
        
        if (arrays.find(name) != arrays.end()) {
            delete arrays[name];
        }
        
        arrays[name] = new Array(length);
        cout << "Array '" << name << "' created with length " << length << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "MPUSH_BY_INDEX" && tokens.size() == 4) {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        string value = tokens[3];
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array '" << name << "' not found! Use MCREATE first." << endl;
        } else {
            arrays[name]->addByIndex(index, value);
            cout << value << endl;
            saveToFile(filename);
        }
    }
    else if (tokens[0] == "MPUSH_END" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array '" << name << "' not found! Use MCREATE first." << endl;
        } else {
            arrays[name]->addToEnd(value);
            cout << value << endl;
            saveToFile(filename);
        }
    }
    else if (tokens[0] == "MGET_BY_INDEX" && tokens.size() == 3) {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array not found!" << endl;
        } else {
            arrays[name]->getByIndex(index);
        }
    }
    else if (tokens[0] == "MGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array not found!" << endl;
        } else {
            arrays[name]->displayAll();
        }
    }
    else if (tokens[0] == "MDEL_BY_INDEX" && tokens.size() == 3) {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array not found!" << endl;
        } else {
            string deletedValue = arrays[name]->deleteByIndex(index);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "MREPLACE" && tokens.size() == 4) {
        string name = tokens[1];
        int index = stoi(tokens[2]);
        string value = tokens[3];
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array not found!" << endl;
        } else {
            // Для получения старого значения нужно немного изменить подход
            // Временно сохраняем старое значение
            string oldValue = arrays[name]->deleteByIndex(index);
            arrays[name]->addByIndex(index, value);
            cout << oldValue << " -> " << value << endl;
            saveToFile(filename);
        }
    }
    else if (tokens[0] == "MLENGTH" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (arrays.find(name) == arrays.end()) {
            cout << "Array not found!" << endl;
        } else {
            arrays[name]->getLength();
        }
    }
    else {
        cout << "Invalid array command!" << endl;
        printUsage();
    }
}

// Вспомогательная функция для получения или создания списка
SinglyLinkedList* getOrCreateList(const string& name) {
    if (singlyLists.find(name) == singlyLists.end()) {
        singlyLists[name] = new SinglyLinkedList();  // вместо createSinglyList()
    }
    return singlyLists[name];
}

void processSinglyListCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "FPUSH_BEFORE" && tokens.size() == 4) {
        string name = tokens[1];
        string target = tokens[2];
        string value = tokens[3];
        
        SinglyLinkedList* list = getOrCreateList(name);
        list->AddElementBefore(value, target);
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "FPUSH_AFTER" && tokens.size() == 4) {
        string name = tokens[1];
        string target = tokens[2];
        string value = tokens[3];
        
        SinglyLinkedList* list = getOrCreateList(name);
        list->AddElementAfter(value, target);
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "FPUSH_HEAD" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        SinglyLinkedList* list = getOrCreateList(name);
        // ПРОСТО ИСПОЛЬЗУЕМ AddHead!
        list->AddHead(value);
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "FPUSH_TAIL" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        SinglyLinkedList* list = getOrCreateList(name);
        list->AddElementAtTail(value);
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "FDEL_BEFORE" && tokens.size() == 3) {
        string name = tokens[1];
        string target = tokens[2];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = singlyLists[name]->DeleteElementBefore(target);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "FDEL_AFTER" && tokens.size() == 3) {
        string name = tokens[1];
        string target = tokens[2];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = singlyLists[name]->DeleteElementAfter(target);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "FDEL_HEAD" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = singlyLists[name]->DeleteElementAtHead();
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "FDEL_TAIL" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = singlyLists[name]->DeleteElementAtTail();
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "FDEL_BY_VALUE" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = singlyLists[name]->DeleteElementByValue(value);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "FGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            singlyLists[name]->DisplayList();
        }
    }
    else if (tokens[0] == "FSEARCH" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        if (singlyLists.find(name) == singlyLists.end()) {
            cout << "List not found!" << endl;
        } else {
            if (singlyLists[name]->SearchElement(value)) {
                cout << "TRUE" << endl;
            } else {
                cout << "FALSE" << endl;
            }
        }
    }
    else {
        cout << "Invalid singly list command!" << endl;
        printUsage();
    }
}

// Вспомогательная функция для получения или создания двусвязного списка
DoubleLinkedList* getOrCreateDoubleList(const string& name) {
    if (doubleLists.find(name) == doubleLists.end()) {
        doubleLists[name] = new DoubleLinkedList();
    }
    return doubleLists[name];
}

// Функция для обработки команд двусвязных списков
void processDoubleListCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "LPUSH_BEFORE" && tokens.size() == 4) {
        string name = tokens[1];
        string target = tokens[2];
        string value = tokens[3];
        
        DoubleLinkedList* list = getOrCreateDoubleList(name);
        list->AddElementBefore(value, target);
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "LPUSH_AFTER" && tokens.size() == 4) {
        string name = tokens[1];
        string target = tokens[2];
        string value = tokens[3];
        
        DoubleLinkedList* list = getOrCreateDoubleList(name);
        list->AddElementAfter(value, target);
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "LPUSH_HEAD" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        DoubleLinkedList* list = getOrCreateDoubleList(name);
        list->AddHead(value);  // используем AddHead напрямую
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "LPUSH_TAIL" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        DoubleLinkedList* list = getOrCreateDoubleList(name);
        list->AddTail(value);  // используем AddTail напрямую
        cout << value << endl;
        saveToFile(filename);
    }
    else if (tokens[0] == "LDEL_BEFORE" && tokens.size() == 3) {
        string name = tokens[1];
        string target = tokens[2];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = doubleLists[name]->DeleteElementBefore(target);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "LDEL_AFTER" && tokens.size() == 3) {
        string name = tokens[1];
        string target = tokens[2];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = doubleLists[name]->DeleteElementAfter(target);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "LDEL_HEAD" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = doubleLists[name]->DeleteElementAtHead();
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "LDEL_TAIL" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = doubleLists[name]->DeleteElementAtTail();
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "LDEL_BY_VALUE" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            string deletedValue = doubleLists[name]->DeleteElementByValue(value);
            if (!deletedValue.empty()) {
                cout << deletedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "LGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            doubleLists[name]->DisplayList();
        }
    }
    else if (tokens[0] == "LSEARCH" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        if (doubleLists.find(name) == doubleLists.end()) {
            cout << "List not found!" << endl;
        } else {
            if (doubleLists[name]->SearchElement(value)) {
                cout << "TRUE" << endl;
            } else {
                cout << "FALSE" << endl;
            }
        }
    }
    else {
        cout << "Invalid double list command!" << endl;
        printUsage();
    }
}

Stack* getOrCreateStack(const string& name) {
    if (stacks.find(name) == stacks.end()) {
        stacks[name] = new Stack(100);  // дефолтный размер 100
    }
    return stacks[name];
}

Queue* getOrCreateQueue(const string& name) {
    if (queues.find(name) == queues.end()) {
        queues[name] = new Queue(100);  // дефолтный размер 100
    }
    return queues[name];
}

// Функция для обработки команд стеков (убираем SCREATE)
void processStackCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "SPUSH" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        Stack* stack = getOrCreateStack(name);
        string pushedValue = stack->StackPush(value);
        if (!pushedValue.empty()) {
            cout << pushedValue << endl;
            saveToFile(filename);
        }
    }
    else if (tokens[0] == "SPOP" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (stacks.find(name) == stacks.end()) {
            cout << "Stack not found!" << endl;
        } else {
            string poppedValue = stacks[name]->StackPop();
            if (!poppedValue.empty()) {
                cout << poppedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "SGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (stacks.find(name) == stacks.end()) {
            cout << "Stack not found!" << endl;
        } else {
            stacks[name]->StackDisplay();
        }
    }
    else {
        cout << "Invalid stack command!" << endl;
        printUsage();
    }
}

void processQueueCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "QPUSH" && tokens.size() == 3) {
        string name = tokens[1];
        string value = tokens[2];
        
        Queue* queue = getOrCreateQueue(name);
        string pushedValue = queue->QueuePush(value);
        if (!pushedValue.empty()) {
            cout << pushedValue << endl;
            saveToFile(filename);
        }
    }
    else if (tokens[0] == "QPOP" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (queues.find(name) == queues.end()) {
            cout << "Queue not found!" << endl;
        } else {
            string poppedValue = queues[name]->QueuePop();
            if (!poppedValue.empty()) {
                cout << poppedValue << endl;
                saveToFile(filename);
            }
        }
    }
    else if (tokens[0] == "QGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (queues.find(name) == queues.end()) {
            cout << "Queue not found!" << endl;
        } else {
            queues[name]->QueueDisplay();
        }
    }
    else {
        cout << "Invalid queue command!" << endl;
        printUsage();
    }
}

// Функция для обработки команд деревьев
void processTreeCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "TINSERT" && tokens.size() == 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        
        Tree*& tree = trees[name];
        if (tree == nullptr) {
            tree = new Tree();
        }
        
        if (tree->insert(value)) {
            cout << value << endl;
            saveToFile(filename);
        } else {
            cout << "Value " << value << " already exists in tree." << endl;
        }

    }
    else if (tokens[0] == "TGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (trees.find(name) == trees.end() || trees[name] == nullptr) {
            cout << "Tree is empty" << endl;
        } else {
            Tree* tree = trees[name];
            cout << "Inorder recursive: ";
            tree->printInOrderRecursive(tree->getRoot());
            cout << endl;
            
            cout << "Inorder iterative: ";
            tree->printInOrderIterative(tree->getRoot());
            
            cout << "Preorder: ";
            tree->printPreOrderRecursive(tree->getRoot());
            cout << endl;

            cout << "Postorder: ";
            tree->printPostOrderRecursive(tree->getRoot());
            cout << endl;

            cout << "Level order: ";
            tree->printLevelOrderRecursive(tree->getRoot());
        }
    }
    else if (tokens[0] == "TSEARCH" && tokens.size() == 3) {
        string name = tokens[1];
        int value = stoi(tokens[2]);
        
        if (trees.find(name) == trees.end() || trees[name] == nullptr) {
            cout << "FALSE" << endl;
        } else {
            if (trees[name]->searchRecursive(trees[name]->getRoot(), value)) {
                cout << "TRUE" << endl;
            } else {
                cout << "FALSE" << endl;
            }
        }
    }
    else if (tokens[0] == "TISFULL" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (trees.find(name) == trees.end() || trees[name] == nullptr) {
            cout << "TRUE" << endl;
        } else {
            if (trees[name]->isFullRecursive(trees[name]->getRoot())) {
                cout << "TRUE" << endl;
            } else {
                cout << "FALSE" << endl;
            }
        }
    }
    else {
        cout << "Invalid tree command!" << endl;
        printUsage();
    }
}

void processHashTableCommand(const vector<string>& tokens, const string& filename) {
    if (tokens[0] == "HINSERT" && tokens.size() == 4) {
        string name = tokens[1];
        string key = tokens[2];
        int value = stoi(tokens[3]);
        
        // Создаем хэш-таблицу, если не существует
        if (hashtables.find(name) == hashtables.end()) {
            hashtables[name] = new HashTable(); // Создается с дефолтным размером 10
        }
        
        if (hashtables[name]->insert(key, value)) {
            cout << value << endl; // Выводим значение, которое добавили
            saveToFile(filename);
        } else {
            cout << "Failed to insert (table might be full)" << endl;
        }
    }
    else if (tokens[0] == "HGET" && tokens.size() == 2) {
        string name = tokens[1];
        
        if (hashtables.find(name) == hashtables.end()) {
            cout << "Hash table '" << name << "' not found!" << endl;
        } else {
            hashtables[name]->print_all();
        }
    }
    else if (tokens[0] == "HSEARCH" && tokens.size() == 3) {
        string name = tokens[1];
        string key = tokens[2];
        
        if (hashtables.find(name) == hashtables.end()) {
            cout << "FALSE" << endl;
        } else {
            if (hashtables[name]->contains(key)) {
                cout << "TRUE" << endl;
            } else {
                cout << "FALSE" << endl;
            }
        }
    }
    else if (tokens[0] == "HREMOVE" && tokens.size() == 3) {
        string name = tokens[1];
        string key = tokens[2];
        
        if (hashtables.find(name) == hashtables.end()) {
            cout << "Hash table '" << name << "' not found!" << endl;
        } else {
            if (hashtables[name]->remove(key)) {
                cout << key << endl; // Выводим ключ, который удалили
                saveToFile(filename);
            } else {
                cout << "Key '" << key << "' not found in hash table" << endl;
            }
        }
    }
    else {
        cout << "Invalid hash table command!" << endl;
        printUsage();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printUsage();
        return 1;
    }
    
    string mode = argv[1];
    string filename = argv[2];
    
    // Режимы без команд
    if (mode == "--save-binary") {
        cout << "Use --binary mode to work with binary files directly" << endl;
        cout << "Example: ./dbms --binary " << filename << " --query 'MCREATE arr 3'" << endl;
        return 0;
    }
    
    if (mode == "--load-binary") {
        cout << "Use --binary mode to work with binary files directly" << endl;
        cout << "Example: ./dbms --binary " << filename << " --query 'PRINT <name>'" << endl;
        return 0;
    }
    
    if (argc != 5) {
        printUsage();
        return 1;
    }
    
    string query = argv[4];
    
    // Загружаем данные ВСЕГДА перед командой
    if (mode == "--file") {
        loadFromFile(filename);
    } else if (mode == "--binary") {
        loadFromBinaryFile(filename);
    } else {
        printUsage();
        return 1;
    }
    
    // Разбираем команду
    vector<string> tokens = split(query);
    
    if (tokens.empty()) {
        cout << "Empty command!" << endl;
        return 1;
    }
    
    string commandType = tokens[0];
    
    // Обработка команд
    if (commandType == "PRINT") {
        processPrintCommand(tokens);
    }
    else if (commandType.substr(0, 1) == "M") {
        processArrayCommand(tokens, filename);
    }
    else if (commandType.substr(0, 1) == "F") {
        processSinglyListCommand(tokens, filename);
    }
    else if (commandType.substr(0, 1) == "L") {
        processDoubleListCommand(tokens, filename);
    }
    else if (commandType.substr(0, 1) == "S") {
        processStackCommand(tokens, filename);
    }
    else if (commandType.substr(0, 1) == "Q") {
        processQueueCommand(tokens, filename);
    }
    else if (commandType.substr(0, 1) == "T") {
        processTreeCommand(tokens, filename);
    }
    else if (commandType.substr(0, 1) == "H") {
        processHashTableCommand(tokens, filename);
    }
    else {
        cout << "Unknown command type!" << endl;
        printUsage();
        return 1;
    }
    
    // Сохраняем данные ВСЕГДА после команды
    if (mode == "--file") {
        saveToFile(filename);
    } else if (mode == "--binary") {
        saveToBinaryFile(filename);
    }
    
    return 0;
}
