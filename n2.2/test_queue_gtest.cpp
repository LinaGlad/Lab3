#include <gtest/gtest.h>
#include "queue.h"

TEST(QueueTest, PushPopBasic) {
    Queue q(3);
    EXPECT_EQ(q.QueuePush("a"), "a");
    EXPECT_EQ(q.QueuePush("b"), "b");
    EXPECT_EQ(q.QueuePush("c"), ""); 
    EXPECT_EQ(q.QueuePop(), "a");
    EXPECT_EQ(q.QueuePop(), "b");
    EXPECT_EQ(q.QueuePop(), ""); 
}

TEST(QueueTest, DisplayEmptyAndFilled) {
    Queue q(3);
    testing::internal::CaptureStdout();
    q.QueueDisplay();
    std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("Queue is empty"), std::string::npos);

    q.QueuePush("x");
    q.QueuePush("y");
    testing::internal::CaptureStdout();
    q.QueueDisplay();
    std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("x y"), std::string::npos);
}

TEST(QueueTest, SerializationAccessors) {
    Queue q(5);
    q.QueuePush("one");
    q.QueuePush("two");

    EXPECT_EQ(q.getHead(), 1);
    EXPECT_EQ(q.getTail(), 3);
    EXPECT_EQ(q.getLength(), 5);
    const std::string* arr = q.getArray();
    EXPECT_EQ(arr[1], "one");
    EXPECT_EQ(arr[2], "two");

    q.setHead(2);
    q.setTail(2);
    EXPECT_EQ(q.QueuePop(), "");
}

TEST(QueueSerialization, BinaryFormat) {
    Queue q(3);
    q.QueuePush("Data1");
    q.QueuePush("Data2");

    std::stringstream ss;
    q.serializeBinary(ss);

    Queue loaded(3);
    loaded.deserializeBinary(ss);

    EXPECT_EQ(loaded.QueuePop(), "Data1");
    EXPECT_EQ(loaded.QueuePop(), "Data2");
    EXPECT_EQ(loaded.QueuePop(), "");
}

TEST(QueueSerialization, TextFormat) {
    Queue q(5);
    q.QueuePush("Text1");
    q.QueuePush("Text2");

    std::stringstream ss;
    q.serializeText(ss);

    Queue loaded(5);
    loaded.deserializeText(ss);

    EXPECT_EQ(loaded.QueuePop(), "Text1");
    EXPECT_EQ(loaded.QueuePop(), "Text2");
}
