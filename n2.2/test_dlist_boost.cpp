#define BOOST_TEST_MODULE DoubleLinkedListTest
#include <boost/test/included/unit_test.hpp>
#include <iostream>
#include "doubleLinkedList.h"

BOOST_AUTO_TEST_CASE(AddHeadAndTail) {
    DoubleLinkedList list;
    list.AddHead("b");
    list.AddTail("c");
    list.AddHead("a");
    
    std::vector<std::string> expected = {"a", "b", "c"};
    
    std::vector<std::string> actual = list.getAllElements(); 
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), 
        expected.begin(), expected.end()
    );
}

BOOST_AUTO_TEST_CASE(AddBefore_CoversAddBefore) {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    list.AddTail("c");
    list.AddElementBefore("x", "b");
    
    std::vector<std::string> expected = {"a", "x", "b", "c"};
    
    std::vector<std::string> actual = list.getAllElements();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(), 
        expected.begin(), expected.end()
    );
}

BOOST_AUTO_TEST_CASE(AddAfter_CoversAddAfter) {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    list.AddTail("c");
    list.AddElementAfter("y", "b");
    
    std::vector<std::string> expected = {"a", "b", "y", "c"};
    
    std::vector<std::string> actual = list.getAllElements();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(),
        expected.begin(), expected.end()
    );
}

BOOST_AUTO_TEST_CASE(AddBeforeAfterValid) {
    DoubleLinkedList list;
    list.AddHead("center");
    list.AddElementBefore("before", "center");
    list.AddElementAfter("after", "center");
    
    std::vector<std::string> expected = {"before", "center", "after"};
    
    std::vector<std::string> actual = list.getAllElements();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(),
        expected.begin(), expected.end()
    );
}

BOOST_AUTO_TEST_CASE(AddBeforeAfterInvalid) {
    DoubleLinkedList list;
    list.AddHead("only");
    list.AddElementBefore("x", "ghost");
    list.AddElementAfter("y", "ghost");
    BOOST_CHECK(!list.SearchElement("x"));
    BOOST_CHECK(!list.SearchElement("y"));
}

BOOST_AUTO_TEST_CASE(DeleteHeadTail) {
    DoubleLinkedList list;
    list.AddHead("a");
    list.AddTail("b");
    BOOST_CHECK_EQUAL(list.DeleteElementAtHead(), "a");
    BOOST_CHECK_EQUAL(list.DeleteElementAtTail(), "b");
    BOOST_CHECK_EQUAL(list.DeleteElementAtHead(), "");
}

BOOST_AUTO_TEST_CASE(DeleteByValue) {
    DoubleLinkedList list;
    list.AddHead("a");
    list.AddTail("b");
    list.AddTail("c");
    
    BOOST_CHECK_EQUAL(list.DeleteElementByValue("b"), "b");
    BOOST_CHECK_EQUAL(list.DeleteElementByValue("ghost"), "");
    
    std::vector<std::string> expected = {"a", "c"};
    
    std::vector<std::string> actual = list.getAllElements();
    
    BOOST_CHECK_EQUAL_COLLECTIONS(
        actual.begin(), actual.end(),
        expected.begin(), expected.end()
    );
}

BOOST_AUTO_TEST_CASE(DeleteBeforeAfterValid) {
    DoubleLinkedList list;
    list.AddHead("1");
    list.AddTail("2");
    list.AddTail("3");
    BOOST_CHECK_EQUAL(list.DeleteElementBefore("2"), "1");
    BOOST_CHECK_EQUAL(list.DeleteElementAfter("2"), "3");
}

BOOST_AUTO_TEST_CASE(DeleteBeforeAfterInvalid) {
    DoubleLinkedList list;
    BOOST_CHECK_EQUAL(list.DeleteElementBefore("x"), "");
    BOOST_CHECK_EQUAL(list.DeleteElementAfter("x"), "");
    list.AddHead("solo");
    BOOST_CHECK_EQUAL(list.DeleteElementBefore("solo"), "");
    BOOST_CHECK_EQUAL(list.DeleteElementAfter("solo"), "");
}

BOOST_AUTO_TEST_CASE(SearchAndFind) {
    DoubleLinkedList list;
    list.AddTail("x");
    list.AddTail("y");
    int pos = -1;
    auto node = list.FindByValue("y", &pos);
    BOOST_CHECK(node != nullptr);
    BOOST_CHECK_EQUAL(pos, 1);
    BOOST_CHECK_EQUAL(node->key, "y");
}

BOOST_AUTO_TEST_CASE(SerializationTestText) {
    DoubleLinkedList listOriginal;
    listOriginal.AddTail("First");
    listOriginal.AddTail("Second");

    std::stringstream ss;
    listOriginal.serializeText(ss);

    DoubleLinkedList listLoaded;
    listLoaded.deserializeText(ss);

    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "First");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "Second");
}

BOOST_AUTO_TEST_CASE(SerializationTestBinary) {
    DoubleLinkedList listOriginal;
    listOriginal.AddTail("Bin1");
    listOriginal.AddTail("Bin2");

    std::stringstream ss;
    listOriginal.serializeBinary(ss);

    DoubleLinkedList listLoaded;
    listLoaded.deserializeBinary(ss);

    BOOST_CHECK(listLoaded.SearchElement("Bin1"));
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtTail(), "Bin2");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtTail(), "Bin1");
}
