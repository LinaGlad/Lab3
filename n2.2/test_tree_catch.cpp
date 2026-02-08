#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "tree.h"

TEST_CASE("Insert and Search") {
    Tree tree;
    REQUIRE(tree.insert(10));
    REQUIRE(tree.insert(5));
    REQUIRE(tree.insert(15));
    REQUIRE_FALSE(tree.insert(10));

    REQUIRE(tree.searchRecursive(tree.getRoot(), 5));
    REQUIRE_FALSE(tree.searchRecursive(tree.getRoot(), 99));
}

TEST_CASE("Is Full Tree") {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    REQUIRE(tree.isFullRecursive(tree.getRoot()));

    tree.insert(3);
    REQUIRE_FALSE(tree.isFullRecursive(tree.getRoot()));
}

TEST_CASE("Traversals") {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());

    tree.printInOrderRecursive(tree.getRoot());
    std::string inOrder = oss.str();
    REQUIRE(inOrder.find("5 10 15") != std::string::npos);

    oss.str(""); oss.clear();
    tree.printPreOrderRecursive(tree.getRoot());
    std::string preOrder = oss.str();
    REQUIRE(preOrder.find("10 5 15") != std::string::npos);

    oss.str(""); oss.clear();
    tree.printPostOrderRecursive(tree.getRoot());
    std::string postOrder = oss.str();
    REQUIRE(postOrder.find("5 15 10") != std::string::npos);

    oss.str(""); oss.clear();
    tree.printLevelOrderRecursive(tree.getRoot());
    std::string levelOrder = oss.str();
    REQUIRE(levelOrder.find("10 5 15") != std::string::npos);

    std::cout.rdbuf(old);
}

TEST_CASE("Clear Tree") {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.clearTree();
    REQUIRE(tree.getRoot() == nullptr);
}

TEST_CASE("Tree Original Code Serialization") {
    Tree tree;
    tree.insert(50);
    tree.insert(25);
    tree.insert(75);

    SECTION("Binary") {
        std::stringstream ss;
        tree.serializeBinary(ss);

        Tree loaded;
        loaded.deserializeBinary(ss);

        REQUIRE(loaded.searchRecursive(loaded.getRoot(), 50) == true);
        REQUIRE(loaded.searchRecursive(loaded.getRoot(), 25) == true);
        REQUIRE(loaded.searchRecursive(loaded.getRoot(), 10) == false);
    }

    SECTION("Text") {
        std::stringstream ss;
        tree.serializeText(ss);

        Tree loaded;
        loaded.deserializeText(ss);

        REQUIRE(loaded.searchRecursive(loaded.getRoot(), 75) == true);
        REQUIRE(loaded.searchRecursive(loaded.getRoot(), 50) == true);
    }
}
