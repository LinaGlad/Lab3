#define BOOST_TEST_MODULE QueueTest
#include <boost/test/included/unit_test.hpp>
#include "queue.h"

BOOST_AUTO_TEST_CASE(PushPopBasic) {
    Queue q(3);
    BOOST_CHECK_EQUAL(q.QueuePush("a"), "a");
    BOOST_CHECK_EQUAL(q.QueuePush("b"), "b");
    BOOST_CHECK_EQUAL(q.QueuePush("c"), ""); 
    BOOST_CHECK_EQUAL(q.QueuePop(), "a");
    BOOST_CHECK_EQUAL(q.QueuePop(), "b");
    BOOST_CHECK_EQUAL(q.QueuePop(), ""); 
}

BOOST_AUTO_TEST_CASE(DisplayEmptyAndFilled) {
    Queue q(3);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    q.QueueDisplay();
    std::string out1 = oss.str();
    BOOST_CHECK(out1.find("Queue is empty") != std::string::npos);

    oss.str(""); oss.clear();
    q.QueuePush("x");
    q.QueuePush("y");
    q.QueueDisplay();
    std::string out2 = oss.str();
    BOOST_CHECK(out2.find("x y") != std::string::npos);
    std::cout.rdbuf(old);
}

BOOST_AUTO_TEST_CASE(SerializationAccessors) {
    Queue q(5);
    q.QueuePush("one");
    q.QueuePush("two");

    BOOST_CHECK_EQUAL(q.getHead(), 1);
    BOOST_CHECK_EQUAL(q.getTail(), 3);
    BOOST_CHECK_EQUAL(q.getLength(), 5);
    const std::string* arr = q.getArray();
    BOOST_CHECK_EQUAL(arr[1], "one");
    BOOST_CHECK_EQUAL(arr[2], "two");

    q.setHead(2);
    q.setTail(2);
    BOOST_CHECK_EQUAL(q.QueuePop(), "");
}

BOOST_AUTO_TEST_CASE(BinarySerialization) {
    Queue q(4);
    q.QueuePush("B1");
    q.QueuePush("B2");

    std::stringstream ss;
    q.serializeBinary(ss);

    Queue loaded(1);
    loaded.deserializeBinary(ss);

    BOOST_CHECK_EQUAL(loaded.QueuePop(), "B1");
    BOOST_CHECK_EQUAL(loaded.QueuePop(), "B2");
}

BOOST_AUTO_TEST_CASE(TextSerialization) {
    Queue q(4);
    q.QueuePush("T1");

    std::stringstream ss;
    q.serializeText(ss);

    Queue loaded(4);
    loaded.deserializeText(ss);

    BOOST_CHECK_EQUAL(loaded.QueuePop(), "T1");
    BOOST_CHECK_EQUAL(loaded.QueuePop(), "");
}
