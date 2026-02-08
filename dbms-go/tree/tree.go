package tree

import (
    "fmt"
)

type TreeNode struct {
    Key   int
    Left  *TreeNode
    Right *TreeNode
}

type Tree struct {
    Root *TreeNode
}

func NewTree() *Tree {
    return &Tree{Root: nil}
}

func (t *Tree) createNode(key int) *TreeNode {
    return &TreeNode{
        Key:   key,
        Left:  nil,
        Right: nil,
    }
}

func (t *Tree) insertRecursive(node **TreeNode, key int) bool {
    if *node == nil {
        *node = t.createNode(key)
        return true
    }

    if key < (*node).Key {
        return t.insertRecursive(&(*node).Left, key)
    } else if key > (*node).Key {
        return t.insertRecursive(&(*node).Right, key)
    }

    return false
}

func (t *Tree) Insert(key int) bool {
    return t.insertRecursive(&t.Root, key)
}

func (t *Tree) searchRecursive(node *TreeNode, key int) bool {
    if node == nil {
        return false
    }
    if node.Key == key {
        return true
    }
    if key < node.Key {
        return t.searchRecursive(node.Left, key)
    }
    return t.searchRecursive(node.Right, key)
}

func (t *Tree) Search(key int) bool {
    return t.searchRecursive(t.Root, key)
}

func (t *Tree) isFullRecursive(node *TreeNode) bool {
    if node == nil {
        return true
    }
    if node.Left == nil && node.Right == nil {
        return true
    }
    if node.Left != nil && node.Right != nil {
        return t.isFullRecursive(node.Left) && t.isFullRecursive(node.Right)
    }
    return false
}

func (t *Tree) IsFull() bool {
    return t.isFullRecursive(t.Root)
}

func (t *Tree) printInOrderRecursive(node *TreeNode) {
    if node != nil {
        t.printInOrderRecursive(node.Left)
        fmt.Printf("%d ", node.Key)
        t.printInOrderRecursive(node.Right)
    }
}

func (t *Tree) PrintInOrder() {
    t.printInOrderRecursive(t.Root)
    fmt.Println()
}

func (t *Tree) PrintInOrderIterative() {
    stack := []*TreeNode{}
    current := t.Root

    for current != nil || len(stack) > 0 {
        for current != nil {
            stack = append(stack, current)
            current = current.Left
        }

        current = stack[len(stack)-1]
        stack = stack[:len(stack)-1]

        fmt.Printf("%d ", current.Key)
        current = current.Right
    }
    fmt.Println()
}

func (t *Tree) printPreOrderRecursive(node *TreeNode) {
    if node != nil {
        fmt.Printf("%d ", node.Key)
        t.printPreOrderRecursive(node.Left)
        t.printPreOrderRecursive(node.Right)
    }
}

func (t *Tree) PrintPreOrder() {
    t.printPreOrderRecursive(t.Root)
    fmt.Println()
}

func (t *Tree) printPostOrderRecursive(node *TreeNode) {
    if node != nil {
        t.printPostOrderRecursive(node.Left)
        t.printPostOrderRecursive(node.Right)
        fmt.Printf("%d ", node.Key)
    }
}

func (t *Tree) PrintPostOrder() {
    t.printPostOrderRecursive(t.Root)
    fmt.Println()
}

func (t *Tree) printLevelSimple(node *TreeNode, level int, printed *bool) {
    if node == nil {
        return
    }

    if level == 1 {
        fmt.Printf("%d ", node.Key)
        *printed = true
    } else {
        t.printLevelSimple(node.Left, level-1, printed)
        t.printLevelSimple(node.Right, level-1, printed)
    }
}

func (t *Tree) PrintLevelOrder() {
    if t.Root == nil {
        fmt.Println("Tree is empty")
        return
    }

    level := 1
    for {
        printed := false
        t.printLevelSimple(t.Root, level, &printed)
        if !printed {
            break
        }
        level++
    }
    fmt.Println()
}

func (t *Tree) clearTreeRecursive(node **TreeNode) {
    if *node == nil {
        return
    }
    t.clearTreeRecursive(&(*node).Left)
    t.clearTreeRecursive(&(*node).Right)
    *node = nil
}

func (t *Tree) Clear() {
    t.clearTreeRecursive(&t.Root)
}

func (t *Tree) serializeRecursive(node *TreeNode, arr *[]int) {
    if node == nil {
        return
    }
    t.serializeRecursive(node.Left, arr)
    *arr = append(*arr, node.Key)
    t.serializeRecursive(node.Right, arr)
}

func (t *Tree) Serialize() []int {
    result := []int{}
    t.serializeRecursive(t.Root, &result)
    return result
}

func (t *Tree) GetRoot() *TreeNode {
    return t.Root
}

func (t *Tree) SetRoot(newRoot *TreeNode) {
    t.Clear()
    t.Root = newRoot
}

