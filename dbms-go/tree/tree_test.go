package tree_test

import (
    "dbms-go/tree"
    "os"
    "testing"
)

func TestTree(t *testing.T) {
    t1 := tree.NewTree()

    t1.Insert(10)
    t1.Insert(5)
    t1.Insert(15)

    if !t1.Search(5) {
        t.Fatalf("Search failed")
    }

    if !t1.IsFull() {
        t.Fatalf("Tree should be full")
    }
}

func TestTreeInsertDuplicate(t *testing.T) {
    tr := tree.NewTree()
    tr.Insert(10)
    ok := tr.Insert(10)
    if ok {
        t.Fatalf("Expected false on duplicate insert")
    }
}

func TestTreeSearchMissing(t *testing.T) {
    tr := tree.NewTree()
    tr.Insert(10)
    if tr.Search(999) {
        t.Fatalf("Expected false")
    }
}

func TestTreeIsFullEmpty(t *testing.T) {
    tr := tree.NewTree()

    if !tr.IsFull() {
        t.Fatalf("Empty tree should be full")
    }
}

func TestTreeTraversals(t *testing.T) {
    tr := tree.NewTree()

    values := []int{10, 5, 15, 3, 7, 12, 18}
    for _, v := range values {
        tr.Insert(v)
    }

    tr.PrintInOrder()
    tr.PrintInOrderIterative()
    tr.PrintPreOrder()
    tr.PrintPostOrder()
    tr.PrintLevelOrder()

    ser := tr.Serialize()
    if len(ser) != len(values) {
        t.Fatalf("Serialize wrong size")
    }
}

func TestTreeSetRoot(t *testing.T) {
    tr := tree.NewTree()
    tr.Insert(10)

    newRoot := &tree.TreeNode{Key: 999}
    tr.SetRoot(newRoot)

    if tr.Root.Key != 999 {
        t.Fatalf("SetRoot failed")
    }
}

func TestTree_JSONSerialization(t *testing.T) {
    tr := tree.NewTree()
    tr.Insert(5)
    tr.Insert(3)
    tr.Insert(7)

    err := tr.SaveToFile("test_tree.json")
    if err != nil {
        t.Fatalf("SaveToFile failed: %v", err)
    }

    restored := tree.NewTree()
    err = restored.LoadFromFile("test_tree.json")
    if err != nil {
        t.Fatalf("LoadFromFile failed: %v", err)
    }

    expected := []int{3, 5, 7}
    got := restored.Serialize()
    for i := range expected {
        if got[i] != expected[i] {
            t.Fatalf("Mismatch at %d: expected %d, got %d", i, expected[i], got[i])
        }
    }

    os.Remove("test_tree.json")
}

func TestTree_BinarySerialization(t *testing.T) {
    tr := tree.NewTree()
    tr.Insert(10)
    tr.Insert(6)
    tr.Insert(15)

    err := tr.SaveBinary("test_tree.gob")
    if err != nil {
        t.Fatalf("SaveBinary failed: %v", err)
    }

    restored := tree.NewTree()
    err = restored.LoadBinary("test_tree.gob")
    if err != nil {
        t.Fatalf("LoadBinary failed: %v", err)
    }

    expected := []int{6, 10, 15}
    got := restored.Serialize()
    for i := range expected {
        if got[i] != expected[i] {
            t.Fatalf("Mismatch at %d: expected %d, got %d", i, expected[i], got[i])
        }
    }

    os.Remove("test_tree.gob")
}