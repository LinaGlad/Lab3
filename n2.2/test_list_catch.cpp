#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "singlyLinkedList.h"
#include <sstream>

TEST_CASE("Add head and tail") {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementAtTail("b");
    REQUIRE(list.SearchElement("a"));
    REQUIRE(list.SearchElement("b"));
}

TEST_CASE("Add before and after valid") {
    SinglyLinkedList list;
    list.AddHead("center");
    list.AddElementBefore("before", "center");
    list.AddElementAfter("after", "center");
    REQUIRE(list.SearchElement("before"));
    REQUIRE(list.SearchElement("after"));
}

TEST_CASE("Add before and after invalid") {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementBefore("x", "ghost");
    list.AddElementAfter("y", "ghost");
    REQUIRE_FALSE(list.SearchElement("x"));
    REQUIRE_FALSE(list.SearchElement("y"));
}

TEST_CASE("Delete by value valid and invalid") {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementAtTail("b");
    REQUIRE(list.DeleteElementByValue("a") == "a");
    REQUIRE(list.DeleteElementByValue("ghost") == "");
}

TEST_CASE("Delete head and tail including empty") {
    SinglyLinkedList list;
    REQUIRE(list.DeleteElementAtHead() == "");
    REQUIRE(list.DeleteElementAtTail() == "");
    list.AddHead("x");
    list.AddElementAtTail("y");
    REQUIRE(list.DeleteElementAtHead() == "x");
    REQUIRE(list.DeleteElementAtTail() == "y");
}

TEST_CASE("Delete before and after valid") {
    SinglyLinkedList list;
    list.AddHead("1");
    list.AddElementAtTail("2");
    list.AddElementAtTail("3");
    REQUIRE(list.DeleteElementBefore("2") == "1");
    REQUIRE(list.DeleteElementAfter("2") == "3");
}

TEST_CASE("Delete before and after invalid") {
    SinglyLinkedList list;
    REQUIRE(list.DeleteElementBefore("x") == "");
    REQUIRE(list.DeleteElementAfter("x") == "");
    list.AddHead("solo");
    REQUIRE(list.DeleteElementBefore("solo") == "");
    REQUIRE(list.DeleteElementAfter("solo") == "");
}

TEST_CASE("Serialization and Deserialization") {
    SinglyLinkedList listOriginal;
    listOriginal.AddElementAtTail("Alpha");
    listOriginal.AddElementAtTail("Beta");
    listOriginal.AddElementAtTail("Gamma");

    SECTION("Text Serialization") {
        std::stringstream ss;
        listOriginal.serializeText(ss);

        SinglyLinkedList listLoaded;
        listLoaded.deserializeText(ss);

        REQUIRE(listLoaded.DeleteElementAtHead() == "Alpha");
        REQUIRE(listLoaded.DeleteElementAtHead() == "Beta");
        REQUIRE(listLoaded.DeleteElementAtHead() == "Gamma");
        REQUIRE(listLoaded.DeleteElementAtHead() == ""); 
    }

    SECTION("Binary Serialization") {
        std::stringstream ss;
        listOriginal.serializeBinary(ss);

        SinglyLinkedList listLoaded;
        listLoaded.deserializeBinary(ss);

        REQUIRE(listLoaded.DeleteElementAtHead() == "Alpha");
        REQUIRE(listLoaded.DeleteElementAtHead() == "Beta");
        REQUIRE(listLoaded.DeleteElementAtHead() == "Gamma");
        REQUIRE(listLoaded.DeleteElementAtHead() == "");
    }
}
