#define BOOST_TEST_MODULE SinglyLinkedListTest
#include <boost/test/included/unit_test.hpp>
#include "singlyLinkedList.h"

BOOST_AUTO_TEST_CASE(AddHeadTail) {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementAtTail("b");
    BOOST_CHECK(list.SearchElement("a"));
    BOOST_CHECK(list.SearchElement("b"));
}

BOOST_AUTO_TEST_CASE(AddBeforeAfterValid) {
    SinglyLinkedList list;
    list.AddHead("center");
    list.AddElementBefore("before", "center");
    list.AddElementAfter("after", "center");
    BOOST_CHECK(list.SearchElement("before"));
    BOOST_CHECK(list.SearchElement("after"));
}

BOOST_AUTO_TEST_CASE(AddBeforeAfterInvalid) {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementBefore("x", "ghost");
    list.AddElementAfter("y", "ghost");
    BOOST_CHECK(!list.SearchElement("x"));
    BOOST_CHECK(!list.SearchElement("y"));
}

BOOST_AUTO_TEST_CASE(DeleteByValue) {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementAtTail("b");
    BOOST_CHECK_EQUAL(list.DeleteElementByValue("a"), "a");
    BOOST_CHECK_EQUAL(list.DeleteElementByValue("ghost"), "");
}

BOOST_AUTO_TEST_CASE(DeleteHeadTail) {
    SinglyLinkedList list;
    BOOST_CHECK_EQUAL(list.DeleteElementAtHead(), "");
    BOOST_CHECK_EQUAL(list.DeleteElementAtTail(), "");
    list.AddHead("x");
    list.AddElementAtTail("y");
    BOOST_CHECK_EQUAL(list.DeleteElementAtHead(), "x");
    BOOST_CHECK_EQUAL(list.DeleteElementAtTail(), "y");
}

BOOST_AUTO_TEST_CASE(DeleteBeforeAfterValid) {
    SinglyLinkedList list;
    list.AddHead("1");
    list.AddElementAtTail("2");
    list.AddElementAtTail("3");
    BOOST_CHECK_EQUAL(list.DeleteElementBefore("2"), "1");
    BOOST_CHECK_EQUAL(list.DeleteElementAfter("2"), "3");
}

BOOST_AUTO_TEST_CASE(DeleteBeforeAfterInvalid) {
    SinglyLinkedList list;
    BOOST_CHECK_EQUAL(list.DeleteElementBefore("x"), "");
    BOOST_CHECK_EQUAL(list.DeleteElementAfter("x"), "");
    list.AddHead("solo");
    BOOST_CHECK_EQUAL(list.DeleteElementBefore("solo"), "");
    BOOST_CHECK_EQUAL(list.DeleteElementAfter("solo"), "");
}

BOOST_AUTO_TEST_CASE(SerializationText) {
    SinglyLinkedList listOriginal;
    listOriginal.AddElementAtTail("Apple");
    listOriginal.AddElementAtTail("Banana");

    std::stringstream ss;
    listOriginal.serializeText(ss);

    SinglyLinkedList listLoaded;
    listLoaded.deserializeText(ss);

    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "Apple");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "Banana");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "");
}

BOOST_AUTO_TEST_CASE(SerializationBinary) {
    SinglyLinkedList listOriginal;
    listOriginal.AddElementAtTail("X");
    listOriginal.AddElementAtTail("Y");
    listOriginal.AddElementAtTail("Z");

    std::stringstream ss;
    listOriginal.serializeBinary(ss);

    SinglyLinkedList listLoaded;
    listLoaded.deserializeBinary(ss);

    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "X");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "Y");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "Z");
    BOOST_CHECK_EQUAL(listLoaded.DeleteElementAtHead(), "");
}
