#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <sstream> 
#include "queue.h"

TEST_CASE("Push and Pop basic") {
    Queue q(3);
    REQUIRE(q.QueuePush("a") == "a");
    REQUIRE(q.QueuePush("b") == "b");
    REQUIRE(q.QueuePush("c") == ""); 
    REQUIRE(q.QueuePop() == "a");
    REQUIRE(q.QueuePop() == "b");
    REQUIRE(q.QueuePop() == ""); 
}

TEST_CASE("Display empty and filled") {
    Queue q(3);
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    q.QueueDisplay();
    std::string out1 = oss.str();
    REQUIRE(out1.find("Queue is empty") != std::string::npos);

    oss.str(""); oss.clear();
    q.QueuePush("x");
    q.QueuePush("y");
    q.QueueDisplay();
    std::string out2 = oss.str();
    REQUIRE(out2.find("x y") != std::string::npos);
    std::cout.rdbuf(old);
}

TEST_CASE("Serialization accessors") {
    Queue q(5);
    q.QueuePush("one");
    q.QueuePush("two");

    REQUIRE(q.getHead() == 1);
    REQUIRE(q.getTail() == 3);
    REQUIRE(q.getLength() == 5);
    const std::string* arr = q.getArray();
    REQUIRE(arr[1] == "one");
    REQUIRE(arr[2] == "two");

    q.setHead(2);
    q.setTail(2);
    REQUIRE(q.QueuePop() == "");
}

TEST_CASE("Queue Serialization Tests") {
    Queue q(5);
    q.QueuePush("First");
    q.QueuePush("Second");
    q.QueuePush("Third");
    q.QueuePop(); 

    SECTION("Binary Serialization") {
        std::stringstream ss;
        q.serializeBinary(ss);

        Queue loaded(1); 
        loaded.deserializeBinary(ss);

        REQUIRE(loaded.QueuePop() == "Second");
        REQUIRE(loaded.QueuePop() == "Third");
        REQUIRE(loaded.QueuePop() == ""); 
    }

    SECTION("Text Serialization") {
        std::stringstream ss;
        q.serializeText(ss);

        Queue loaded(10);
        loaded.deserializeText(ss);

        REQUIRE(loaded.QueuePop() == "Second");
        REQUIRE(loaded.QueuePop() == "Third");
    }
}
