#define BOOST_TEST_MODULE HashTableTest
#include <boost/test/included/unit_test.hpp>
#include "HashTable.h"

BOOST_AUTO_TEST_CASE(InsertAndFind) {
    HashTable ht(5);
    BOOST_CHECK(ht.insert("apple", 10));
    BOOST_CHECK(ht.insert("banana", 20));
    BOOST_CHECK(ht.insert("apple", 30));

    int value = 0;
    BOOST_CHECK(ht.find("apple", value));
    BOOST_CHECK_EQUAL(value, 30);
    BOOST_CHECK(ht.find("banana", value));
    BOOST_CHECK_EQUAL(value, 20);
    BOOST_CHECK(!ht.find("cherry", value));
}

BOOST_AUTO_TEST_CASE(RemoveAndContains) {
    HashTable ht(5);
    ht.insert("key1", 1);
    ht.insert("key2", 2);
    BOOST_CHECK(ht.contains("key1"));
    BOOST_CHECK(ht.remove("key1"));
    BOOST_CHECK(!ht.contains("key1"));
    BOOST_CHECK(!ht.remove("key1"));
}

BOOST_AUTO_TEST_CASE(PrintAllAndEmpty) {
    HashTable ht(3);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    ht.print_all();
    std::string out1 = oss.str();
    BOOST_CHECK(out1.find("empty") != std::string::npos);

    oss.str(""); oss.clear();
    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.print_all();
    std::string out2 = oss.str();
    BOOST_CHECK(out2.find("1") != std::string::npos);
    BOOST_CHECK(out2.find("2") != std::string::npos);
    std::cout.rdbuf(old);
}

BOOST_AUTO_TEST_CASE(GetAllElements) {
    HashTable ht(5);
    ht.insert("x", 100);
    ht.insert("y", 200);
    auto elements = ht.get_all_elements();
    BOOST_CHECK_EQUAL(elements.size(), 2);
}

BOOST_AUTO_TEST_CASE(HashSerializationTest) {
    HashTable ht(15);
    ht.insert("Boost", 1999);

    std::stringstream ssB, ssT;
    ht.serializeBinary(ssB);
    ht.serializeText(ssT);

    HashTable resB, resT;
    resB.deserializeBinary(ssB);
    resT.deserializeText(ssT);

    BOOST_CHECK_EQUAL(resB.get_size(), 1);
    BOOST_CHECK(resT.contains("Boost"));
}