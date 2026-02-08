#include "array.h"
#include "singlyLinkedList.h"
#include "doubleLinkedList.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "HashTable.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>

class Timer {
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    double stop() {
        auto end = std::chrono::high_resolution_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start_time);
        return ms.count() / 1000.0;
    }
};

void print_result(const std::string& name, double ms, int ops) {
    double rate = ops / (ms / 1000.0);
    std::cout << std::setw(20) << name
              << std::setw(12) << std::fixed << std::setprecision(3) << ms << " ms"
              << std::setw(15) << std::fixed << std::setprecision(0) << rate << " ops/sec"
              << std::endl;
}

void benchmark_array() {
    std::cout << "\nBenchmark: Array\n";
    const int N = 10000;
    Array arr(N+2000);
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        arr.addToEnd("str" + std::to_string(i));
    }
    print_result("Add to End", t.stop(), N);

    std::mt19937 gen(42);
    std::uniform_int_distribution<> dis(0, N - 1);
    volatile int total = 0;

    t.start();
    for (int i = 0; i < N; ++i) {
        std::string s = arr.getElementAt(dis(gen));
        total += s.length();
    }
    print_result("Random Access", t.stop(), N);

    t.start();
    for (int i = 0; i < 1000; ++i) {
        arr.addByIndex(0, "inserted");
    }
    print_result("Insert Front", t.stop(), 1000);

    t.start();
    for (int i = 0; i < 1000; ++i) {
        int index = arr.getSizeValue() / 2;
        arr.deleteByIndex(index);
    }
    print_result("Delete Middle", t.stop(), 1000);
}

void benchmark_singly_linked_list() {
    std::cout << "\nBenchmark: SinglyLinkedList\n";
    const int N = 10000;
    SinglyLinkedList list;
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        list.AddHead("val" + std::to_string(i));
    }
    print_result("Add Head", t.stop(), N);

    t.start();
    int found = 0;
    for (int i = 0; i < 1000; ++i) {
        if (list.SearchElement("val" + std::to_string(i))) {
            found++;
        }
    }
    print_result("Search", t.stop(), 1000);

    t.start();
    for (int i = 0; i < 1000; ++i) {
        list.DeleteElementAtHead();
    }
    print_result("Delete Head", t.stop(), 1000);
}

void benchmark_double_linked_list() {
    std::cout << "\nBenchmark: DoubleLinkedList\n";
    const int N = 10000;
    DoubleLinkedList list;
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        list.AddHead("val" + std::to_string(i));
    }
    print_result("Add Head", t.stop(), N);

    DoubleLinkedList tailList;
    t.start();
    for (int i = 0; i < N; ++i) {
        tailList.AddTail("val" + std::to_string(i));
    }
    print_result("Add Tail", t.stop(), N);

    t.start();
    int found = 0;
    for (int i = 0; i < 1000; ++i) {
        if (list.SearchElement("val" + std::to_string(i))) {
            found++;
        }
    }
    print_result("Search", t.stop(), 1000);

    t.start();
    for (int i = 0; i < 1000; ++i) {
        list.DeleteElementAtHead();
    }
    print_result("Delete Head", t.stop(), 1000);

    t.start();
    for (int i = 0; i < 1000; ++i) {
        tailList.DeleteElementAtTail();
    }
    print_result("Delete Tail", t.stop(), 1000);
}

void benchmark_stack() {
    std::cout << "\nBenchmark: Stack\n";
    const int N = 10000;
    Stack s(N + 1000);
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        s.StackPush("val" + std::to_string(i));
    }
    print_result("Push", t.stop(), N);

    t.start();
    for (int i = 0; i < N; ++i) {
        s.StackPop();
    }
    print_result("Pop", t.stop(), N);
}

void benchmark_queue() {
    std::cout << "\nBenchmark: Queue\n";
    const int N = 10000;
    Queue q(N + 10);
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        q.QueuePush("val" + std::to_string(i));
    }
    print_result("Enqueue", t.stop(), N);

    t.start();
    for (int i = 0; i < N; ++i) {
        q.QueuePop();
    }
    print_result("Dequeue", t.stop(), N);
}

void benchmark_tree() {
    std::cout << "\nBenchmark: Tree\n";
    const int N = 10000;
    Tree tree;
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        tree.insert(i);
    }
    print_result("Insert", t.stop(), N);

    t.start();
    int found = 0;
    for (int i = 0; i < N; ++i) {
        if (tree.searchRecursive(tree.getRoot(), i)) {
            found++;
        }
    }
    print_result("Search", t.stop(), N);
}

void benchmark_hashtable() {
    std::cout << "\nBenchmark: HashTable\n";
    const int N = 10000;
    HashTable ht(N + 1000);
    Timer t;

    t.start();
    for (int i = 0; i < N; ++i) {
        ht.insert("key" + std::to_string(i), i);
    }
    print_result("Insert", t.stop(), N);

    int value = 0;
    t.start();
    for (int i = 0; i < N; ++i) {
        ht.find("key" + std::to_string(i), value);
    }
    print_result("Find", t.stop(), N);

    t.start();
    for (int i = 0; i < N; ++i) {
        ht.remove("key" + std::to_string(i));
    }
    print_result("Remove", t.stop(), N);
}

int main() {
    std::cout << "Starting benchmark...\n";
    benchmark_array();
    benchmark_singly_linked_list();
    benchmark_double_linked_list(); 
    benchmark_stack();
    benchmark_queue();
    benchmark_tree();
    benchmark_hashtable();
    std::cout << "\nBenchmark complete!\n";
    return 0;
}
