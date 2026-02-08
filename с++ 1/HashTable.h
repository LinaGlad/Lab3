#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

enum class EntryState {
    EMPTY,
    OCCUPIED,
    DELETED
};

struct Entry {
    std::string key;
    int value;
    EntryState state;
    
    Entry() : value(0), state(EntryState::EMPTY) {}
};

class HashTable {
private:
    Entry* table;
    size_t capacity;
    size_t size;
    
    static const size_t DEFAULT_CAPACITY = 10;
    static const size_t NOT_FOUND = static_cast<size_t>(-1);
    
    static size_t hash_function(const std::string& key, size_t table_capacity) {
        size_t hash_value = 0;
        for (char c : key) {
            hash_value = hash_value * 31 + static_cast<size_t>(c);
        }
        return hash_value % table_capacity;
    }
    
public:
    HashTable(size_t initial_capacity = DEFAULT_CAPACITY) 
        : capacity(initial_capacity), size(0) {
        table = new Entry[initial_capacity];
        for (size_t i = 0; i < initial_capacity; i++) {
            table[i].state = EntryState::EMPTY;
        }
    }
    
    ~HashTable() {
        delete[] table;
    }
    
    bool insert(const std::string& key, int value) {
        if (size >= capacity) {
            return false; 
        }
        
        size_t index = hash_function(key, capacity);
        size_t attempt = 0;
        
        while (attempt < capacity) {
            size_t current_index = (index + attempt) % capacity;
            
            if (table[current_index].state == EntryState::EMPTY ||
                table[current_index].state == EntryState::DELETED) {
                
                table[current_index].key = key;
                table[current_index].value = value;
                table[current_index].state = EntryState::OCCUPIED;
                size++;
                return true;
            }
            
            if (table[current_index].state == EntryState::OCCUPIED &&
                table[current_index].key == key) {
                table[current_index].value = value; 
                return true;
            }
            
            attempt++;
        }
        
        return false;
    }
    
    bool find(const std::string& key, int& value) const {
        size_t index = hash_function(key, capacity);
        size_t attempt = 0;
        
        while (attempt < capacity) {
            size_t current_index = (index + attempt) % capacity;
            
            if (table[current_index].state == EntryState::EMPTY) {
                return false;
            }
            
            if (table[current_index].state == EntryState::OCCUPIED &&
                table[current_index].key == key) {
                value = table[current_index].value;
                return true;
            }
            
            attempt++;
        }
        
        return false;
    }
    
    bool remove(const std::string& key) {
        size_t index = hash_function(key, capacity);
        size_t attempt = 0;
        
        while (attempt < capacity) {
            size_t current_index = (index + attempt) % capacity;
            
            if (table[current_index].state == EntryState::EMPTY) {
                return false;
            }
            
            if (table[current_index].state == EntryState::OCCUPIED &&
                table[current_index].key == key) {
                table[current_index].state = EntryState::DELETED;
                size--;
                return true;
            }
            
            attempt++;
        }
        
        return false;
    }
    
    void print_all() const {
        bool has_elements = false;
        
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].state == EntryState::OCCUPIED) {
                std::cout << table[i].value << " ";
                has_elements = true;
            }
        }
        
        if (!has_elements) {
            std::cout << "Hash table is empty" << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
    
    bool contains(const std::string& key) const {
        int dummy;
        return find(key, dummy);
    }
    
    std::vector<std::pair<std::string, int>> get_all_elements() const {
        std::vector<std::pair<std::string, int>> result;
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i].state == EntryState::OCCUPIED) {
                result.push_back({table[i].key, table[i].value});
            }
        }
        return result;
    }
    
    size_t get_size() const {
        return size;
    }
    
    size_t get_capacity() const {
        return capacity;
    }
    
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
};

#endif
