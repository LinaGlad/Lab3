#define CATCH_CONFIG_MAIN
#include "array.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

TEST_CASE("AddToEnd and Get") {
    Array arr(2);
    arr.addToEnd("one");
    arr.addToEnd("two");
    REQUIRE(arr.getSizeValue() == 2);
    REQUIRE(arr.getElementAt(0) == "one");
    REQUIRE(arr.getElementAt(1) == "two");
}

TEST_CASE("AddToEnd when full") {
    Array arr(1);
    arr.addToEnd("one");
    arr.addToEnd("two");
    REQUIRE(arr.getSizeValue() == 1);
}

TEST_CASE("AddByIndex valid") {
    Array arr(3);
    arr.addToEnd("a");
    arr.addToEnd("c");
    arr.addByIndex(1, "b");
    REQUIRE(arr.getElementAt(1) == "b");
}

TEST_CASE("AddByIndex invalid") {
    Array arr(2);
    arr.addByIndex(-1, "x");
    arr.addByIndex(5, "y");
    REQUIRE(arr.getSizeValue() == 0);
}

TEST_CASE("DeleteByIndex valid") {
    Array arr(2);
    arr.addToEnd("x");
    arr.addToEnd("y");
    std::string deleted = arr.deleteByIndex(0);
    REQUIRE(deleted == "x");
    REQUIRE(arr.getElementAt(0) == "y");
}

TEST_CASE("DeleteByIndex invalid") {
    Array arr(1);
    std::string deleted = arr.deleteByIndex(0);
    REQUIRE(deleted == "");
}

TEST_CASE("ReplaceByIndex valid") {
    Array arr(1);
    arr.addToEnd("old");
    arr.replaceByIndex(0, "new");
    REQUIRE(arr.getElementAt(0) == "new");
}

TEST_CASE("ReplaceByIndex invalid") {
    Array arr(1);
    arr.replaceByIndex(5, "fail");
    REQUIRE(arr.getSizeValue() == 0);
}

TEST_CASE("Set and Get element") {
    Array arr(2);
    arr.setElementAt(0, "manual");
    arr.setSize(1);
    REQUIRE(arr.getElementAt(0) == "manual");
}

TEST_CASE("Get length value") {
    Array arr(5);
    REQUIRE(arr.getLengthValue() == 5);
}

TEST_CASE("Binary serialization and deserialization") {
    Array original(5);
    original.addToEnd("alpha");
    original.addToEnd("beta");

    std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
    original.serializeBinary(ss);

    Array restored(5);
    restored.deserializeBinary(ss);

    REQUIRE(restored.getSizeValue() == 2);
    REQUIRE(restored.getElementAt(0) == "alpha");
    REQUIRE(restored.getElementAt(1) == "beta");
}

TEST_CASE("Text serialization and deserialization") {
    Array original(5);
    original.addToEnd("gamma");
    original.addToEnd("delta");

    std::stringstream ss;
    original.serializeText(ss);

    Array restored(5);
    restored.deserializeText(ss);

    REQUIRE(restored.getSizeValue() == 2);
    REQUIRE(restored.getElementAt(0) == "gamma");
    REQUIRE(restored.getElementAt(1) == "delta");
}

