#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream> 
#include "stack.h"

TEST_CASE("Push and Pop basic") {
    Stack s(3);
    REQUIRE(s.StackPush("a") == "a");
    REQUIRE(s.StackPush("b") == "b");
    REQUIRE(s.StackPush("c") == "c");
    REQUIRE(s.StackPush("d") == ""); 
    REQUIRE(s.StackPop() == "c");
    REQUIRE(s.StackPop() == "b");
    REQUIRE(s.StackPop() == "a");
    REQUIRE(s.StackPop() == ""); 
}

TEST_CASE("Display empty and filled stack") {
    Stack s(2);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    s.StackDisplay();
    std::string output1 = oss.str();
    REQUIRE(output1.find("Stack is empty") != std::string::npos);

    oss.str(""); oss.clear();
    s.StackPush("x");
    s.StackPush("y");
    s.StackDisplay();
    std::string output2 = oss.str();
    REQUIRE(output2.find("y x") != std::string::npos);
    std::cout.rdbuf(old);
}

TEST_CASE("Serialization accessors") {
    Stack s(5);
    s.StackPush("one");
    s.StackPush("two");

    REQUIRE(s.getTop() == 2);
    REQUIRE(s.getLength() == 5);
    const std::string* arr = s.getArray();
    REQUIRE(arr[0] == "one");
    REQUIRE(arr[1] == "two");

    s.setTop(1);
    REQUIRE(s.StackPop() == "one");
}

TEST_CASE("Stack: Serialization and Deserialization") {
    Stack stackOriginal(10);
    stackOriginal.StackPush("Bottom");
    stackOriginal.StackPush("Middle");
    stackOriginal.StackPush("Top");

    SECTION("Binary Serialization") {
        std::stringstream ss;
        stackOriginal.serializeBinary(ss);

        Stack stackLoaded(5); 
        stackLoaded.deserializeBinary(ss);

        REQUIRE(stackLoaded.getLength() == 10);
        REQUIRE(stackLoaded.getTop() == 3);
        REQUIRE(stackLoaded.StackPop() == "Top");
        REQUIRE(stackLoaded.StackPop() == "Middle");
        REQUIRE(stackLoaded.StackPop() == "Bottom");
        REQUIRE(stackLoaded.StackPop() == ""); 
    }

    SECTION("Text Serialization") {
        std::stringstream ss;
        stackOriginal.serializeText(ss);

        Stack stackLoaded(10);
        stackLoaded.deserializeText(ss);

        REQUIRE(stackLoaded.getTop() == 3);
        REQUIRE(stackLoaded.StackPop() == "Top");
    }
}
