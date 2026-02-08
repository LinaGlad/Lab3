#include <gtest/gtest.h>
#include "stack.h"

TEST(StackTest, PushPopBasic) {
    Stack s(3);
    EXPECT_EQ(s.StackPush("a"), "a");
    EXPECT_EQ(s.StackPush("b"), "b");
    EXPECT_EQ(s.StackPush("c"), "c");
    EXPECT_EQ(s.StackPush("d"), ""); 
    EXPECT_EQ(s.StackPop(), "c");
    EXPECT_EQ(s.StackPop(), "b");
    EXPECT_EQ(s.StackPop(), "a");
    EXPECT_EQ(s.StackPop(), ""); 
}

TEST(StackTest, DisplayEmptyAndFilled) {
    Stack s(2);
    testing::internal::CaptureStdout();
    s.StackDisplay();
    std::string output1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output1.find("Stack is empty"), std::string::npos);

    s.StackPush("x");
    s.StackPush("y");
    testing::internal::CaptureStdout();
    s.StackDisplay();
    std::string output2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(output2.find("y x"), std::string::npos);
}

TEST(StackTest, SerializationAccessors) {
    Stack s(5);
    s.StackPush("one");
    s.StackPush("two");

    EXPECT_EQ(s.getTop(), 2);
    EXPECT_EQ(s.getLength(), 5);
    const std::string* arr = s.getArray();
    EXPECT_EQ(arr[0], "one");
    EXPECT_EQ(arr[1], "two");

    s.setTop(1);
    EXPECT_EQ(s.StackPop(), "one");
}

TEST(StackTest, TextSerialization) {
    Stack stackOriginal(5);
    stackOriginal.StackPush("First");
    stackOriginal.StackPush("Second");
    stackOriginal.StackPush("Third");

    std::stringstream ss;
    stackOriginal.serializeText(ss);

    Stack stackLoaded(1);
    stackLoaded.deserializeText(ss);

    EXPECT_EQ(stackLoaded.getLength(), 5);
    EXPECT_EQ(stackLoaded.getTop(), 3);

    EXPECT_EQ(stackLoaded.StackPop(), "Third");
    EXPECT_EQ(stackLoaded.StackPop(), "Second");
    EXPECT_EQ(stackLoaded.StackPop(), "First");
    EXPECT_EQ(stackLoaded.StackPop(), ""); 
}

TEST(StackTest, BinarySerialization) {
    Stack stackOriginal(10);
    stackOriginal.StackPush("Data_A");
    stackOriginal.StackPush("Data_B");

    std::stringstream ss;
    stackOriginal.serializeBinary(ss);

    Stack stackLoaded(10);
    stackLoaded.deserializeBinary(ss);

    EXPECT_EQ(stackLoaded.getTop(), 2);
    EXPECT_EQ(stackLoaded.StackPop(), "Data_B");
    EXPECT_EQ(stackLoaded.StackPop(), "Data_A");
}
