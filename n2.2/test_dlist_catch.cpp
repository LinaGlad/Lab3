#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "doubleLinkedList.h"
#include <sstream>

TEST_CASE("Add head and tail") {
    DoubleLinkedList list;
    list.AddHead("b");
    list.AddTail("c");
    list.AddHead("a");
    std::vector<std::string> expected = {"a", "b", "c"};
    REQUIRE(list.getAllElements() == expected);
}

TEST_CASE("AddBefore covers AddBefore") {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    list.AddTail("c");
    list.AddElementBefore("x", "b");
    std::vector<std::string> expected = {"a", "x", "b", "c"};
    REQUIRE(list.getAllElements() == expected);
}

TEST_CASE("AddAfter covers AddAfter") {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    list.AddTail("c");
    list.AddElementAfter("y", "b");
    std::vector<std::string> expected = {"a", "b", "y", "c"};
    REQUIRE(list.getAllElements() == expected);
}

TEST_CASE("Add before and after valid") {
    DoubleLinkedList list;
    list.AddHead("center");
    list.AddElementBefore("before", "center");
    list.AddElementAfter("after", "center");
    std::vector<std::string> expected = {"before", "center", "after"};
    REQUIRE(list.getAllElements() == expected);
}

TEST_CASE("Add before and after invalid") {
    DoubleLinkedList list;
    list.AddHead("only");
    list.AddElementBefore("x", "ghost");
    list.AddElementAfter("y", "ghost");
    REQUIRE_FALSE(list.SearchElement("x"));
    REQUIRE_FALSE(list.SearchElement("y"));
}

TEST_CASE("Delete head and tail") {
    DoubleLinkedList list;
    list.AddHead("a");
    list.AddTail("b");
    REQUIRE(list.DeleteElementAtHead() == "a");
    REQUIRE(list.DeleteElementAtTail() == "b");
    REQUIRE(list.DeleteElementAtHead() == "");
}

TEST_CASE("Delete by value") {
    DoubleLinkedList list;
    list.AddHead("a");
    list.AddTail("b");
    list.AddTail("c");
    REQUIRE(list.DeleteElementByValue("b") == "b");
    REQUIRE(list.DeleteElementByValue("ghost") == "");
    std::vector<std::string> expected = {"a", "c"};
    REQUIRE(list.getAllElements() == expected);
}

TEST_CASE("Delete before and after valid") {
    DoubleLinkedList list;
    list.AddHead("1");
    list.AddTail("2");
    list.AddTail("3");
    REQUIRE(list.DeleteElementBefore("2") == "1");
    REQUIRE(list.DeleteElementAfter("2") == "3");
}

TEST_CASE("Delete before and after invalid") {
    DoubleLinkedList list;
    REQUIRE(list.DeleteElementBefore("x") == "");
    REQUIRE(list.DeleteElementAfter("x") == "");
    list.AddHead("solo");
    REQUIRE(list.DeleteElementBefore("solo") == "");
    REQUIRE(list.DeleteElementAfter("solo") == "");
}

TEST_CASE("Search and find") {
    DoubleLinkedList list;
    list.AddTail("x");
    list.AddTail("y");
    int pos = -1;
    auto node = list.FindByValue("y", &pos);
    REQUIRE(node != nullptr);
    REQUIRE(pos == 1);
    REQUIRE(node->key == "y");
}

TEST_CASE("DoubleLinkedList: Serialization and Deserialization") {
    DoubleLinkedList listOriginal;
    listOriginal.AddTail("Node1");
    listOriginal.AddTail("Node2");
    listOriginal.AddTail("Node3");

    SECTION("Text Serialization") {
        std::stringstream ss;
        listOriginal.serializeText(ss);

        DoubleLinkedList listLoaded;
        listLoaded.deserializeText(ss);

        // Ïðîâåðÿåì êîëè÷åñòâî è ïîðÿäîê ÷åðåç óäàëåíèå ñ ãîëîâû
        REQUIRE(listLoaded.DeleteElementAtHead() == "Node1");
        REQUIRE(listLoaded.DeleteElementAtHead() == "Node2");
        REQUIRE(listLoaded.DeleteElementAtHead() == "Node3");
        REQUIRE(listLoaded.DeleteElementAtHead() == "");
    }

    SECTION("Binary Serialization") {
        std::stringstream ss;
        listOriginal.serializeBinary(ss);

        DoubleLinkedList listLoaded;
        listLoaded.deserializeBinary(ss);

        // Ïðîâåðÿåì êîððåêòíîñòü âîññòàíîâëåíèÿ ñâÿçåé (prev/next) 
        // ÷åðåç ïîèñê è óäàëåíèå õâîñòà
        REQUIRE(listLoaded.SearchElement("Node2") == true);
        REQUIRE(listLoaded.DeleteElementAtTail() == "Node3");
        REQUIRE(listLoaded.DeleteElementAtTail() == "Node2");
        REQUIRE(listLoaded.DeleteElementAtTail() == "Node1");
    }
}
