#include <gtest/gtest.h>
#include "singlyLinkedList.h"

TEST(SinglyLinkedListTest, AddHeadAndTail) {
    SinglyLinkedList list;
    list.AddHead("first");
    list.AddElementAtTail("second");
    EXPECT_TRUE(list.SearchElement("first"));
    EXPECT_TRUE(list.SearchElement("second"));
}

TEST(SinglyLinkedListTest, AddBeforeAndAfterValid) {
    SinglyLinkedList list;
    list.AddHead("center");
    list.AddElementBefore("before", "center");
    list.AddElementAfter("after", "center");
    EXPECT_TRUE(list.SearchElement("before"));
    EXPECT_TRUE(list.SearchElement("after"));
}

TEST(SinglyLinkedListTest, AddBeforeAndAfterInvalid) {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementBefore("x", "notfound");
    list.AddElementAfter("y", "notfound");
    EXPECT_FALSE(list.SearchElement("x"));
    EXPECT_FALSE(list.SearchElement("y"));
}

TEST(SinglyLinkedListTest, DeleteByValueValidAndInvalid) {
    SinglyLinkedList list;
    list.AddHead("a");
    list.AddElementAtTail("b");
    EXPECT_EQ(list.DeleteElementByValue("a"), "a");
    EXPECT_EQ(list.DeleteElementByValue("ghost"), "");
}

TEST(SinglyLinkedListTest, DeleteHeadTailEmpty) {
    SinglyLinkedList list;
    EXPECT_EQ(list.DeleteElementAtHead(), "");
    EXPECT_EQ(list.DeleteElementAtTail(), "");
    list.AddHead("x");
    list.AddElementAtTail("y");
    EXPECT_EQ(list.DeleteElementAtHead(), "x");
    EXPECT_EQ(list.DeleteElementAtTail(), "y");
}

TEST(SinglyLinkedListTest, DeleteBeforeAndAfterValid) {
    SinglyLinkedList list;
    list.AddHead("1");
    list.AddElementAtTail("2");
    list.AddElementAtTail("3");
    EXPECT_EQ(list.DeleteElementBefore("2"), "1");
    EXPECT_EQ(list.DeleteElementAfter("2"), "3");
}

TEST(SinglyLinkedListTest, DeleteBeforeAndAfterInvalid) {
    SinglyLinkedList list;
    EXPECT_EQ(list.DeleteElementBefore("x"), "");
    EXPECT_EQ(list.DeleteElementAfter("x"), "");
    list.AddHead("solo");
    EXPECT_EQ(list.DeleteElementBefore("solo"), "");
    EXPECT_EQ(list.DeleteElementAfter("solo"), "");
}

TEST(SinglyLinkedListTest, SerializationText) {
    SinglyLinkedList listOriginal;
    listOriginal.AddElementAtTail("One");
    listOriginal.AddElementAtTail("Two");

    std::stringstream ss;
    listOriginal.serializeText(ss);

    SinglyLinkedList listLoaded;
    listLoaded.deserializeText(ss);

    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "One");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "Two");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "");
}

TEST(SinglyLinkedListTest, SerializationBinary) {
    SinglyLinkedList listOriginal;
    listOriginal.AddElementAtTail("Bin1");
    listOriginal.AddElementAtTail("Bin2");
    listOriginal.AddElementAtTail("Bin3");

    std::stringstream ss;
    listOriginal.serializeBinary(ss);

    SinglyLinkedList listLoaded;
    listLoaded.deserializeBinary(ss);

    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "Bin1");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "Bin2");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "Bin3");
    EXPECT_EQ(listLoaded.DeleteElementAtHead(), "");
}
