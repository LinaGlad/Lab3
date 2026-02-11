package storage_test

import (
    "dbms-go/array"
    "dbms-go/doublelist"
    "dbms-go/hashtable"
    "dbms-go/queue"
    "dbms-go/singlylist"
    "dbms-go/stack"
    "dbms-go/tree"
    "dbms-go/storage"
    "testing"
    "os"
)

func TestJSONSerialization(t *testing.T) {
    s := storage.NewStorage()

    sl := singlylist.NewForwardList()
    sl.AddTail("A")
    sl.AddTail("B")
    s.SinglyLists["sl"] = sl

    dl := doublelist.NewDoubleList()
    dl.AddTail("X")
    dl.AddTail("Y")
    s.DoubleLists["dl"] = dl

    st := stack.NewStack(5)
    st.Push("S1")
    st.Push("S2")
    s.Stacks["st"] = st

    q := queue.NewQueue(5)
    q.Push("Q1")
    q.Push("Q2")
    s.Queues["q"] = q

    ht := hashtable.NewHashTable(10)
    ht.Insert("k1", 100)
    ht.Insert("k2", 200)
    s.HashTables["ht"] = ht

    if err := s.SaveToFile("test.json"); err != nil {
        t.Fatalf("JSON save failed: %v", err)
    }

    s2 := storage.NewStorage()
    if err := s2.LoadFromFile("test.json"); err != nil {
        t.Fatalf("JSON load failed: %v", err)
    }

    if s2.SinglyLists["sl"].Head.Key != "A" {
        t.Fatalf("Singly list not restored")
    }
    if s2.DoubleLists["dl"].Head.Key != "X" {
        t.Fatalf("Double list not restored")
    }
    if s2.Stacks["st"].Top != 2 {
        t.Fatalf("Stack not restored")
    }
    if s2.Queues["q"].Tail != 3 {
        t.Fatalf("Queue not restored")
    }
    if !s2.HashTables["ht"].Contains("k1") {
        t.Fatalf("HashTable not restored")
    }

    os.Remove("test.json")
}

func TestBinarySerialization(t *testing.T) {
    s := storage.NewStorage()

    sl := singlylist.NewForwardList()
    sl.AddTail("A")
    s.SinglyLists["sl"] = sl

    if err := s.SaveBinary("test.gob"); err != nil {
        t.Fatalf("Binary save failed: %v", err)
    }

    s2 := storage.NewStorage()
    if err := s2.LoadBinary("test.gob"); err != nil {
        t.Fatalf("Binary load failed: %v", err)
    }

    if s2.SinglyLists["sl"].Head.Key != "A" {
        t.Fatalf("Binary singly list not restored")
    }

    os.Remove("test.gob")
}

func TestArrayAndTreeJSONSerialization(t *testing.T) {
    s := storage.NewStorage()

    arr := array.NewArray(5)
    arr.AddByIndex(0, "A")
    arr.AddByIndex(1, "B")
    arr.AddByIndex(2, "C")
    s.Arrays["arr1"] = arr

    tr := tree.NewTree()
    tr.Insert(5)
    tr.Insert(2)
    tr.Insert(8)
    tr.Insert(1)
    tr.Insert(3)
    s.Trees["tree1"] = tr

    if err := s.SaveToFile("test_arrays_trees.json"); err != nil {
        t.Fatalf("SaveToFile failed: %v", err)
    }

    s2 := storage.NewStorage()
    if err := s2.LoadFromFile("test_arrays_trees.json"); err != nil {
        t.Fatalf("LoadFromFile failed: %v", err)
    }

    restoredArr := s2.Arrays["arr1"]
    if restoredArr == nil {
        t.Fatalf("Array not restored")
    }

    expectedArr := []string{"A", "B", "C"}
    for i, v := range expectedArr {
        if restoredArr.Arr[i] != v {
            t.Fatalf("Array element mismatch: expected %s, got %s", v, restoredArr.Arr[i])
        }
    }

    restoredTree := s2.Trees["tree1"]
    if restoredTree == nil {
        t.Fatalf("Tree not restored")
    }

    expectedTree := []int{1, 2, 3, 5, 8}
    restoredSlice := restoredTree.Serialize()

    if len(restoredSlice) != len(expectedTree) {
        t.Fatalf("Tree length mismatch: expected %d, got %d", len(expectedTree), len(restoredSlice))
    }

    for i := range expectedTree {
        if restoredSlice[i] != expectedTree[i] {
            t.Fatalf("Tree element mismatch: expected %d, got %d", expectedTree[i], restoredSlice[i])
        }
    }

    os.Remove("test_arrays_trees.json")
}
