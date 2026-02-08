#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream> 
#include "HashTable.h"

TEST_CASE("Insert and Find") {
    HashTable ht(5);
    REQUIRE(ht.insert("apple", 10));
    REQUIRE(ht.insert("banana", 20));
    REQUIRE(ht.insert("apple", 30)); 

    int value = 0;
    REQUIRE(ht.find("apple", value));
    REQUIRE(value == 30);
    REQUIRE(ht.find("banana", value));
    REQUIRE(value == 20);
    REQUIRE_FALSE(ht.find("cherry", value));
}

TEST_CASE("Remove and Contains") {
    HashTable ht(5);
    ht.insert("key1", 1);
    ht.insert("key2", 2);
    REQUIRE(ht.contains("key1"));
    REQUIRE(ht.remove("key1"));
    REQUIRE_FALSE(ht.contains("key1"));
    REQUIRE_FALSE(ht.remove("key1"));
}

TEST_CASE("PrintAll and Empty") {
    HashTable ht(3);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    ht.print_all();
    std::string out1 = oss.str();
    REQUIRE(out1.find("empty") != std::string::npos);

    oss.str(""); oss.clear();
    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.print_all();
    std::string out2 = oss.str();
    REQUIRE(out2.find("1") != std::string::npos);
    REQUIRE(out2.find("2") != std::string::npos);
    std::cout.rdbuf(old);
}

TEST_CASE("Get All Elements") {
    HashTable ht(5);
    ht.insert("x", 100);
    ht.insert("y", 200);
    auto elements = ht.get_all_elements();
    REQUIRE(elements.size() == 2);
}

TEST_CASE("HashTable: Binary and Text Integrity") {
    HashTable ht(20);
    ht.insert("Apple", 100);
    ht.insert("Banana", 200);
    ht.remove("Apple"); 
    ht.insert("Cherry", 300);

    SECTION("Binary Serialization") {
        std::stringstream ss;
        ht.serializeBinary(ss);

        HashTable loaded(1);
        loaded.deserializeBinary(ss);

        int val;
        REQUIRE(loaded.get_size() == 2);
        REQUIRE(loaded.find("Banana", val) == true);
        REQUIRE(val == 200);
        REQUIRE(loaded.contains("Apple") == false);
    }

    SECTION("Text Serialization") {
        std::stringstream ss;
        ht.serializeText(ss);

        HashTable loaded(1);
        loaded.deserializeText(ss);

        int val;
        REQUIRE(loaded.find("Cherry", val) == true);
        REQUIRE(val == 300);
    }
}
