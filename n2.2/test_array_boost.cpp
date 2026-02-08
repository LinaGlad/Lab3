#define BOOST_TEST_MODULE ArrayTest
#include <boost/test/included/unit_test.hpp>
#include "array.h"

BOOST_AUTO_TEST_CASE(AddToEndAndGet) {
    Array arr(2);
    arr.addToEnd("one");
    arr.addToEnd("two");
    BOOST_CHECK_EQUAL(arr.getSizeValue(), 2);
    BOOST_CHECK_EQUAL(arr.getElementAt(0), "one");
    BOOST_CHECK_EQUAL(arr.getElementAt(1), "two");
}

BOOST_AUTO_TEST_CASE(AddToEndWhenFull) {
    Array arr(1);
    arr.addToEnd("one");
    arr.addToEnd("two");
    BOOST_CHECK_EQUAL(arr.getSizeValue(), 1);
}

BOOST_AUTO_TEST_CASE(AddByIndexValid) {
    Array arr(3);
    arr.addToEnd("a");
    arr.addToEnd("c");
    arr.addByIndex(1, "b");
    BOOST_CHECK_EQUAL(arr.getElementAt(1), "b");
}

BOOST_AUTO_TEST_CASE(AddByIndexInvalid) {
    Array arr(2);
    arr.addByIndex(-1, "x");
    arr.addByIndex(5, "y");
    BOOST_CHECK_EQUAL(arr.getSizeValue(), 0);
}

BOOST_AUTO_TEST_CASE(DeleteByIndexValid) {
    Array arr(2);
    arr.addToEnd("x");
    arr.addToEnd("y");
    std::string deleted = arr.deleteByIndex(0);
    BOOST_CHECK_EQUAL(deleted, "x");
    BOOST_CHECK_EQUAL(arr.getElementAt(0), "y");
}

BOOST_AUTO_TEST_CASE(DeleteByIndexInvalid) {
    Array arr(1);
    std::string deleted = arr.deleteByIndex(0);
    BOOST_CHECK_EQUAL(deleted, "");
}

BOOST_AUTO_TEST_CASE(ReplaceByIndexValid) {
    Array arr(1);
    arr.addToEnd("old");
    arr.replaceByIndex(0, "new");
    BOOST_CHECK_EQUAL(arr.getElementAt(0), "new");
}

BOOST_AUTO_TEST_CASE(ReplaceByIndexInvalid) {
    Array arr(1);
    arr.replaceByIndex(5, "fail");
    BOOST_CHECK_EQUAL(arr.getSizeValue(), 0);
}

BOOST_AUTO_TEST_CASE(SetAndGetElementAt) {
    Array arr(2);
    arr.setElementAt(0, "manual");
    arr.setSize(1);
    BOOST_CHECK_EQUAL(arr.getElementAt(0), "manual");
}

BOOST_AUTO_TEST_CASE(GetLengthValue) {
    Array arr(5);
    BOOST_CHECK_EQUAL(arr.getLengthValue(), 5);
}

BOOST_AUTO_TEST_CASE(BinarySerialization) {
    Array original(5);
    original.addToEnd("alpha");
    original.addToEnd("beta");

    std::stringstream ss(std::ios::in | std::ios::out | std::ios::binary);
    original.serializeBinary(ss);

    Array restored(5);
    restored.deserializeBinary(ss);

    BOOST_CHECK_EQUAL(restored.getSizeValue(), 2);
    BOOST_CHECK_EQUAL(restored.getElementAt(0), "alpha");
    BOOST_CHECK_EQUAL(restored.getElementAt(1), "beta");
}

BOOST_AUTO_TEST_CASE(TextSerialization) {
    Array original(5);
    original.addToEnd("gamma");
    original.addToEnd("delta");

    std::stringstream ss;
    original.serializeText(ss);

    Array restored(5);
    restored.deserializeText(ss);

    BOOST_CHECK_EQUAL(restored.getSizeValue(), 2);
    BOOST_CHECK_EQUAL(restored.getElementAt(0), "gamma");
    BOOST_CHECK_EQUAL(restored.getElementAt(1), "delta");
}
