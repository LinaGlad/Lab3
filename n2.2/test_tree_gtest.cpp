#include <gtest/gtest.h>
#include "tree.h"

TEST(TreeTest, InsertAndSearch) {
    Tree tree;
    EXPECT_TRUE(tree.insert(10));
    EXPECT_TRUE(tree.insert(5));
    EXPECT_TRUE(tree.insert(15));
    EXPECT_FALSE(tree.insert(10)); 

    EXPECT_TRUE(tree.searchRecursive(tree.getRoot(), 5));
    EXPECT_FALSE(tree.searchRecursive(tree.getRoot(), 99));
}

TEST(TreeTest, IsFullTree) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    EXPECT_TRUE(tree.isFullRecursive(tree.getRoot()));

    tree.insert(3);
    EXPECT_FALSE(tree.isFullRecursive(tree.getRoot()));
}

TEST(TreeTest, Traversals) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    testing::internal::CaptureStdout();
    tree.printInOrderRecursive(tree.getRoot());
    std::string inOrder = testing::internal::GetCapturedStdout();
    EXPECT_NE(inOrder.find("5 10 15"), std::string::npos);

    testing::internal::CaptureStdout();
    tree.printPreOrderRecursive(tree.getRoot());
    std::string preOrder = testing::internal::GetCapturedStdout();
    EXPECT_NE(preOrder.find("10 5 15"), std::string::npos);

    testing::internal::CaptureStdout();
    tree.printPostOrderRecursive(tree.getRoot());
    std::string postOrder = testing::internal::GetCapturedStdout();
    EXPECT_NE(postOrder.find("5 15 10"), std::string::npos);

    testing::internal::CaptureStdout();
    tree.printLevelOrderRecursive(tree.getRoot());
    std::string levelOrder = testing::internal::GetCapturedStdout();
    EXPECT_NE(levelOrder.find("10 5 15"), std::string::npos);
}

TEST(TreeTest, ClearTree) {
    Tree tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.clearTree();
    EXPECT_EQ(tree.getRoot(), nullptr);
}

TEST(TreeSerialization, BinaryFormat) {
    Tree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    std::stringstream ss;
    tree.serializeBinary(ss);

    Tree loaded;
    loaded.deserializeBinary(ss);

    EXPECT_TRUE(loaded.searchRecursive(loaded.getRoot(), 10));
    EXPECT_TRUE(loaded.searchRecursive(loaded.getRoot(), 5));
    EXPECT_TRUE(loaded.searchRecursive(loaded.getRoot(), 15));
    EXPECT_FALSE(loaded.searchRecursive(loaded.getRoot(), 99));
}

TEST(TreeSerialization, TextFormat) {
    Tree tree;
    tree.insert(20);
    tree.insert(30);

    std::stringstream ss;
    tree.serializeText(ss);

    Tree loaded;
    loaded.deserializeText(ss);

    EXPECT_TRUE(loaded.searchRecursive(loaded.getRoot(), 20));
    EXPECT_TRUE(loaded.searchRecursive(loaded.getRoot(), 30));
    EXPECT_FALSE(loaded.searchRecursive(loaded.getRoot(), 10));
}
