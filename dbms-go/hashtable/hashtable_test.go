package hashtable_test

import (
    "dbms-go/hashtable"
    "testing"
)

func TestHashTableBasic(t *testing.T) {
    h := hashtable.NewHashTable(10)

    h.Insert("a", 1)
    h.Insert("b", 2)

    if !h.Contains("a") {
        t.Fatalf("Contains failed")
    }

    if !h.Remove("a") {
        t.Fatalf("Remove failed")
    }

    if h.Contains("a") {
        t.Fatalf("Expected a to be removed")
    }
}

func TestHashTableInsertDuplicate(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.Insert("a", 1)
    ok := h.Insert("a", 2) 
    if !ok {
        t.Fatalf("Expected true on duplicate insert (overwrite)")
    }

    val, found := h.Find("a")
    if !found || val != 2 {
        t.Fatalf("Expected updated value 2, got %d", val)
    }
}

func TestHashTableRemoveMissing(t *testing.T) {
    h := hashtable.NewHashTable(10)
    ok := h.Remove("zzz")
    if ok {
        t.Fatalf("Expected false on missing remove")
    }
}

func TestHashTablePrintAll(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.PrintAll() 

    h.Insert("a", 1)
    h.Insert("b", 2)
    h.PrintAll() 
}

func TestHashTableSearchMissing(t *testing.T) {
    h := hashtable.NewHashTable(10)
    if h.Contains("zzz") {
        t.Fatalf("Expected false")
    }
}

func TestHashTableGetAllElements(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.Insert("x", 100)
    h.Insert("y", 200)

    elems := h.GetAllElements()
    if len(elems) != 2 {
        t.Fatalf("Expected 2 elements")
    }

    found := false
    for _, e := range elems {
        if e.Key == "x" && e.Value == 100 {
            found = true
        }
    }
    if !found {
        t.Fatalf("Expected to find key x with value 100")
    }
}

func TestHashTableSizeAndCapacity(t *testing.T) {
    h := hashtable.NewHashTable(5)
    if h.Capacity != 5 {
        t.Fatalf("Expected capacity 5")
    }

    h.Insert("a", 1)
    h.Insert("b", 2)

    if h.Size != 2 {
        t.Fatalf("Expected size 2")
    }
}
