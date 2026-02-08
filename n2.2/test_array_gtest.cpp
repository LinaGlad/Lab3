#include <gtest/gtest.h>
#include "array.h"

TEST(ArrayTest, AddToEndAndGet) {
    Array arr(2);
    arr.addToEnd("one");
    arr.addToEnd("two");
    EXPECT_EQ(arr.getSizeValue(), 2);
    EXPECT_EQ(arr.getElementAt(0), "one");
    EXPECT_EQ(arr.getElementAt(1), "two");
}

TEST(ArrayTest, AddToEndWhenFull) {
    Array arr(1);
    arr.addToEnd("one");
    arr.addToEnd("two"); 
    EXPECT_EQ(arr.getSizeValue(), 1);
}

TEST(ArrayTest, AddByIndexValid) {
    Array arr(3);
    arr.addToEnd("a");
    arr.addToEnd("c");
    arr.addByIndex(1, "b");
    EXPECT_EQ(arr.getElementAt(1), "b");
}

TEST(ArrayTest, AddByIndexInvalid) {
    Array arr(2);
    arr.addByIndex(-1, "x");
    arr.addByIndex(5, "y");
    EXPECT_EQ(arr.getSizeValue(), 0);
}

TEST(ArrayTest, DeleteByIndexValid) {
    Array arr(2);
    arr.addToEnd("x");
    arr.addToEnd("y");
    std::string deleted = arr.deleteByIndex(0);
    EXPECT_EQ(deleted, "x");
    EXPECT_EQ(arr.getElementAt(0), "y");
}

TEST(ArrayTest, DeleteByIndexInvalid) {
    Array arr(1);
    std::string deleted = arr.deleteByIndex(0);
    EXPECT_EQ(deleted, "");
}

TEST(ArrayTest, ReplaceByIndexValid) {
    Array arr(1);
    arr.addToEnd("old");
    arr.replaceByIndex(0, "new");
    EXPECT_EQ(arr.getElementAt(0), "new");
}

TEST(ArrayTest, ReplaceByIndexInvalid) {
    Array arr(1);
    arr.replaceByIndex(5, "fail");
    EXPECT_EQ(arr.getSizeValue(), 0);
}

TEST(ArrayTest, SetAndGetElementAt) {
    Array arr(2);
    arr.setElementAt(0, "manual");
    arr.setSize(1);
    EXPECT_EQ(arr.getElementAt(0), "manual");
}

TEST(ArrayTest, GetLengthValue) {
    Array arr(5);
    EXPECT_EQ(arr.getLengthValue(), 5);
}

TEST(ArrayTest, BinarySerialization) {
    Array original(5);
    original.addToEnd("alpha");
    original.addToEnd("beta");

    std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
    original.serializeBinary(ss);

    Array restored(5);
    restored.deserializeBinary(ss);

    EXPECT_EQ(restored.getSizeValue(), 2);
    EXPECT_EQ(restored.getElementAt(0), "alpha");
    EXPECT_EQ(restored.getElementAt(1), "beta");
}

TEST(ArrayTest, TextSerialization) {
    Array original(5);
    original.addToEnd("gamma");
    original.addToEnd("delta");

    std::stringstream ss;
    original.serializeText(ss);

    Array restored(5);
    restored.deserializeText(ss);

    EXPECT_EQ(restored.getSizeValue(), 2);
    EXPECT_EQ(restored.getElementAt(0), "gamma");
    EXPECT_EQ(restored.getElementAt(1), "delta");
}

