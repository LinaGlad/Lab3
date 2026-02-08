#define BOOST_TEST_MODULE TreeTest
#include <boost/test/included/unit_test.hpp>
#include "tree.h"

BOOST_AUTO_TEST_CASE(InsertAndSearch) {
    Tree tree;
    BOOST_CHECK(tree.insert(10));
    BOOST_CHECK(tree.insert(5));
    BOOST_CHECK(tree.insert(15));
    BOOST_CHECK(!tree.insert(10));

    BOOST_CHECK(tree.searchRecursive(tree.getRoot(), 5));
    BOOST_CHECK(!tree.searchRecursive(tree.getRoot(), 99));
}

BOOST_AUTO_TEST_CASE(IsFullTree) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    BOOST_CHECK(tree.isFullRecursive(tree.getRoot()));

    tree.insert(3);
    BOOST_CHECK(!tree.isFullRecursive(tree.getRoot()));
}

BOOST_AUTO_TEST_CASE(Traversals) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

    tree.printInOrderRecursive(tree.getRoot());
    std::string inOrder = oss.str();
    BOOST_CHECK(inOrder.find("5 10 15") != std::string::npos);

    oss.str(""); oss.clear();
    tree.printPreOrderRecursive(tree.getRoot());
    std::string preOrder = oss.str();
    BOOST_CHECK(preOrder.find("10 5 15") != std::string::npos);

    oss.str(""); oss.clear();
    tree.printPostOrderRecursive(tree.getRoot());
    std::string postOrder = oss.str();
    BOOST_CHECK(postOrder.find("5 15 10") != std::string::npos);

    oss.str(""); oss.clear();
    tree.printLevelOrderRecursive(tree.getRoot());
    std::string levelOrder = oss.str();
    BOOST_CHECK(levelOrder.find("10 5 15") != std::string::npos);

    std::cout.rdbuf(old);
}

BOOST_AUTO_TEST_CASE(ClearTree) {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.clearTree();
    BOOST_CHECK(tree.getRoot() == nullptr);
}

BOOST_AUTO_TEST_CASE(BinarySerializationTest) {
    Tree tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(150);

    std::stringstream ss;
    tree.serializeBinary(ss);

    Tree loaded;
    loaded.deserializeBinary(ss);

    BOOST_CHECK(loaded.searchRecursive(loaded.getRoot(), 100));
    BOOST_CHECK(loaded.searchRecursive(loaded.getRoot(), 50));
    BOOST_CHECK(loaded.searchRecursive(loaded.getRoot(), 150));
    BOOST_CHECK(!loaded.searchRecursive(loaded.getRoot(), 200)); 
}

BOOST_AUTO_TEST_CASE(TextSerializationTest) {
    Tree tree;
    tree.insert(42);
    tree.insert(21);

    std::stringstream ss;
    tree.serializeText(ss);

    Tree loaded;
    loaded.deserializeText(ss);

    BOOST_CHECK(loaded.searchRecursive(loaded.getRoot(), 42));
    BOOST_CHECK(loaded.searchRecursive(loaded.getRoot(), 21));
    
    BOOST_CHECK(loaded.getRoot() != nullptr);
}
