#include <gtest/gtest.h>
#include "doubleLinkedList.h"

TEST(DoubleLinkedListTest, AddHeadAndTail) {
    DoubleLinkedList list;
    list.AddHead("b");
    list.AddTail("c");
    list.AddHead("a");
    std::vector<std::string> expected = {"a", "b", "c"};
    EXPECT_EQ(list.getAllElements(), expected);
}

TEST(DoubleLinkedListTest, AddBeforeCoversAddBefore) {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    list.AddTail("c");
    list.AddElementBefore("x", "b");
    std::vector<std::string> expected = {"a", "x", "b", "c"};
    EXPECT_EQ(list.getAllElements(), expected);
}

TEST(DoubleLinkedListTest, AddAfterCoversAddAfter) {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    list.AddTail("c");
    list.AddElementAfter("y", "b");
    std::vector<std::string> expected = {"a", "b", "y", "c"};
    EXPECT_EQ(list.getAllElements(), expected);
}

TEST(DoubleLinkedListTest, AddBeforeAndAfterValid) {
    DoubleLinkedList list;
    list.AddHead("center");
    list.AddElementBefore("before", "center");
    list.AddElementAfter("after", "center");
    std::vector<std::string> expected = {"before", "center", "after"};
    EXPECT_EQ(list.getAllElements(), expected);
}

TEST(DoubleLinkedListTest, AddBeforeAndAfterInvalid) {
    DoubleLinkedList list;
    list.AddHead("only");
    testing::internal::CaptureStdout();
    list.AddElementBefore("x", "ghost");
    list.AddElementAfter("y", "ghost");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(list.SearchElement("x"));
    EXPECT_FALSE(list.SearchElement("y"));
    EXPECT_NE(output.find("not found"), std::string::npos);
}

TEST(DoubleLinkedListTest, DeleteHeadTail) {
    DoubleLinkedList list;
    list.AddHead("a");
    list.AddTail("b");
    EXPECT_EQ(list.DeleteElementAtHead(), "a");
    EXPECT_EQ(list.DeleteElementAtTail(), "b");
    EXPECT_EQ(list.DeleteElementAtHead(), "");
}

TEST(DoubleLinkedListTest, DeleteByValue) {
    DoubleLinkedList list;
    list.AddHead("a");
    list.AddTail("b");
    list.AddTail("c");
    EXPECT_EQ(list.DeleteElementByValue("b"), "b");
    EXPECT_EQ(list.DeleteElementByValue("ghost"), "");
    std::vector<std::string> expected = {"a", "c"};
    EXPECT_EQ(list.getAllElements(), expected);
}

TEST(DoubleLinkedListTest, DeleteBeforeAfterValid) {
    DoubleLinkedList list;
    list.AddHead("1");
    list.AddTail("2");
    list.AddTail("3");
    EXPECT_EQ(list.DeleteElementBefore("2"), "1");
    EXPECT_EQ(list.DeleteElementAfter("2"), "3");
}

TEST(DoubleLinkedListTest, DeleteBeforeAfterInvalid) {
    DoubleLinkedList list;
    list.AddHead("solo");
    testing::internal::CaptureStdout();
    EXPECT_EQ(list.DeleteElementBefore("solo"), "");
    EXPECT_EQ(list.DeleteElementAfter("solo"), "");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("No values before"), std::string::npos);
}

TEST(DoubleLinkedListTest, SearchAndFind) {
    DoubleLinkedList list;
    list.AddTail("x");
    list.AddTail("y");
    int pos = -1;
    auto node = list.FindByValue("y", &pos);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(pos, 1);
    EXPECT_EQ(node->key, "y");
}

TEST(DoubleLinkedListTest, DisplayListDoesNotCrash) {
    DoubleLinkedList list;
    list.AddTail("a");
    list.AddTail("b");
    testing::internal::CaptureStdout();
    list.DisplayList();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("List forward"), std::string::npos);
    EXPECT_NE(output.find("List backward"), std::string::npos);
}

TEST(DoubleLinkedListTest, TextSerialization) {
    DoubleLinkedList listOriginal;
    listOriginal.AddTail("A");
    listOriginal.AddTail("B");

    std::stringstream ss;
    listOriginal.serializeText(ss);

    DoubleLinkedList listLoaded;
    listLoaded.deserializeText(ss);

    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "A");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "B");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "");
}

TEST(DoubleLinkedListTest, BinarySerialization) {
    DoubleLinkedList listOriginal;
    listOriginal.AddTail("Data1");
    listOriginal.AddTail("Data2");

    std::stringstream ss;
    listOriginal.serializeBinary(ss);

    DoubleLinkedList listLoaded;
    listLoaded.deserializeBinary(ss);

    EXPECT_EQ(listLoaded.DeleteElementAtTail(), "Data2");
    EXPECT_EQ(listLoaded.DeleteElementAtTail(), "Data1");
}
