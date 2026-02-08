#define BOOST_TEST_MODULE StackTest
#include <boost/test/included/unit_test.hpp>
#include "stack.h"

BOOST_AUTO_TEST_CASE(PushPopBasic) {
    Stack s(3);
    BOOST_CHECK_EQUAL(s.StackPush("a"), "a");
    BOOST_CHECK_EQUAL(s.StackPush("b"), "b");
    BOOST_CHECK_EQUAL(s.StackPush("c"), "c");
    BOOST_CHECK_EQUAL(s.StackPush("d"), ""); 
    BOOST_CHECK_EQUAL(s.StackPop(), "c");
    BOOST_CHECK_EQUAL(s.StackPop(), "b");
    BOOST_CHECK_EQUAL(s.StackPop(), "a");
    BOOST_CHECK_EQUAL(s.StackPop(), ""); 
}

BOOST_AUTO_TEST_CASE(DisplayEmptyAndFilled) {
    Stack s(2);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    s.StackDisplay();
    std::string output1 = oss.str();
    BOOST_CHECK(output1.find("Stack is empty") != std::string::npos);

    oss.str(""); oss.clear();
    s.StackPush("x");
    s.StackPush("y");
    s.StackDisplay();
    std::string output2 = oss.str();
    BOOST_CHECK(output2.find("y x") != std::string::npos);
    std::cout.rdbuf(old);
}

BOOST_AUTO_TEST_CASE(SerializationAccessors) {
    Stack s(5);
    s.StackPush("one");
    s.StackPush("two");

    BOOST_CHECK_EQUAL(s.getTop(), 2);
    BOOST_CHECK_EQUAL(s.getLength(), 5);
    const std::string* arr = s.getArray();
    BOOST_CHECK_EQUAL(arr[0], "one");
    BOOST_CHECK_EQUAL(arr[1], "two");

    s.setTop(1);
    BOOST_CHECK_EQUAL(s.StackPop(), "one");
}

BOOST_AUTO_TEST_CASE(StackSerializationText) {
    Stack s1(100);
    s1.StackPush("Bottom");
    s1.StackPush("Middle");
    s1.StackPush("Top");

    std::stringstream ss;
    s1.serializeText(ss);

    Stack s2(10); 
    s2.deserializeText(ss);

    BOOST_CHECK_EQUAL(s2.getLength(), 100);
    BOOST_CHECK_EQUAL(s2.getTop(), 3);

    BOOST_CHECK_EQUAL(s2.StackPop(), "Top");
    BOOST_CHECK_EQUAL(s2.StackPop(), "Middle");
    BOOST_CHECK_EQUAL(s2.StackPop(), "Bottom");
}

BOOST_AUTO_TEST_CASE(StackSerializationBinary) {
    Stack s1(5);
    s1.StackPush("Binary1");
    s1.StackPush("Binary2");

    std::stringstream ss;
    s1.serializeBinary(ss);

    Stack s2(5);
    s2.deserializeBinary(ss);

    BOOST_CHECK_EQUAL(s2.getTop(), 2);
    BOOST_CHECK_EQUAL(s2.StackPop(), "Binary2");
    BOOST_CHECK_EQUAL(s2.StackPop(), "Binary1");
    BOOST_CHECK_EQUAL(s2.StackPop(), ""); 
}
