#include <gtest/gtest.h>
#include "HashTable.h"

TEST(HashTableTest, InsertAndFind) {
    HashTable ht(5);
    EXPECT_TRUE(ht.insert("apple", 10));
    EXPECT_TRUE(ht.insert("banana", 20));
    EXPECT_TRUE(ht.insert("apple", 30)); 

    int value = 0;
    EXPECT_TRUE(ht.find("apple", value));
    EXPECT_EQ(value, 30);

    EXPECT_TRUE(ht.find("banana", value));
    EXPECT_EQ(value, 20);

    EXPECT_FALSE(ht.find("cherry", value));
}

TEST(HashTableTest, RemoveAndContains) {
    HashTable ht(5);
    ht.insert("key1", 1);
    ht.insert("key2", 2);
    EXPECT_TRUE(ht.contains("key1"));
    EXPECT_TRUE(ht.remove("key1"));
    EXPECT_FALSE(ht.contains("key1"));
    EXPECT_FALSE(ht.remove("key1")); 
}

TEST(HashTableTest, PrintAllAndEmpty) {
    HashTable ht(3);
    testing::internal::CaptureStdout();
    ht.print_all();
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("empty"), std::string::npos);

    ht.insert("a", 1);
    ht.insert("b", 2);
    testing::internal::CaptureStdout();
    ht.print_all();
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("1"), std::string::npos);
    EXPECT_NE(out2.find("2"), std::string::npos);
}

TEST(HashTableTest, GetAllElements) {
    HashTable ht(5);
    ht.insert("x", 100);
    ht.insert("y", 200);
    auto elements = ht.get_all_elements();
    EXPECT_EQ(elements.size(), 2);
}

TEST(HashTableTest, AllFormats) {
    HashTable ht(10);
    ht.insert("Key1", 1);
    ht.insert("Key2", 2);

    std::stringstream ssB;
    ht.serializeBinary(ssB);
    HashTable htB;
    htB.deserializeBinary(ssB);
    EXPECT_TRUE(htB.contains("Key1"));
    EXPECT_EQ(htB.get_size(), 2);

    std::stringstream ssT;
    ht.serializeText(ssT);
    HashTable htT;
    htT.deserializeText(ssT);
    int v;
    EXPECT_TRUE(htT.find("Key2", v));
    EXPECT_EQ(v, 2);
}
